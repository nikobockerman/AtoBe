#ifndef GPSCONTROLLER_P_H
#define GPSCONTROLLER_P_H

#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>

QTM_USE_NAMESPACE

class Location;

class GpsControllerPrivate : public QObject
{
    Q_OBJECT

public:
    GpsControllerPrivate();
    ~GpsControllerPrivate();

    virtual void init();
    virtual void startGps();
    virtual void stopGps();

    virtual void setGps( QGeoPositionInfoSource *gps );
    virtual void setCurrentLocation( Location *location );
    virtual void setUseFakeLocation( bool useFake );

    virtual QGeoPositionInfoSource *gps();
    virtual Location *currentLocation();
    virtual bool useFakeLocation();

private Q_SLOTS:
    virtual void updateLocation( QGeoPositionInfo positionInfo );

private:
    QGeoPositionInfoSource *m_gps;
    Location               *m_currentLocation;
    bool                    m_useFakeLocation;
};

#endif //GPSCONTROLLER_P_H
