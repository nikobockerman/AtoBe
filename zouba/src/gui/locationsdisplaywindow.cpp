#include "locationsdisplaywindow.h"
#include "ui_locationsdisplaywindow.h"

#include "src/logic/locations.h"

#include "src/addressdialog.h"

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

    this->populateLocations();

    Locations *locations = Locations::GetInstance();
    connect(locations, SIGNAL(locationsChanged()), this, SLOT(populateLocations()));

    this->ui->buttonsStacked->adjustSize();
    this->ui->locationsWidget->adjustSize();
}

LocationsDisplayWindow::~LocationsDisplayWindow()
{
    delete ui;
}

void LocationsDisplayWindow::populateLocations()
{
    this->ui->locationsWidget->clear();
    qDebug() << "Populating locations";
    Locations *locations = Locations::GetInstance();

    QStringList locs;
    for (int index = 1; index <= locations->size(); ++index)
    {
        qDebug() << "Adding location: " << locations->getLocation(index)->label();
        Location* loc = locations->getLocation(index);
        QString dispName = loc->label();
        if (!loc->isValid())
            dispName.append(invalidPostText);
        locs << dispName;
    }
    this->ui->locationsWidget->addItems(locs);
    qDebug() << "Locations populated";
}


void LocationsDisplayWindow::editLocation(QListWidgetItem *item)
{
    /// TODO
    /*if (!item) return;

    Locations *locations = Locations::GetInstance();
    QString findText = getLocName(item);
    Location *loc = locations->getLocation(findText);
    if (!loc)
        qDebug() << "No location with label " << findText << " was found from locations.";
    else
    {
        AddressDialog *dialog = new AddressDialog(this, loc);
        dialog->show();
    }*/
}

QString LocationsDisplayWindow::getLocName(const QListWidgetItem *item)
{
    if (!item) return NULL;
    QString retText = item->text();
    if (retText.contains(" - Invalid address", Qt::CaseSensitive))
        retText.chop(18);
    return retText;
}

Location* LocationsDisplayWindow::getSelectedLocation(QList<QListWidgetItem*> list)
{
    if (list.size() == 0)
    {
        qDebug() << "No item is selected";
        return NULL;
    }
    QListWidgetItem *item = list.at(0);
    QString name = getLocName(item);
    qDebug() << "Selected item is" << name;
    Locations *locations = Locations::GetInstance();
    return locations->getLocation(name);
}

void LocationsDisplayWindow::on_newLocButton_clicked()
{
    /// TODO
    /*AddressDialog *dialog = new AddressDialog(this);
    dialog->show();*/
}

void LocationsDisplayWindow::on_upButton_clicked()
{
    qDebug() << "Move up called";
    Location* loc = this->getSelectedLocation(this->ui->locationsWidget->selectedItems());
    if (!loc)
        qDebug() << "No location with selected label was found from locations.";
    else
    {
        Locations *locations = Locations::GetInstance();
        locations->lowerLocationIndex(loc->label());
    }
}

void LocationsDisplayWindow::on_downButton_clicked()
{
    qDebug() << "Move down called";
    Location* loc = this->getSelectedLocation(this->ui->locationsWidget->selectedItems());
    if (!loc)
        qDebug() << "No location with selected label was found from locations.";
    else
    {
        Locations *locations = Locations::GetInstance();
        locations->increaseLocationIndex(loc->label());
    }
}

void LocationsDisplayWindow::on_deleteButton_clicked()
{
    qDebug() << "Remove called";
    Location* loc = this->getSelectedLocation(this->ui->locationsWidget->selectedItems());
    if (!loc)
        qDebug() << "No location with selected label was found from locations.";
    else
    {
        Locations *locations = Locations::GetInstance();
        locations->removeLocation(loc);
    }
}

void LocationsDisplayWindow::on_customizeButton_clicked()
{
    this->ui->buttonsStacked->setCurrentIndex(1);
}

void LocationsDisplayWindow::on_doneButton_clicked()
{
    this->ui->buttonsStacked->setCurrentIndex(0);
}

void LocationsDisplayWindow::on_locationsWidget_itemClicked(QListWidgetItem* item)
{
    if (this->ui->buttonsStacked->currentIndex() == 0)
        this->editLocation(item);
}

void LocationsDisplayWindow::on_locationsWidget_clicked(QModelIndex index){}
