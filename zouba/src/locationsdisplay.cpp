#include <QPushButton>
#include <QVBoxLayout>
#include <QMaemo5EditBar>
#include <QListWidget>
#include <QHash>
#include <QDebug>
#include <QListWidgetItem>
#include <QPoint>
#include <QMenu>
#include <QMaemo5EditBar>
#include <QMenuBar>
#include <QAction>
#include <QWidget>

#include "locationsdisplay.h"
#include "locations.h"
#include "addressdialog.h"


LocationsDisplay::LocationsDisplay(QWidget *parent) :
        QMainWindow(parent)
{
    this->setAttribute(Qt::WA_Maemo5StackedWindow);
    this->setWindowFlags(this->windowFlags() | Qt::Window);

    QMenuBar *menu = this->menuBar();
    QAction *editListAction = new QAction("Edit list", menu);
    menu->addAction(editListAction);
    connect(editListAction, SIGNAL(triggered()), this, SLOT(showEditOptions()));

    this->m_centralWidget = new QWidget(this);
    this->setCentralWidget(this->m_centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(this->m_centralWidget);
    this->m_centralWidget->setLayout(layout);

    this->m_topWidget = new QWidget(this->m_centralWidget);
    layout->addWidget(this->m_topWidget);
    QVBoxLayout *topLayout = new QVBoxLayout(this->m_topWidget);
    this->m_topWidget->setLayout(topLayout);
    this->m_addButton = new QPushButton("Add new location", this->m_topWidget);
    connect(this->m_addButton, SIGNAL(clicked()), this, SLOT(addAddress()));
    topLayout->addWidget(this->m_addButton);

    this->m_list = new QListWidget(this->m_centralWidget);
    connect(this->m_list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(editLocation(QListWidgetItem*)));
    //this->m_list->setContextMenuPolicy(Qt::CustomContextMenu);
    //connect(this->m_list, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenu(const QPoint&)));
    layout->addWidget(this->m_list);

    this->populateLocations();

    this->m_bottomWidget = new QWidget(this->m_centralWidget);
    layout->addWidget(this->m_bottomWidget);
    QHBoxLayout *bottomLayout = new QHBoxLayout(this->m_bottomWidget);
    this->m_bottomWidget->setLayout(bottomLayout);
    QPushButton *removeButton = new QPushButton("Remove", this->m_bottomWidget);
    connect(removeButton, SIGNAL(clicked()), this, SLOT(remove()));
    bottomLayout->addWidget(removeButton);
    QPushButton *doneButton = new QPushButton("Done", this->m_bottomWidget);
    connect(doneButton, SIGNAL(clicked()), this, SLOT(closeEditOptions()));
    bottomLayout->addWidget(doneButton);
    this->m_bottomWidget->hide();

    Locations *locations = Locations::GetInstance();
    connect(locations, SIGNAL(locationsChanged()), this, SLOT(populateLocations()));
}

void LocationsDisplay::populateLocations()
{
    m_list->clear();
    qDebug() << "Populating locations";
    Locations *locations = Locations::GetInstance();

    for (int index = 1; index <= locations->size(); ++index)
    {
        qDebug() << "Adding location: " << locations->getLocation(index)->label();
        new QListWidgetItem(locations->getLocation(index)->label(), m_list);
    }
    qDebug() << "Locations populated";
}

void LocationsDisplay::addAddress()
{
    AddressDialog *dialog = new AddressDialog(this);
    dialog->show();
}

void LocationsDisplay::editLocation(QListWidgetItem *item)
{
    Locations *locations = Locations::GetInstance();
    Location *loc = locations->getLocation(item->text());
    if (!loc)
        qDebug() << "No location with label " << item->text() << " was found from locations.";
    else
    {
        AddressDialog *dialog = new AddressDialog(this, loc);
        dialog->show();
    }
}

void LocationsDisplay::contextMenu(const QPoint &point)
{
    qDebug() << "ContextMenu requested";
    this->m_point = point;
    QMenu *menu = new QMenu(this->m_list);
    menu->addAction("Delete", this, SLOT(remove()));
    menu->exec(this->mapToGlobal(point));
}

void LocationsDisplay::remove()
{
    qDebug() << "Remove called";
    QList<QListWidgetItem*> list = this->m_list->selectedItems();
    if (list.size() == 0)
    {
        qDebug() << "No item is selected";
        return;
    }
    QListWidgetItem *item = list.at(0);
    qDebug() << "Selected item is" << item->text();
    Locations *locations = Locations::GetInstance();
    locations->removeLocation(locations->getLocation(item->text()));
}

void LocationsDisplay::showEditOptions()
{
    disconnect(this->m_list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(editLocation(QListWidgetItem*)));
    this->m_topWidget->hide();
    this->m_bottomWidget->show();
}

void LocationsDisplay::closeEditOptions()
{
    connect(this->m_list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(editLocation(QListWidgetItem*)));
    this->m_topWidget->show();
    this->m_bottomWidget->hide();
}
