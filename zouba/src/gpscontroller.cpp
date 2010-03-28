#include "gpscontroller.h"

#include <QObject>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>
#include <QDebug>

QTM_USE_NAMESPACE

GpsController::GpsController() :
  m_location( QGeoPositionInfoSource::createDefaultSource(this) ),
  m_currentLocation(0),
  m_useFakeLocation(false)
{
  connect( 
      m_location, SIGNAL( positionUpdated( QGeoPositionInfo ) ),
      this, SLOT( updateLocation( QGeoPositionInfo ) )
  );

  m_location->startUpdates();
}

GpsController::~GpsController()
{
  delete m_location;
  m_location = 0;
  delete m_currentLocation;
  m_currentLocation = 0;
}

void GpsController::updateLocation( QGeoPositionInfo positionInfo )
{
  delete m_currentLocation;
  m_currentLocation = new Location( positionInfo );
}

void GpsController::getGps()
{
  if ( m_currentLocation != 0 ) {
    emit locationChanged( m_currentLocation );
  }
}

void GpsController::useLiveGps()
{
  m_location->startUpdates();
  m_useFakeLocation=false;
  m_currentLocation=0;
}

void GpsController::useFakeGps( Location *fakeLocation )
{
  m_location->stopUpdates();
  m_useFakeLocation=true;
  delete m_currentLocation;
  m_currentLocation = new Location( *fakeLocation );
  emit locationChanged( m_currentLocation );
}
