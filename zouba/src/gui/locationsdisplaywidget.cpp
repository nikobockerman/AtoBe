#include "locationsdisplaywidget.h"
#include "ui_locationsdisplaywidget.h"

#include "locationmodifydialog.h"
#include "src/logic/locations.h"

#include <QDebug>
#include <QListWidgetItem>
#include <QListWidget>
#include <QList>


const QString invalidPostText = " - Invalid address";
const QString editText = "Edit list";

QString getLocName(const QListWidgetItem *item);
Location* getSelectedLocation(QList<QListWidgetItem*> list);

LocationsDisplayWidget::LocationsDisplayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LocationsDisplayWidget)
{
    ui->setupUi(this);

#ifdef Q_WS_MAEMO_5
    this->setAttribute(Qt::WA_Maemo5StackedWindow);
    this->setWindowFlags(this->windowFlags() | Qt::Window);
    this->setWindowTitle(QCoreApplication::applicationName());
#endif

    this->populateLocations();

    Locations* locations = Locations::GetInstance();
    this->connect(locations, SIGNAL(locationsChanged()), SLOT(populateLocations()));

    //this->ui->buttonsStacked->adjustSize();
    //this->ui->locationsWidget->adjustSize();
}

LocationsDisplayWidget::~LocationsDisplayWidget()
{
    delete ui;
}

void LocationsDisplayWidget::showWidget()
{
    this->ui->buttonsStacked->setCurrentIndex(0);
    this->show();
}

void LocationsDisplayWidget::on_customizeButton_clicked()
{
    this->ui->buttonsStacked->setCurrentIndex(1);
}

void LocationsDisplayWidget::on_locationsWidget_itemClicked(QListWidgetItem* item)
{
    if (this->ui->buttonsStacked->currentIndex() == 0)
        this->editLocation(item);
}

void LocationsDisplayWidget::on_doneButton_clicked()
{
    this->ui->buttonsStacked->setCurrentIndex(0);
}

void LocationsDisplayWidget::on_deleteButton_clicked()
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

void LocationsDisplayWidget::on_downButton_clicked()
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

void LocationsDisplayWidget::on_upButton_clicked()
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

void LocationsDisplayWidget::on_newLocButton_clicked()
{
    LocationModifyDialog *modify = new LocationModifyDialog(this);
    modify->show();
}

void LocationsDisplayWidget::populateLocations()
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


void LocationsDisplayWidget::editLocation(QListWidgetItem *item)
{
    if (!item) return;

    Locations *locations = Locations::GetInstance();
    QString findText = getLocName(item);
    Location *loc = locations->getLocation(findText);
    if (!loc)
        qDebug() << "No location with label " << findText << " was found from locations.";
    else
    {
        LocationModifyDialog *modify = new LocationModifyDialog(this, loc);
        modify->show();
    }
}

QString LocationsDisplayWidget::getLocName(const QListWidgetItem *item)
{
    if (!item) return NULL;
    QString retText = item->text();
    if (retText.contains(" - Invalid address", Qt::CaseSensitive))
        retText.chop(18);
    return retText;
}

Location* LocationsDisplayWidget::getSelectedLocation(QList<QListWidgetItem*> list)
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
