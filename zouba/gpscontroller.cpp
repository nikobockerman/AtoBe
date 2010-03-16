#include "gpscontroller.h"

#include <QObject>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>
#include <QDebug>

QTM_USE_NAMESPACE

GpsController::~GpsController()
{
  qDebug() << __PRETTY_FUNCTION__;
  delete m_location;
  m_location = 0;
}

GpsController::GpsController() :
  m_location( QGeoPositionInfoSource::createDefaultSource(this) )
{
  qDebug() << __PRETTY_FUNCTION__;
  m_location->setUpdateInterval( 1*60*1000 );

  connect( 
      m_location, SIGNAL( positionUpdated( QGeoPositionInfo ) ),
      this, SLOT( updateLocation( QGeoPositionInfo ) )
      );

  m_location->stopUpdates();
}

void GpsController::updateLocation( QGeoPositionInfo positionInfo )
{
  qDebug() << __PRETTY_FUNCTION__;
  Location newLocation( positionInfo );

  emit locationChanged( newLocation );
  m_location->stopUpdates();
}

void GpsController::startGps()
{
  qDebug() << __PRETTY_FUNCTION__;
  m_location->startUpdates();
}
