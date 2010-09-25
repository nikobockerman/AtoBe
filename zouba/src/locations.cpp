#include "locations.h"
#include "location.h"

#include <QDebug>
#include <QHash>
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QCoreApplication>

Locations* Locations::m_instance = 0;

Locations* Locations::GetInstance()
{
    if (m_instance == 0)
        m_instance = new Locations();

    return m_instance;
}

/*void Locations::destroyLocations()
{
    delete m_instance;
}*/

Locations::Locations() :
        m_locationStorage(QHash<QString,Location *>()),
        m_indexStorage(QHash<QString, int>()),
        m_gpsLocation(new Location("GPS"))
{
    this->restoreLocations();
    qDebug() << "Size of index storage:" << this->m_indexStorage.size();
}

/*Locations::~Locations()
{
    QHash<QString,Location*>::iterator it, ite;
    for (it = this->m_locationStorage.begin(), ite = this->m_locationStorage.end(); it != ite; ++it)
    {
        delete it.value();
    }
    this->m_locationStorage.empty();
    delete m_gpsLocation;
}*/

bool Locations::addEditLocation(Location *location)
{
    bool addedNew=false;

    if ( !this->m_locationStorage.contains(location->label())) {
        qDebug() << "Adding location" << location->label();
        this->m_locationStorage[location->label()] = location;
        qDebug() << "Index storage:";
        qDebug() << this->m_indexStorage;
        qDebug() << "Size of index storage:" << this->m_indexStorage.size();
        this->m_indexStorage.insert(location->label(), this->m_indexStorage.size() + 1);
        qDebug() << "Index storage after inserting location:";
        qDebug() << this->m_indexStorage;
        addedNew = true;
        emit(locationsChanged());
    } else {
        qDebug() << "A location with the same label (" << location->label() << ") already exists.";
        this->m_locationStorage.remove(location->label());
        this->m_locationStorage[location->label()] = location;
    }

    // if it's valid now, save the setting
    if ( location->isValid() ) {
        this->saveLocation(location, this->m_indexStorage.value(location->label()));
    }

    return addedNew;
}

void Locations::restoreLocations()
{
    QSettings settings;

    settings.beginGroup("Locations");
    QStringList labels = settings.childGroups();

    for( int i=0; i<labels.size(); ++i ) {
        QString label = labels[i];
        settings.beginGroup(label);
        QString x       = settings.value( "x" ).toString();
        QString y       = settings.value( "y" ).toString();
        QString address = settings.value( "address" ).toString();
        int index = settings.value("index").toInt();
        settings.endGroup();

        qDebug() << "Restoring " << label;
        Location *location = new Location( x, y, label );
        location->setAddress(address);

        this->m_locationStorage[label] = location;
        this->m_indexStorage.insert(label,this->m_indexStorage.size() + 1);
        if (index != 0)
            this->changeIndex(label, index, false);
    }

    settings.endGroup();
}

void Locations::saveLocation(Location *location, int index)
{
    qDebug() << "Saving location " << location->label();
    QSettings settings;
    settings.beginGroup("Locations");
    settings.beginGroup(location->label() );
    settings.setValue( "address", location->address() );
    settings.setValue( "x", location->x() );
    settings.setValue( "y", location->y() );
    settings.setValue("index", index);
    settings.endGroup();
    settings.endGroup();
}

bool Locations::removeLocation(Location *location)
{
    bool succeeded = false;
    qDebug() << "Trying to remove location " << location->label();
    QSettings settings;
    settings.beginGroup("Locations");
    if (settings.contains(location->label()))
    {
        qDebug() << "Given location exists in settings -> removing it";
        settings.remove(location->label());
        succeeded = true;
        emit(locationsChanged());
    }
    settings.endGroup();

    if (this->m_locationStorage.contains(location->label()))
    {
        qDebug() << "Given location exists in locations list -> removing it";
        this->m_locationStorage.remove(location->label());
        int remIndex = this->m_indexStorage.value(location->label());
        this->m_indexStorage.remove(location->label());
        QHash<QString, int>::iterator it, ite;
        for (it = this->m_indexStorage.begin(), ite = this->m_indexStorage.end(); it != ite; ++it)
        {
            if (it.value() > remIndex)
                it.value() -= 1;
        }
        emit(locationsChanged());
    }
    return succeeded;
}

Location *Locations::getLocation(const QString &label) const
{
    qDebug() << "requesting location " << label;
    Location *retVal = 0;

    if (this->m_locationStorage.contains(label)) {
        qDebug() << "found location " << label;
        retVal = this->m_locationStorage[label];
    } else {
        qDebug() << "didn't find location " << label;
    }

    return retVal;
}

void Locations::changeIndex(const QString &label, const int &index, bool signal)
{
    int oldIndex = this->m_indexStorage.value(label);
    if (index == oldIndex)
        return;

    qDebug() << "Index map before moving " << label << " from index " << oldIndex << " to index " << index;
    qDebug() << this->m_indexStorage;
    QHash<QString, int>::iterator it, ite;
    if (index < oldIndex)
    {
        for (it = this->m_indexStorage.begin(), ite = this->m_indexStorage.end(); it != ite; ++it)
        {
            if (it.value() >= index && it.value() < oldIndex)
            {
                this->saveLocation(this->getLocation(label), ++(it.value()));
            }
        }
    }
    else
        for (it = this->m_indexStorage.begin(), ite = this->m_indexStorage.end(); it != ite; ++it)
            if (it.value() <= index && it.value() > oldIndex)
                this->saveLocation(this->getLocation(label), --(it.value()));

    this->m_indexStorage[label] = index;
    this->saveLocation(this->getLocation(label), index);

    qDebug() << "Index map after move";
    qDebug() << this->m_indexStorage;
    if (signal)
        emit(locationsChanged());
}

Location *Locations::getLocation(const int &index) const
{
    qDebug() << "Getting location for index" << index;
    Location *loc = 0;
    QString label;
    if (this->findLabel(index, label))
    {
        qDebug() << "Found a label with given index " << index;
        qDebug() << "Found label is " << label;
        loc = this->getLocation(label);
    }
    return loc;
}

bool Locations::findLabel(const int &index, QString &label) const
{
    qDebug() << "Finding label for index" << index << ". Number of items in indexStorage:" << this->m_indexStorage.size() << ". Number of items in locationStorage:" << this->m_locationStorage.size();
    qDebug() << "Location storage";
    qDebug() << this->m_locationStorage;
    qDebug() << "Index storage";
    qDebug() << this->m_indexStorage;

    if (index > this->m_indexStorage.size() || index < 1)
        return false;
    bool found = false;
    QHash<QString, int>::const_iterator it, ite;
    for (it = this->m_indexStorage.constBegin(), ite = this->m_indexStorage.constEnd(); it != ite; ++it)
    {
        if (it.value() == index)
        {
            label = it.key();
            qDebug() << "Found label is " << label;
            found = true;
            break;
        }
    }
    qDebug() << "Returning from label search.";
    return found;
}

/*const QHash<QString, Location *>& Locations::getLocations() const
{
    return this->m_locationStorage;
}*/

Location *Locations::getGpsLocation() const
{
    qDebug() << "GPS location requested.";
    return this->m_gpsLocation;
}

bool Locations::increaseLocationIndex(const QString &label)
{
    if (!this->m_indexStorage.contains(label))
        return false;
    qDebug() << "Increasing index by one for label" << label;
    bool done = false;
    int oldIndex = this->m_indexStorage.value(label);
    QString otherLabel;
    if (this->findLabel(oldIndex + 1, otherLabel))
    {
        this->m_indexStorage[label] = oldIndex + 1;
        this->m_indexStorage[otherLabel] = oldIndex;
        done = true;
        emit(locationsChanged());
    }
    return done;
}

bool Locations::lowerLocationIndex(const QString &label)
{
    if (!this->m_indexStorage.contains(label))
        return false;
    qDebug() << "Lowering index by one for label" << label;
    bool done = false;
    int oldIndex = this->m_indexStorage[label];
    QString otherLabel;
    if (this->findLabel(oldIndex - 1, otherLabel))
    {
        this->m_indexStorage[label] = oldIndex - 1;
        this->m_indexStorage[otherLabel] = oldIndex;
        done = true;
        emit(locationsChanged());
    }
    return done;
}

int Locations::size() const
{
    return this->m_locationStorage.size();
}
