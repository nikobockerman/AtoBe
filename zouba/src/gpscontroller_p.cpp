#include "gpscontroller_p.h"

#include "location.h"

#include <QObject>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>
#include <QDebug>

QTM_USE_NAMESPACE

GpsControllerPrivate::GpsControllerPrivate() :
  m_gps(0),
  m_currentLocation(0),
  m_useFakeLocation(false)
{
}

GpsControllerPrivate::~GpsControllerPrivate()
{
  delete m_gps;
  m_gps = 0;
  delete m_currentLocation;
  m_currentLocation = 0;
}

void GpsControllerPrivate::init()
{
  m_gps = QGeoPositionInfoSource::createDefaultSource(this);
  connect(
      m_gps, SIGNAL( positionUpdated( QGeoPositionInfo ) ),
      this, SLOT( updateLocation( QGeoPositionInfo ) )
  );
}

void GpsControllerPrivate::startGps()
{
  m_gps->startUpdates();
}

void GpsControllerPrivate::stopGps()
{
  m_gps->stopUpdates();
}

QGeoPositionInfoSource *GpsControllerPrivate::gps()
{
  return m_gps;
}

void GpsControllerPrivate::setGps( QGeoPositionInfoSource *gps )
{
  m_gps = gps;
}

Location *GpsControllerPrivate::currentLocation()
{
  return m_currentLocation;
}

void GpsControllerPrivate::setCurrentLocation( Location *location )
{
  delete m_currentLocation;
  m_currentLocation = location;
}

bool GpsControllerPrivate::useFakeLocation()
{
  return m_useFakeLocation;
}

void GpsControllerPrivate::setUseFakeLocation( bool useFake )
{
  m_useFakeLocation = useFake;
}

void GpsControllerPrivate::updateLocation( QGeoPositionInfo positionInfo )
{
  if ( !m_useFakeLocation ) {
    delete m_currentLocation;
    m_currentLocation = new Location( positionInfo );
  }
}

