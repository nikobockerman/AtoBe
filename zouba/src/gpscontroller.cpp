#include "gpscontroller.h"
#include "gpscontroller_p.h"

#include "locations.h"

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
  Location *location;

  if ( q->useFakeLocation() ) {
    Locations *locations = Locations::instance();
    location = locations->location( q->fakeLocationLabel() );
  } else {
    location = q->liveLocation();
  }

  emit locationChanged( location );
}

void GpsController::useLiveGps()
{
  q->setUseFakeLocation( false );
  q->startGps();
  emit locationChanged( q->liveLocation() );
}

void GpsController::useFakeGps( const QString &fakeLocationLabel )
{
  qDebug() << "using fake gps (" << fakeLocationLabel << ")";

  Locations *locations = Locations::instance();
  Location  *fakeLocation = locations->location( fakeLocationLabel );

  if ( fakeLocation == 0 ) {
    qDebug() << "invalid fake location label; cannot use fake location";
  } else {
    q->stopGps();
    q->setUseFakeLocation( true );
    q->setFakeLocationLabel( fakeLocationLabel );
    emit locationChanged( fakeLocation );
  }
}
