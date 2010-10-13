#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>
#include <QHash>
#include <QDebug>
#include <QListWidgetItem>
#include <QPoint>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QWidget>
#ifdef Q_WS_MAEMO_5
#include <QMaemo5EditBar>
#endif

#include "locationsdisplay.h"
#include "locations.h"
#include "addressdialog.h"

const QString invalidPostText = " - Invalid address";
const QString editText = "Edit list";
const QString newLocText = "Add new location";
const QString removeText = "Remove";
const QString doneText = "Done";
const QString moveUpText = "Move up";
const QString moveDownText = "Move down";

QString getLocName(const QListWidgetItem *item);
Location* getSelectedLocation(QList<QListWidgetItem*> list);

LocationsDisplay::LocationsDisplay(QWidget *parent) :
        QMainWindow(parent)
{
#ifdef Q_WS_MAEMO_5
    this->setAttribute(Qt::WA_Maemo5StackedWindow);
    //this->setWindowFlags(this->windowFlags() | Qt::Window);
#endif

    QMenuBar *menu = this->menuBar();
    QAction *editListAction = new QAction(editText, menu);
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
    this->m_addButton = new QPushButton(newLocText, this->m_topWidget);
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
    QPushButton *removeButton = new QPushButton(removeText, this->m_bottomWidget);
    connect(removeButton, SIGNAL(clicked()), this, SLOT(remove()));
    bottomLayout->addWidget(removeButton);
    QPushButton *moveUpButton = new QPushButton(moveUpText, this->m_bottomWidget);
    connect(moveUpButton, SIGNAL(clicked()), this, SLOT(moveUp()));
    bottomLayout->addWidget(moveUpButton);
    QPushButton *moveDownButton = new QPushButton(moveDownText, this->m_bottomWidget);
    connect(moveDownButton, SIGNAL(clicked()), this, SLOT(moveDown()));
    bottomLayout->addWidget(moveDownButton);

    QPushButton *doneButton = new QPushButton(doneText, this->m_bottomWidget);
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
        Location* loc = locations->getLocation(index);
        QString dispName = loc->label();
        if (!loc->isValid())
            dispName.append(invalidPostText);
        new QListWidgetItem(dispName, m_list);
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

QString getLocNameold(const QListWidgetItem *item)
{
    if (!item) return 0;
    QString retText = item->text();
    if (retText.contains(" - Invalid address", Qt::CaseSensitive))
        retText.chop(18);
    return retText;
}

/*void LocationsDisplay::contextMenu(const QPoint &point)
{
    qDebug() << "ContextMenu requested";
    this->m_point = point;
    QMenu *menu = new QMenu(this->m_list);
    menu->addAction("Delete", this, SLOT(remove()));
    menu->exec(this->mapToGlobal(point));
}*/

void LocationsDisplay::remove()
{
    qDebug() << "Remove called";
    Location* loc = getSelectedLocation(this->m_list->selectedItems());
    if (!loc)
        qDebug() << "No location with selected label was found from locations.";
    else
    {
        Locations *locations = Locations::GetInstance();
        locations->removeLocation(loc);
    }
}

Location* getSelectedLocationold(QList<QListWidgetItem*> list)
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

void LocationsDisplay::moveUp()
{
    qDebug() << "Move up called";
    Location* loc = getSelectedLocation(this->m_list->selectedItems());
    if (!loc)
        qDebug() << "No location with selected label was found from locations.";
    else
    {
        Locations *locations = Locations::GetInstance();
        locations->lowerLocationIndex(loc->label());
    }
}

void LocationsDisplay::moveDown()
{
    qDebug() << "Move down called";
    Location* loc = getSelectedLocation(this->m_list->selectedItems());
    if (!loc)
        qDebug() << "No location with selected label was found from locations.";
    else
    {
        Locations *locations = Locations::GetInstance();
        locations->increaseLocationIndex(loc->label());
    }
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
