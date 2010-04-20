#include <QObject>
#include <QtDebug>
#include "ut_gpscontroller.h"

#include "gpscontroller.h"
#include "gpscontroller_p.h"

class MyGpsControllerPrivate: public GpsControllerPrivate
{
public:
  MyGpsControllerPrivate();
  ~MyGpsControllerPrivate();

  void init();
  void startGps();
  void stopGps();

  void setGps( QGeoPositionInfoSource *gps );
  void setFakeLocationLabel( const QString &label );
  void setUseFakeLocation( bool useFake );
  void updateLocation();

  QGeoPositionInfoSource *gps();
  Location               *liveLocation();
  Location               *fakeLocation();
  bool                    useFakeLocation();

  bool                    m_gpsOn;
  Location               *m_liveLocation;
  Location               *m_fakeLocation;
  QString                 m_fakeLocationLabel;
  bool                    m_useFakeLocation;
};

MyGpsControllerPrivate::MyGpsControllerPrivate() :
  m_gpsOn(false),
  m_liveLocation( new Location( "livegps" ) ),
  m_fakeLocation( new Location( "fakegps" ) ),
  m_fakeLocationLabel(),
  m_useFakeLocation(false)
{
}

MyGpsControllerPrivate::~MyGpsControllerPrivate()
{
  delete m_liveLocation;
  m_liveLocation = 0;
  delete m_fakeLocation;
  m_fakeLocation = 0;
}

void MyGpsControllerPrivate::init()
{
}

void MyGpsControllerPrivate::startGps()
{
  m_gpsOn=true;
}

void MyGpsControllerPrivate::stopGps()
{
  m_gpsOn=false;
}

QGeoPositionInfoSource *MyGpsControllerPrivate::gps()
{
  return 0;
}

void MyGpsControllerPrivate::setGps( QGeoPositionInfoSource *gps )
{
  Q_UNUSED( gps );
}

Location *MyGpsControllerPrivate::liveLocation()
{
  return m_liveLocation;
}

Location *MyGpsControllerPrivate::fakeLocation()
{
  return m_fakeLocation;
}

void MyGpsControllerPrivate::setFakeLocationLabel( const QString &label )
{
  m_fakeLocationLabel = label;
  m_fakeLocation->setLabel( label );
}

bool MyGpsControllerPrivate::useFakeLocation()
{
  return m_useFakeLocation;
}

void MyGpsControllerPrivate::setUseFakeLocation( bool useFake )
{
  m_useFakeLocation = useFake;
}

void MyGpsControllerPrivate::updateLocation()
{
}

void Ut_GpsController::init()
{
  qRegisterMetaType<Location *>( "Location*" );

  m_subject_p = new MyGpsControllerPrivate();
  m_subject = new GpsController( m_subject_p ); // private ownership transferred
}

void Ut_GpsController::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_GpsController::initTestCase()
{
}

void Ut_GpsController::cleanupTestCase()
{
}

void Ut_GpsController::testGetGpsWithNoGpsUpdates()
{
  QSignalSpy spy(m_subject, SIGNAL(locationChanged(Location*)));

  // this should start the gps,
  // one signal to invalidate the previous display
  // (which could be showing fake results, for example
  m_subject->getGps();

  QCOMPARE(m_subject_p->m_gpsOn, true);
  QCOMPARE(spy.count(), 1);
}

void Ut_GpsController::testGetGpsWithGpsUpdates()
{
  QSignalSpy spy(m_subject, SIGNAL(locationChanged(Location*)));

  // make test call
  m_subject->getGps();

  // check effect
  QCOMPARE(m_subject_p->m_gpsOn, true);
  QCOMPARE(spy.count(), 1);
  QList<QVariant> arguments = spy.takeFirst();
  QCOMPARE(arguments.at(0).value<Location*>(), m_subject_p->m_liveLocation);
}

void Ut_GpsController::testFakeGps()
{
  QSignalSpy spy(m_subject, SIGNAL(locationChanged(Location*)));

  Location *gpsLocation = m_subject_p->m_liveLocation; // position from GPS

  // make test call
  m_subject->useFakeGps( "fakegps" );
  m_subject->getGps();

  // check effect
  QList<QVariant> arguments;

  // gps should be off
  QCOMPARE(m_subject_p->m_gpsOn, false);

  // should get two signals, one from useFakeGps() and one from getGps()
  QVERIFY2(spy.count()==2, "Should receive two signals" );

  // both args should be the fake gps position supplied to useFakeGps()
  arguments = spy.takeFirst();
  QCOMPARE( arguments.at(0).value<Location*>(), m_subject_p->m_fakeLocation );
  QCOMPARE( arguments.at(0).value<Location*>()->label(), QString( "fakegps" ) );
  arguments = spy.takeFirst();
  QCOMPARE( arguments.at(0).value<Location*>(), m_subject_p->m_fakeLocation );
  QCOMPARE( arguments.at(0).value<Location*>()->label(), QString( "fakegps" ) );

  // switch back to GPS
  m_subject->useLiveGps();
  m_subject->getGps();

  // gps should be on
  QCOMPARE(m_subject_p->m_gpsOn, true);

  QVERIFY2(spy.count()==2, "should get two locationChanged signals" );
  arguments = spy.takeFirst();
  QCOMPARE(arguments.at(0).value<Location*>(), m_subject_p->m_liveLocation);
  QCOMPARE( arguments.at(0).value<Location*>()->label(), QString( "livegps" ) );
  arguments = spy.takeFirst();
  QCOMPARE(arguments.at(0).value<Location*>(), m_subject_p->m_liveLocation);
  QCOMPARE( arguments.at(0).value<Location*>()->label(), QString( "livegps" ) );

  // get GPS location
  m_subject->getGps();

  // check effect
  QCOMPARE(spy.count(), 1);
  arguments = spy.takeFirst();
  QCOMPARE(arguments.at(0).value<Location*>(), m_subject_p->m_liveLocation);
  QCOMPARE( arguments.at(0).value<Location*>()->label(), QString( "livegps" ) );
}

void Ut_GpsController::testLiveToFakeToLive()
{
  m_subject_p->updateLocation(); // pretend GPS has given an update

  m_subject->useFakeGps( "fakegps" );
  m_subject->getGps();

  // switch back to live GPS
  m_subject->useLiveGps();
  m_subject->getGps();

  m_subject->useFakeGps( "fakegps" );
  m_subject->getGps();
}

QTEST_APPLESS_MAIN(Ut_GpsController)
