#ifndef LOCATIONFINDER_H
#define LOCATIONFINDER_H

#include <QThread>
#include <QNetworkReply>
#include <QList>
#include <QMutex>
#include <QWaitCondition>
#include "location.h"




class LocationFinder : public QObject
{
    Q_OBJECT
public:
    explicit LocationFinder(QString address, QObject *parent = 0);
    ~LocationFinder();

    bool responseWasValid() const;
    bool locationsFound() const;
    int numberOfLocationsFound() const;
    int numberOfPlaces() const;
    int numberOfRoadNames() const;
    int numberOfStops() const;

    /** The caller of these methods is responsible for deleting the Locations returned by these methods. */
    Location* getPlace(int index) const;
    Location* getRoadName(int index) const;
    Location* getStop(int index) const;

    /** These functions return lists of pointers to Locations.
      The Locations will be deleted after LocationFinder is deleted, so use upper methods to get Locations that will not be deleted with this LocationFinder.*/
    const QList<Location*>& getPlaces() const;
    const QList<Location*>& getRoadNames() const;
    const QList<Location*>& getStops() const;

private slots:
    void processReply();

signals:
    void finished();

private:

    QString address;
    QNetworkReply *reply;
    QList<Location*> places, roadNames, stops;
    bool invalidResponse;
};

#endif // LOCATIONFINDER_H
