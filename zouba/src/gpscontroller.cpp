#include "gpscontroller.h"
#include "logic/locations.h"

#include <QObject>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>
#include <QDebug>

GpsController::GpsController(bool started) :
        m_gps(QGeoPositionInfoSource::createDefaultSource(this)),
        m_started(started)
{   
    m_gps->setUpdateInterval(20000);
    connect(m_gps, SIGNAL(positionUpdated(QGeoPositionInfo)),
            this, SLOT(updateLocation(QGeoPositionInfo)));
    connect(m_gps, SIGNAL(updateTimeout()),
            this, SLOT(timeoutRequested()));
    if (m_started) m_gps->startUpdates();
}

GpsController::~GpsController()
{
    delete m_gps;
}

void GpsController::useGPS( bool use)
{
    if (use) m_gps->startUpdates();
    else m_gps->stopUpdates();
}

bool GpsController::isStarted() const
{
    return m_started;
}

QGeoPositionInfoSource *GpsController::gps() const
{
    return m_gps;
}

void GpsController::updateLocation( QGeoPositionInfo positionInfo )
{
    qDebug() << "GPS location update received";
    Locations *locations = Locations::GetInstance();

    //DEBUG
    /*if (locations == 0)
        qDebug() << "Null locations received from getInstance";
    else
        qDebug() << "Locations is not null";
    Location* gpsLoc = locations->getGpsLocation();
    if (gpsLoc == 0)
        qDebug() << "Null gpsLocation received from locations";
    else
        qDebug() << "GPS location is not null.";*/
    //DEBUG ENDED

    locations->getGpsLocation()->setLocation(positionInfo);
    //emit(gpsLocationChanged(m_location));
}

void GpsController::timeoutRequested()
{
    qDebug() << "GPS sent timeout requested.";
}
