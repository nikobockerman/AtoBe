#ifndef GPSCONTROLLER_H
#define GPSCONTROLLER_H

#include "logic/location.h"

#include <QObject>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>

QTM_USE_NAMESPACE;

class Location;

class GpsController : public QObject
{
    Q_OBJECT

public:
    GpsController(bool started = true);

    ~GpsController();

    QGeoPositionInfoSource *gps() const;
    bool                    isStarted() const;

public Q_SLOTS:
    void useGPS( bool );

Q_SIGNALS:
    void gpsLocationChanged( Location *newLocation );

private Q_SLOTS:
    void updateLocation( QGeoPositionInfo positionInfo );
    void timeoutRequested();

private:
    QGeoPositionInfoSource *m_gps;
    bool                    m_started;
};

#endif // GPSCONTROLLER_H
