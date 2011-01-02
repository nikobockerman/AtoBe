#include "locationmodifydialog.h"
#include "ui_locationmodifydialog.h"

#include "../logic/locations.h"

#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>

Location* foundFromList(const QString address, const QList<Location*>& list);

LocationModifyDialog::LocationModifyDialog(QWidget *parent, Location *existing) :
    QDialog(parent),
    ui(new Ui::LocationModifyDialog),
    finder(NULL),
    edit(false)
{
    ui->setupUi(this);
    this->ui->result_widget->hide();

    this->setAttribute(Qt::WA_DeleteOnClose);

#ifdef Q_WS_MAEMO_5
    this->setAttribute(Qt::WA_Maemo5AutoOrientation);
    this->setWindowTitle(QCoreApplication::applicationName());
    this->connect(QApplication::desktop(), SIGNAL(resized(int)), SLOT(orientationChanged()));
    this->setFixedHeight(QApplication::desktop()->screenGeometry().height());
#endif

    if (existing)
    {
        this->ui->label_edit->setText(existing->label());
        this->ui->label_edit->setEnabled(false);
        this->ui->address_edit->setText(existing->address());
        this->edit = true;
    }

}

LocationModifyDialog::~LocationModifyDialog()
{
    qDebug() << "Modify dialog Destructor called.";
    delete ui;
    if (this->finder)
        this->finder->deleteLater();
    qDebug() << "Destructor ended.";
}

void LocationModifyDialog::on_search_button_clicked()
{
    if (this->ui->label_edit->text().isEmpty())
    {
        this->ui->result_widget->setCurrentWidget(this->ui->labelEmpty);
        this->ui->result_widget->show();
        return;
    }
    if (!this->edit && Locations::GetInstance()->getLocation(this->ui->label_edit->text().trimmed()))
    {
        this->ui->result_widget->setCurrentWidget(this->ui->labelReserved);
        this->ui->result_widget->show();
        return;
    }
#ifdef Q_WS_MAEMO_5
    this->setAttribute(Qt::WA_Maemo5ShowProgressIndicator, true);
#endif
    this->ui->result_widget->setCurrentWidget(this->ui->searching);
    this->ui->result_widget->show();
    if (this->finder)
    {
        this->finder->disconnect(this);
        this->finder->deleteLater();
        this->finder = NULL;
    }
    this->finder = new LocationFinder(this->ui->address_edit->text().trimmed());
    this->connect(this->finder, SIGNAL(finished()), SLOT(location_search_finished()));
}

void LocationModifyDialog::location_search_finished()
{
    bool delete_finder = false;
    if (!this->finder->responseWasValid())
    {
        this->ui->result_widget->setCurrentWidget(this->ui->invalid_response);
        delete_finder = true;

    }
    else if (this->finder->numberOfLocationsFound() == 0)
    {
        this->ui->result_widget->setCurrentWidget(this->ui->noResults);
        delete_finder = true;
    }
    else
    {
        this->ui->address_list->clear();
        if (this->finder->getPlaces().size() > 0)
        {
            QListWidgetItem *item = new QListWidgetItem("Places", this->ui->address_list);
            item->setFlags(item->flags() & (~Qt::ItemIsEnabled));
            this->populateList(this->finder->getPlaces());
        }
        if (this->finder->getRoadNames().size() > 0)
        {
            QListWidgetItem *item = new QListWidgetItem("Street names", this->ui->address_list);
            item->setFlags(item->flags() & (~Qt::ItemIsEnabled));
            this->populateList(this->finder->getRoadNames());
        }
        if (this->finder->getStops().size() > 0)
        {
            QListWidgetItem *item = new QListWidgetItem("Stops", this->ui->address_list);
            item->setFlags(item->flags() & (~Qt::ItemIsEnabled));
            this->populateList(this->finder->getStops());
        }
        this->ui->result_widget->setCurrentWidget(this->ui->results);
    }

    if (delete_finder)
    {
        this->finder->disconnect(this);
        this->finder->deleteLater();
        this->finder = NULL;
    }
#ifdef Q_WS_MAEMO_5
    this->setAttribute(Qt::WA_Maemo5ShowProgressIndicator, false);
#endif
}

void LocationModifyDialog::populateList(const QList<Location *> &list)
{
    QList<Location*>::const_iterator it, ite;
        for (it = list.constBegin(), ite = list.constEnd(); it != ite; ++it)
        {
            new QListWidgetItem((*it)->address(), this->ui->address_list);
        }
}

void LocationModifyDialog::on_address_list_itemClicked(QListWidgetItem* item)
{
    QString address(item->text());
    Location *location = NULL;
    location = foundFromList(address, this->finder->getPlaces());
    if (!location)
        location = foundFromList(address, this->finder->getRoadNames());
    if (!location)
        location = foundFromList(address, this->finder->getStops());
    if (location)
    {
        qDebug() << "Found location pointer: " << location;
        Location *added = new Location(location->x(), location->y(), this->ui->label_edit->text().trimmed(), location->address());
        Locations::GetInstance()->addEditLocation(added);
        this->close();
    }
}

Location* foundFromList(const QString address, const QList<Location*>& list)
{
    Location* ret = NULL;
    QList<Location*>::const_iterator it, ite;
    for (it = list.constBegin(), ite = list.constEnd(); it != ite && !ret; ++it)
    {
        if (address == (*it)->address())
        {
            ret = *it;
        }
    }
    return ret;
}

void LocationModifyDialog::orientationChanged()
{
    this->setFixedHeight(QApplication::desktop()->screenGeometry().height());
}
