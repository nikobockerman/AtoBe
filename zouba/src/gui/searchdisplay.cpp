#include "searchdisplay.h"
#include "ui_searchdisplay.h"

#include "routeresultwidget.h"
#include "favoriteselectiondialog.h"
#include "locationsdisplaywidget.h"

#include "src/logic/locations.h"
#include "src/logic/routefinder.h"

#include <QDebug>

SearchDisplay::SearchDisplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SearchDisplay),
    route_finder(NULL),
    one_search(),
    search_restarted(false),
    edit_window(NULL)
{
    qDebug() << "Start constructor";
    ui->setupUi(this);
    this->setWindowTitle(QCoreApplication::applicationName());
    qDebug() << "Application name:" << QCoreApplication::applicationName();

    Locations *locations = Locations::GetInstance();
    this->connect(locations, SIGNAL(locationsChanged()), SLOT(locations_changed()));

    QMenuBar *menu = this->ui->menubar;

#ifdef Q_WS_MAEMO_5
    this->setAttribute(Qt::WA_Maemo5StackedWindow);
    this->setAttribute(Qt::WA_Maemo5AutoOrientation);

    this->ui->fromHorizontalLayout->removeWidget(this->ui->from_combo);
    this->ui->from_combo->deleteLater();
    //this->ui->from_favorites->setIcon(QIcon::fromTheme("edit-copy"));
    //this->ui->from_favorites->setText("Fav");

    this->ui->destHorizontalLayout->removeWidget(this->ui->dest_combo);
    this->ui->dest_combo->deleteLater();
    //this->ui->from_favorites->setIcon(QIcon::fromTheme("edit-copy"));
    //this->ui->dest_favorites->setText("Fav");

    QAction *use_gps = new QAction("Use GPS", this);
    use_gps->setCheckable(true);
    use_gps->setChecked(false);
    this->connect(use_gps, SIGNAL(toggled(bool)), SLOT(gps_status_change_requested(bool)));
    this->connect(use_gps, SIGNAL(toggled(bool)), locations->getGpsLocation(), SLOT(enableGps(bool)));
    menu->addAction(use_gps);

    this->from_selected = NULL;
    this->dest_selected = NULL;

#else
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();
    widget->setLayout(layout);

    this->tabs = new QTabWidget();
    this->tabs->setTabsClosable(true);
    this->ui->centralwidget->setParent(this->tabs);
    this->tabs->addTab(this->ui->centralwidget, "Search");

    this->connect(this->tabs, SIGNAL(tabCloseRequested(int)), SLOT(tabclosed(int)));

    layout->addWidget(this->tabs);
    this->setCentralWidget(widget);

    this->ui->fromHorizontalLayout->removeWidget(this->ui->from_favorites);
    this->ui->from_favorites->deleteLater();
    this->ui->destHorizontalLayout->removeWidget(this->ui->dest_favorites);
    this->ui->dest_favorites->deleteLater();

    this->updateLocationLists();

    this->on_from_combo_currentIndexChanged(this->ui->from_combo->currentText());
    this->ui->dest_combo->setCurrentIndex(1);

    QAction *modify_locations = new QAction("Modify locations", this);
    this->connect(modify_locations, SIGNAL(triggered()), SLOT(customize_requested()));
    menu->addAction(modify_locations);

#endif

    qDebug() << "Finish constructor";
}

void SearchDisplay::gps_status_change_requested(bool status)
{


}

SearchDisplay::~SearchDisplay()
{
    delete ui;
}

void SearchDisplay::updateLocationLists()
{
    qDebug() << "Start updateLocationLists";
#ifndef Q_WS_MAEMO_5
    this->ui->from_combo->blockSignals(true);
    this->ui->dest_combo->blockSignals(true);
    this->ui->from_combo->clear();
    this->ui->dest_combo->clear();
    //this->ui->from_combo->blockSignals(false);
    //this->ui->dest_combo->blockSignals(false);

    /// TODO: Add GPS location if GPS is selected.




    QStringList locs;
    Locations *locations = Locations::GetInstance();
    for (int index = 1; index <= locations->size(); ++index)
    {
        Location* loc = locations->getLocation(index);
        if (loc && loc->isValid())
        {
            qDebug() << "Adding location: " << loc->label();
            locs << loc->label();

        }
    }
    //this->ui->from_combo->blockSignals(true);
    //this->ui->dest_combo->blockSignals(true);
    this->ui->from_combo->addItems(locs);
    this->ui->dest_combo->addItems(locs);

    this->ui->from_combo->blockSignals(false);
    this->ui->dest_combo->blockSignals(false);
#endif
    qDebug() << "Finish updateLocationLists";
}

void SearchDisplay::locations_changed()
{
#ifndef Q_WS_MAEMO_5
    qDebug() << "Start locations_changed";

    QString from_old = this->ui->from_combo->currentText();
    QString dest_old = this->ui->dest_combo->currentText();

    this->updateLocationLists();

    qDebug() << "Reselecting old items.";
    int from_id = this->ui->from_combo->findText(from_old);
    if (from_id >= 0)
        this->ui->from_combo->setCurrentIndex(from_id);
    else
        this->on_from_combo_currentIndexChanged(this->ui->from_combo->currentText());

    int dest_id = this->ui->dest_combo->findText(dest_old);
    if (dest_id >= 0)
        this->ui->dest_combo->setCurrentIndex(dest_id);
    else
        this->on_dest_combo_currentIndexChanged(this->ui->dest_combo->currentText());

    qDebug() << "Finish locations_changed";
#endif
}

void SearchDisplay::on_searchButton_clicked()
{
    qDebug() << "Start on_search_button_clicked";
    if (!this->one_search.tryLock())
        return; // If mutex is locked ie. the results are being processed, do nothing.
    if (this->route_finder)
    {
#ifdef Q_WS_MAEMO_5
        this->setAttribute(Qt::WA_Maemo5ShowProgressIndicator, false);
#endif
        this->route_finder->disconnect(this);
        this->route_finder->deleteLater();
        this->route_finder = NULL;
        this->search_restarted = true;
        qDebug() << "Tried to start new search. Restart set to true.";
    }

    // Check for empty search fields.
    QString empty;
    if (this->ui->from_edit->text() == empty)
    {
        qDebug() << "From field is empty. No search is made.";
        this->one_search.unlock();
        this->search_restarted = false;
        return;
    }
    if (this->ui->dest_edit->text() == empty)
    {
        qDebug() << "Dest field is empty. No search is made.";
        this->one_search.unlock();
        this->search_restarted = false;
        return;
    }

    Location *from, *dest;
#ifdef Q_WS_MAEMO_5
    from = this->from_selected;
    dest = this->dest_selected;
#else
    Locations* locations = Locations::GetInstance();
    from = locations->getLocation(this->ui->from_combo->currentText());
    dest = locations->getLocation(this->ui->dest_combo->currentText());
#endif
    if (from != NULL && this->ui->from_edit->text() == from->address()) {
        qDebug() << "Written text matches the text in the combo box";
        from = new Location(*from);
    } else {
        qDebug() << "Written text differs from the text in the combo box.";
        from = new Location("Temp", this->ui->from_edit->text());
    }

    if (dest != NULL && this->ui->dest_edit->text() == dest->address()) {
        qDebug() << "Written text matches the text in the combo box";
        dest = new Location(*dest);
    } else {
        qDebug() << "Written text differs from the text in the combo box.";
        dest = new Location("Temp", this->ui->dest_edit->text());
    }

    qDebug() << "Starting route search";

    this->route_finder = new RouteFinder(*from, *dest);
    delete from;
    delete dest;
    this->connect(this->route_finder, SIGNAL(finished()), SLOT(route_finder_finished()));
#ifdef Q_WS_MAEMO_5
    this->setAttribute(Qt::WA_Maemo5ShowProgressIndicator, true);
#endif
    this->one_search.unlock();
    qDebug() << "Finished on_search_button_clicked.";
}

void SearchDisplay::route_finder_finished()
{
    qDebug() << "Received signal from successful route finder";
    if (!this->one_search.tryLock())
        return;
    if (this->search_restarted)
    {
        qDebug() << "Restart had been requested.";
        this->search_restarted = false;
        this->one_search.unlock();
        return;
    }
    if(!this->route_finder)
    {
        qDebug() << "Route finder is NULL.";
        this->one_search.unlock();
        return;
    }

#ifdef Q_WS_MAEMO_5
    RouteResultWidget *results = new RouteResultWidget(this);
    this->setAttribute(Qt::WA_Maemo5ShowProgressIndicator, false);
    results->show();
#else
    RouteResultWidget *results = new RouteResultWidget();
    int cur = this->tabs->addTab(results, "Route" + QString::number(this->tabs->count()));
    this->tabs->setCurrentIndex(cur);
#endif

    for (int i = 0; i < this->route_finder->getNumberOfRoutes(); i++)
        results->addRoute(this->route_finder->getRoute(i));

    this->route_finder->disconnect(this);
    this->route_finder->deleteLater();
    this->route_finder = NULL;

    this->one_search.unlock();
    qDebug() << "Finish route_finder_finished";
}

void SearchDisplay::setEditText(QLineEdit* edit, QString& text)
{
    qDebug() << "Start setEditText";
    Locations* locations = Locations::GetInstance();
    Location* loc = locations->getLocation(text);
    if (loc)
        edit->setText(loc->address());
    qDebug() << "Finish setEditText";
}


void SearchDisplay::on_from_combo_currentIndexChanged(QString text)
{
#ifndef Q_WS_MAEMO_5
    qDebug() << "New FROM location selected.";
    setEditText(this->ui->from_edit, text);
    qDebug() << "Finish on_from_combo_currentIndexChanged";
#endif
}


void SearchDisplay::on_dest_combo_currentIndexChanged(QString text)
{
#ifndef Q_WS_MAEMO_5
    qDebug() << "New DEST location selected.";
    setEditText(this->ui->dest_edit, text);
    qDebug() << "Finish on_dest_combo_currentIndexChanged";
#endif
}


#ifndef Q_WS_MAEMO_5
void SearchDisplay::tabclosed(int index)
{
    qDebug() << "Tab close requested. Nr" << index;
    if (index == 0)
    {
        qDebug() << "First tab requested to be closed.";
        return;
    }
    QWidget *widget = this->tabs->widget(index);
    this->tabs->removeTab(index);
    if (widget == this->edit_window)
        this->edit_window = NULL;
    widget->deleteLater();
}
#endif //Q_WS_MAEMO_5

void SearchDisplay::on_from_favorites_clicked()
{
#ifdef Q_WS_MAEMO_5
    qDebug() << "FROM Favorites button clicked";
    FavoriteSelectionDialog *dialog = new FavoriteSelectionDialog();
    this->connect(dialog, SIGNAL(selectedLocation(Location*)), SLOT(from_selection_selected(Location*)));
    this->connect(dialog, SIGNAL(customizeRequested()), SLOT(customize_requested()));
    dialog->show();
#endif
}


void SearchDisplay::on_dest_favorites_clicked()
{
#ifdef Q_WS_MAEMO_5
    qDebug() << "DEST Favorites button clicked";
    FavoriteSelectionDialog *dialog = new FavoriteSelectionDialog();
    this->connect(dialog, SIGNAL(selectedLocation(Location*)), SLOT(dest_selection_selected(Location*)));
    this->connect(dialog, SIGNAL(customizeRequested()), SLOT(customize_requested()));
    dialog->show();
#endif
}

#ifdef Q_WS_MAEMO_5
void SearchDisplay::from_selection_selected(Location *location)
{
    if (location == NULL)
    {
        qDebug() << "NULL location received from FavoriteSelectionDialog.";
        return;
    }
    this->from_selected = location;
    this->ui->from_edit->setText(this->from_selected->address());
}

void SearchDisplay::dest_selection_selected(Location *location)
{
    if (location == NULL)
    {
        qDebug() << "NULL location received from FavoriteSelectionDialog.";
        return;
    }
    this->dest_selected = location;
    this->ui->dest_edit->setText(this->dest_selected->address());
}
#endif

void SearchDisplay::customize_requested()
{
    qDebug() << "Customizing favorites requested.";

#ifdef Q_WS_MAEMO_5
    if (!this->edit_window)
        this->edit_window = new LocationsDisplayWidget(this);
    this->edit_window->showWidget();
#else
    if (!this->edit_window)
    {
        this->edit_window = new LocationsDisplayWidget();
        this->tabs->addTab(this->edit_window, "Modify locations");
    }
    this->tabs->setCurrentWidget(this->edit_window);
#endif
}
