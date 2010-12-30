#include "favoriteselectiondialog.h"
#include "ui_favoriteselectiondialog.h"

#include "src/logic/locations.h"

#include <QDebug>

static const QString CUSTOMIZE = "Customize";

FavoriteSelectionDialog::FavoriteSelectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FavoriteSelectionDialog)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_Maemo5AutoOrientation);

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

}

FavoriteSelectionDialog::~FavoriteSelectionDialog()
{
    delete ui;
}

void FavoriteSelectionDialog::on_locations_itemClicked(QListWidgetItem* item)
{
    Locations *locations = Locations::GetInstance();
    Location* selected = locations->getLocation(item->text());
    emit(this->selectedLocation(selected));
    this->deleteLater();
}

void FavoriteSelectionDialog::on_modify_button_clicked()
{
    emit(this->customizeRequested());
    this->deleteLater();
}
