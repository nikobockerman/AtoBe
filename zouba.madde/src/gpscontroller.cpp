#include "gpscontroller.h"

#include <QObject>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>
#include <QDebug>

QTM_USE_NAMESPACE

GpsController::GpsController() :
  m_location( QGeoPositionInfoSource::createDefaultSource(this) ),
  currentLocation(0)
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
  delete currentLocation;
  currentLocation = 0;
}

void GpsController::updateLocation( QGeoPositionInfo positionInfo )
{
  delete currentLocation;
  currentLocation = new Location( positionInfo );
}

void GpsController::getGps()
{
  if ( currentLocation != 0 ) {
    emit locationChanged( currentLocation );
  }
}
