#include "favoriteselectiondialog.h"
#include "ui_favoriteselectiondialog.h"

#include "src/logic/locations.h"

#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>

static const QString CUSTOMIZE = "Customize";

FavoriteSelectionDialog::FavoriteSelectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FavoriteSelectionDialog)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_Maemo5AutoOrientation);
    this->setAttribute(Qt::WA_DeleteOnClose);

    Locations* locations = Locations::GetInstance();

    QStringList locs;
    for (int index = 1; index <= locations->size(); ++index)
    {
        Location* loc = locations->getLocation(index);
        if (loc && loc->isValid())
        {
            qDebug() << "Adding location to display: " << loc->label();
            locs << loc->label();
        }
    }
    this->ui->locations->addItems(locs);


    if (!locations->getGpsLocation()->isUpdating())
        this->ui->gps_button->setEnabled(false);
    else if (!locations->getGpsLocation()->isValid())
    {
        this->ui->gps_button->setEnabled(false);
        this->m_text = this->ui->gps_button->text();
        this->ui->gps_button->setText(this->m_text + " (Searching...)");
        this->connect(locations->getGpsLocation(), SIGNAL(gpsLocationChanged(GpsLocation*)), SLOT(gps_location_retrieved()));
    }

    connect(QApplication::desktop(), SIGNAL(resized(int)), this, SLOT(orientationChanged()));
    this->setFixedHeight(QApplication::desktop()->screenGeometry().height());

    //this->connect(locations->getGpsLocation(), SIGNAL(gpsLocationUpdatingChanged(bool)), SLOT(gps_updating_changed(bool)));

}

FavoriteSelectionDialog::~FavoriteSelectionDialog()
{
    delete ui;
}

void FavoriteSelectionDialog::gps_updating_changed(bool isActive)
{
    //this->ui->gps_button->setEnabled(isActive);
}

void FavoriteSelectionDialog::gps_location_retrieved()
{
    this->ui->gps_button->setEnabled(true);
    this->ui->gps_button->setText(this->m_text);
    this->disconnect(this, SLOT(gps_location_retrieved()));
}

void FavoriteSelectionDialog::on_locations_itemClicked(QListWidgetItem* item)
{
    Locations *locations = Locations::GetInstance();
    Location* selected = locations->getLocation(item->text());
    emit(this->selectedLocation(selected));
    this->close();
}

void FavoriteSelectionDialog::on_modify_button_clicked()
{
    emit(this->customizeRequested());
    this->close();
}

void FavoriteSelectionDialog::on_gps_button_clicked()
{
    Locations *locations = Locations::GetInstance();
    emit(this->selectedLocation(locations->getGpsLocation()));
    this->close();
}

void FavoriteSelectionDialog::orientationChanged()
{
    this->setFixedHeight(QApplication::desktop()->screenGeometry().height());
}
