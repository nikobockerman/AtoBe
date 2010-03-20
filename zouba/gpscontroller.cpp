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
  qDebug() << "new GPS position";

  Location newLocation( positionInfo );

  if ( updatesEnabled ) {
    qDebug() << "from location changed";
    emit locationChanged( newLocation );
    updatesEnabled = false;
    m_location->setUpdateInterval( 1*60*1000 );
  }
}

void GpsController::startGps()
{
  updatesEnabled = true;
  m_location->setUpdateInterval( 1 );
}
