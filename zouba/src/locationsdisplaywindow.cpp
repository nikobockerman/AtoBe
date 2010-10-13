#include "locationsdisplaywindow.h"
#include "ui_locationsdisplaywindow.h"
#include "locations.h"
#include "addressdialog.h"

#include <QDebug>
#include <QListWidgetItem>
#include <QListWidget>
#include <QList>

const QString invalidPostText = " - Invalid address";
const QString editText = "Edit list";

QString getLocName(const QListWidgetItem *item);
Location* getSelectedLocation(QList<QListWidgetItem*> list);
/*QString getLocName(const QListWidgetItem *item);
Location* getSelectedLocation(QList<QListWidgetItem*> list);*/

LocationsDisplayWindow::LocationsDisplayWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LocationsDisplayWindow)
{
    ui->setupUi(this);
#ifdef Q_WS_MAEMO_5
    this->setAttribute(Qt::WA_Maemo5StackedWindow);
#endif
    QAction *editListAction = new QAction(editText, this->ui->menuBar);
    this->ui->menuBar->addAction(editListAction);
    connect(editListAction, SIGNAL(triggered()), this, SLOT(showEditOptions()));
//#endif
    this->ui->editViewWidget->hide();

    connect(this->ui->newLocButton, SIGNAL(clicked()), this, SLOT(addAddress()));
    connect(this->ui->locationsWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(editLocation(QListWidgetItem*)));
    connect(this->ui->deleteButton, SIGNAL(clicked()), this, SLOT(remove()));
    connect(this->ui->upButton, SIGNAL(clicked()), this, SLOT(moveUp()));
    connect(this->ui->downButton, SIGNAL(clicked()), this, SLOT(moveDown()));
    connect(this->ui->doneButton, SIGNAL(clicked()), this, SLOT(closeEditOptions()));

    this->populateLocations();

    Locations *locations = Locations::GetInstance();
    connect(locations, SIGNAL(locationsChanged()), this, SLOT(populateLocations()));
}

LocationsDisplayWindow::~LocationsDisplayWindow()
{
    delete ui;
}

void LocationsDisplayWindow::showEditOptions()
{
    disconnect(this->ui->locationsWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(editLocation(QListWidgetItem*)));
    this->ui->defaultViewWidget->hide();
    this->ui->editViewWidget->show();
}

void LocationsDisplayWindow::closeEditOptions()
{
    connect(this->ui->locationsWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(editLocation(QListWidgetItem*)));
    this->ui->defaultViewWidget->show();
    this->ui->editViewWidget->hide();
}

void LocationsDisplayWindow::populateLocations()
{
    this->ui->locationsWidget->clear();
    qDebug() << "Populating locations";
    Locations *locations = Locations::GetInstance();

    for (int index = 1; index <= locations->size(); ++index)
    {
        qDebug() << "Adding location: " << locations->getLocation(index)->label();
        Location* loc = locations->getLocation(index);
        QString dispName = loc->label();
        if (!loc->isValid())
            dispName.append(invalidPostText);
        new QListWidgetItem(dispName, this->ui->locationsWidget);
    }
    qDebug() << "Locations populated";
}

void LocationsDisplayWindow::addAddress()
{
    AddressDialog *dialog = new AddressDialog(this);
    dialog->show();
}

void LocationsDisplayWindow::editLocation(QListWidgetItem *item)
{
    if (!item) return;

    Locations *locations = Locations::GetInstance();
    QString findText = getLocName(item);
    Location *loc = locations->getLocation(findText);
    if (!loc)
        qDebug() << "No location with label " << findText << " was found from locations.";
    else
    {
        AddressDialog *dialog = new AddressDialog(this, loc);
        dialog->show();
    }
}

QString getLocName(const QListWidgetItem *item)
{
    if (!item) return 0;
    QString retText = item->text();
    if (retText.contains(" - Invalid address", Qt::CaseSensitive))
        retText.chop(18);
    return retText;
}

void LocationsDisplayWindow::remove()
{
    qDebug() << "Remove called";
    Location* loc = getSelectedLocation(this->ui->locationsWidget->selectedItems());
    if (!loc)
        qDebug() << "No location with selected label was found from locations.";
    else
    {
        Locations *locations = Locations::GetInstance();
        locations->removeLocation(loc);
    }
}

Location* getSelectedLocation(QList<QListWidgetItem*> list)
{
    if (list.size() == 0)
    {
        qDebug() << "No item is selected";
        return 0;
    }
    QListWidgetItem *item = list.at(0);
    QString name = getLocName(item);
    qDebug() << "Selected item is" << name;
    Locations *locations = Locations::GetInstance();
    return locations->getLocation(name);
}

void LocationsDisplayWindow::moveUp()
{
    qDebug() << "Move up called";
    Location* loc = getSelectedLocation(this->ui->locationsWidget->selectedItems());
    if (!loc)
        qDebug() << "No location with selected label was found from locations.";
    else
    {
        Locations *locations = Locations::GetInstance();
        locations->lowerLocationIndex(loc->label());
    }
}

void LocationsDisplayWindow::moveDown()
{
    qDebug() << "Move down called";
    Location* loc = getSelectedLocation(this->ui->locationsWidget->selectedItems());
    if (!loc)
        qDebug() << "No location with selected label was found from locations.";
    else
    {
        Locations *locations = Locations::GetInstance();
        locations->increaseLocationIndex(loc->label());
    }
}

