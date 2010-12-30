#include "addressdialog.h"
#include "logic/location.h"
#include "logic/ytv.h"
#include "logic/locations.h"

#include <QWidget>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QXmlStreamReader>
#include <QListWidget>
#include <QDebug>
#ifdef Q_WS_MAEMO_5
#include <QMaemo5InformationBox>
#endif

AddressDialog::AddressDialog(QWidget *parent, const Location *location) :
    QDialog(parent), m_reply(0), m_current(0)
{
    QHBoxLayout *layout = new QHBoxLayout();
    this->setLayout(layout);
    QFormLayout *editLayout = new QFormLayout();
    layout->addLayout(editLayout);
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    layout->addLayout(buttonLayout);

    this->m_label = new QLineEdit();
    this->m_address = new QLineEdit();
    connect(this->m_address, SIGNAL(textEdited(const QString&)), this, SLOT(typedInAddress()));

    editLayout->addRow("Name", this->m_label);
    editLayout->addRow("Address", this->m_address);

    this->m_addButton = new QPushButton("Add", this);
    buttonLayout->addWidget(this->m_addButton);
    connect(this->m_addButton, SIGNAL(clicked()), this, SLOT(addLocation()));
    QPushButton *searchButton = new QPushButton("Search", this);
    buttonLayout->addWidget(searchButton);
    connect(searchButton, SIGNAL(clicked()), this, SLOT(searchAddress()));

    // Set dialog as edit dialog if given location is not null.
    if (location)
    {
        this->m_label->setText(location->label());
        this->m_label->setEnabled(false);
        this->m_address->setText(location->address());
        //this->m_current = location;
        this->m_addButton->setText("Edit");
    }
    
    // Always set add button to disabled when creating new layout.
    this->m_addButton->setEnabled(false);
}

void AddressDialog::searchAddress()
{
    emit(busy(true));
    this->m_reply = Ytv::searchAddress(m_address->text());
    connect(m_reply, SIGNAL(finished()), this, SLOT(searchFinished()));
}

void AddressDialog::searchFinished()
{
    qDebug() << "Parsing following xml:";
    QXmlStreamReader xml(this->m_reply->readAll());
    //Remove the reply. Hopefully also removes the connection.
    //delete this->m_reply;
    this->m_reply->deleteLater();
    
    bool responseHasError = false;
    this->m_places = QList<Location*>();
    this->m_roadNames = QList<Location*>();
    this->m_stops = QList<Location*>();

    while (!xml.atEnd())
    {
        qDebug() << "Reading next element";
        xml.readNext();

        if (xml.isStartElement())
        {
            QString xmlName(xml.name().toString());

            if (xmlName == "LOC")
            {
                QXmlStreamAttributes attributes(xml.attributes());
                QStringRef xAttribute( attributes.value("x") );
                QStringRef yAttribute( attributes.value("y") );
                QString newX( xAttribute.toString() );
                QString newY( yAttribute.toString() );
                QString category(attributes.value("category").toString());
                QString name(attributes.value("name1").toString());
                QString number(attributes.value("number").toString());
                if (!number.isEmpty())
                {
                    name.append(" ");
                    name.append(number);
                }
                name.append(", ");
                name.append(attributes.value("city").toString());

                if (category == "poi")
                {
                    m_places.append(new Location(newX, newY, name));
                }
                else if (category == "street")
                {
                    m_roadNames.append(new Location(newX, newY, name));
                }
                else if (category == "stop")
                {
                    m_stops.append(new Location(newX, newY, name));
                }
                else
                {
                    QString errorMessage("Unknown category: ");
                    errorMessage.append(category);
                    qDebug() << errorMessage;
#ifdef Q_WS_MAEMO_5
                    QMaemo5InformationBox::information(this, errorMessage);
#endif
                }
            }

            if (xmlName == "ERROR") {
                responseHasError = true;
            }

        }
    }

    emit(busy(false));

    qDebug() << xml.errorString();
    if ( xml.hasError() || responseHasError ) {
#ifdef Q_WS_MAEMO_5
        QMaemo5InformationBox::information(this, "Invalid response received from Ytv.");
#endif
        qDebug() << "Invalid response received from Ytv";
    } else {
        // Case where no addresses are found.
        if (m_places.size() + m_roadNames.size() + m_stops.size() == 0)
        {
#ifdef Q_WS_MAEMO_5
            QMaemo5InformationBox::information(this, "No addresses were found with the given address.");
#endif
        }
        // Case where addresses are found.
        else        {
            qDebug() << "Starting selection dialog";
            AddressDialogSelection *selection = new AddressDialogSelection(this->m_places, this->m_roadNames, this->m_stops, this);
            connect(selection, SIGNAL(locationSelected(Location*)), this, SLOT(locationSelected(Location*)));
            selection->show();
        }
    }
    //delete m_reply;
    qDebug() << "Exiting xml parsing.";
}

void AddressDialog::typedInAddress()
{
    qDebug() << "Typed in address field signal detected.";
    if (this->m_current != 0)
    {
        qDebug() << "Setting add button disabled and deleting current location.";
        this->m_addButton->setEnabled(false);
        delete this->m_current;
        this->m_current = 0;
    }
}

void AddressDialog::addLocation()
{
    this->m_current->setAddress(this->m_current->label());
    this->m_current->setLabel(this->m_label->text());
    Locations::GetInstance()->addEditLocation(this->m_current);
    this->close();
}

void AddressDialog::locationSelected(Location* location)
{
    qDebug() << "Location selected and signal received. Setting add button enabled and correct text.";
    if (location == 0)
        qDebug() << "Null pointer received.";
    this->m_current = location;
    this->m_address->setText(this->m_current->label());
    this->m_addButton->setEnabled(true);
}






void populateList(QListWidget *widget, const QList<Location*>& list);

AddressDialogSelection::AddressDialogSelection(const QList<Location*> &places, const QList<Location*> &roads, const QList<Location*> &stops, QWidget *parent) :
        QDialog(parent),
        m_places(places),
        m_roads(roads),
        m_stops(stops)
{
    QVBoxLayout *layout = new QVBoxLayout();
    this->setLayout(layout);
    QListWidget *list = new QListWidget(this);
    layout->addWidget(list);
    connect(list, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(itemSelected(QListWidgetItem*)));
    if (this->m_places.size() > 0)
    {
        QListWidgetItem *item = new QListWidgetItem("Places", list);
        item->setFlags(item->flags() & (~Qt::ItemIsEnabled));
        populateList(list, m_places);
    }

    if (m_roads.size() > 0)
    {
        QListWidgetItem *item = new QListWidgetItem("Street names", list);
        item->setFlags(item->flags() & (~Qt::ItemIsEnabled));
        populateList(list, m_roads);
    }

    if (m_stops.size() > 0)
    {
        QListWidgetItem *item = new QListWidgetItem("Stops", list);
        item->setFlags(item->flags() & (~Qt::ItemIsEnabled));
        populateList(list, m_stops);
    }

}

void populateList(QListWidget *widget, const QList<Location*>& list)
{
    QList<Location*>::const_iterator it, ite;
    for (it = list.constBegin(), ite = list.constEnd(); it != ite; ++it)
    {
        new QListWidgetItem((*it)->label(), widget);
    }
}


Location* foundFromList(const QString address, const QList<Location*>& list);

void AddressDialogSelection::itemSelected(QListWidgetItem *item)
{
    qDebug() << "Item selected";
    QString address = item->text();
    Location *location = 0;
    location = foundFromList(address, this->m_places);
    if (!location)
        location = foundFromList(address, this->m_roads);
    if (!location)
        location = foundFromList(address, this->m_stops);
    if (location)
    {
        qDebug() << "Found location pointer: " << location;
        emit(locationSelected(location));
        this->close();
    }
}

Location* foundFromList(const QString address, const QList<Location*>& list)
{
    Location* ret = 0;
    QList<Location*>::const_iterator it, ite;
    for (it = list.constBegin(), ite = list.constEnd(); it != ite && !ret; ++it)
    {
        if (address == (*it)->label())
        {
            qDebug() << "Found item from list: " << *it;
            ret = new Location(**it);
            qDebug() << "After assignment: " << ret;
        }
    }
    return ret;
}
