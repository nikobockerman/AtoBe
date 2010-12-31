#ifndef LOCATIONS_H
#define LOCATIONS_H

#include "location.h"
#include "gpslocation.h"

#include <QHash>
#include <QList>
#include <QString>
#include <QObject>

class Locations: public QObject
{
    Q_OBJECT

public:
    static Locations *GetInstance();
    //static void destroyLocations();

    bool addEditLocation(Location *location);
    bool removeLocation(Location *location);

    bool increaseLocationIndex(const QString &label);
    bool lowerLocationIndex(const QString &label);

    Location *getLocation(const QString &label) const;
    Location *getLocation(const int&) const;
    GpsLocation *getGpsLocation() const;
    int size() const;

    //const QHash<QString, Location *>& getLocations() const;

signals:
    void locationsChanged();

private:
    Locations();
    //~Locations();
    Locations(const Locations&);
    void operator=(const Locations&);

    void restoreLocations();
    void saveLocation(Location *location);
    bool findLabel(const int &index, QString &label) const;
    void changeIndex(const QString &label, const int &index, bool signal = true);

    QHash<QString, Location*> m_locationStorage;
    QList<QString> m_indexStorage;
    GpsLocation* m_gpsLocation;

    static Locations *m_instance;
};
#endif // LOCATIONS_H
