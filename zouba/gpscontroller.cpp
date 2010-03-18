#include "gpscontroller.h"

#include <QObject>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>
#include <QDebug>

QTM_USE_NAMESPACE

GpsController::GpsController() :
  m_location( QGeoPositionInfoSource::createDefaultSource(this) ),
  updatesEnabled(false)
{
  m_location->setUpdateInterval( 1*60*1000 );

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
}

void GpsController::updateLocation( QGeoPositionInfo positionInfo )
{
  Location newLocation( positionInfo );

  if ( updatesEnabled ) {
    emit locationChanged( newLocation );
    updatesEnabled = false;
  }
}

void GpsController::startGps()
{
  updatesEnabled = true;
}
