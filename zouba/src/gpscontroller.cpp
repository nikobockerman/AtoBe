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
  Location *location;
  Location *previousLocation = q->mostRecentlyReportedLocation();

  if ( q->useFakeLocation() ) {
    location = q->fakeLocation();
  } else {
    location = q->liveLocation();
  }

  if ( location != previousLocation ) {
    emit locationChanged( location );
  }
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

  q->setFakeLocationLabel( fakeLocationLabel );
  Location  *fakeLocation = q->fakeLocation();

  if ( fakeLocation == 0 ) {
    qDebug() << "invalid fake location label; cannot use fake location";
  } else {
    q->stopGps();
    q->setUseFakeLocation( true );
    emit locationChanged( fakeLocation );
  }
}
