#include "gpscontroller.h"
#include "gpscontroller_p.h"

#include <QObject>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>
#include <QDebug>

GpsController::GpsController() :
  q( new GpsControllerPrivate() )
{
  q->init();
  q->startGps();
}

GpsController::GpsController( GpsControllerPrivate *gpsControllerPrivate ) :
  q( gpsControllerPrivate )
{
  q->init();
  q->startGps();
}

GpsController::~GpsController()
{
  delete q;
}

void GpsController::getGps()
{
  if ( q->currentLocation() != 0 ) {
    emit locationChanged( q->currentLocation() );
  }
}

void GpsController::useLiveGps()
{
  q->setUseFakeLocation( false );
  q->setCurrentLocation( new Location( "livegps" ) );
  q->startGps();
}

void GpsController::useFakeGps( Location *fakeLocation )
{
  qDebug() << "using fake gps (" << fakeLocation->label() << ")";
  q->stopGps();
  q->setUseFakeLocation( true );
  q->setCurrentLocation( fakeLocation );
  emit locationChanged( q->currentLocation() );
}
