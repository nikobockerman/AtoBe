#include "gpscontroller_p.h"

#include "location.h"
#include "locations.h"

#include <QObject>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>
#include <QDebug>

QTM_USE_NAMESPACE

GpsControllerPrivate::GpsControllerPrivate() :
  m_gps(0),
  m_liveLocation( new Location( "livegps" ) ),
  m_fakeLocationLabel(),
  m_useFakeLocation(false)
{
}

GpsControllerPrivate::~GpsControllerPrivate()
{
  delete m_gps;
  m_gps = 0;
  delete m_liveLocation;
  m_liveLocation = 0;
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

Location *GpsControllerPrivate::liveLocation()
{
  m_mostRecentlyReportedLocation = m_liveLocation;
  return m_liveLocation;
}

Location *GpsControllerPrivate::fakeLocation()
{
  Locations locations;
  Location  *location = locations.location( fakeLocationLabel() );
  m_mostRecentlyReportedLocation = location;
  return location;
}

QString GpsControllerPrivate::fakeLocationLabel()
{
  return m_fakeLocationLabel;
}

void GpsControllerPrivate::setFakeLocationLabel( const QString &label )
{
  m_fakeLocationLabel = label;
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
  m_liveLocation->setLocation( positionInfo );
}

Location *GpsControllerPrivate::mostRecentlyReportedLocation()
{
  return m_mostRecentlyReportedLocation;
}
