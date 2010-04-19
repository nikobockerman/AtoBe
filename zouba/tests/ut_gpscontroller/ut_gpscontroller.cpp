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
  void setCurrentLocation( Location *location );
  void setUseFakeLocation( bool useFake );
  void updateLocation();

  QGeoPositionInfoSource *gps();
  Location               *currentLocation();
  bool                    useFakeLocation();

  bool                    m_gpsOn;
  Location               *m_currentLocation;
  bool                    m_useFakeLocation;
};

MyGpsControllerPrivate::MyGpsControllerPrivate() :
  m_gpsOn(false),
  m_currentLocation(0),
  m_useFakeLocation(false)
{
}

MyGpsControllerPrivate::~MyGpsControllerPrivate()
{
  delete m_currentLocation;
  m_currentLocation=0;
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

Location *MyGpsControllerPrivate::currentLocation()
{
  return m_currentLocation;
}

void MyGpsControllerPrivate::setCurrentLocation( Location *location )
{
  m_currentLocation = location;
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
  if ( m_currentLocation && m_currentLocation->label() == "livegps" ) {
    delete m_currentLocation;
  }
  m_currentLocation = new Location( "livegps" );
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
  // but since there's been no update from the GPS, there should be
  // no signal
  m_subject->getGps();

  QCOMPARE(m_subject_p->m_gpsOn, true);
  QCOMPARE(spy.count(), 0);
}

void Ut_GpsController::testGetGpsWithGpsUpdates()
{
  QSignalSpy spy(m_subject, SIGNAL(locationChanged(Location*)));

  m_subject_p->updateLocation(); // pretend GPS has given an update

  // make test call
  m_subject->getGps();

  // check effect
  QCOMPARE(m_subject_p->m_gpsOn, true);
  QCOMPARE(spy.count(), 1);
  QList<QVariant> arguments = spy.takeFirst();
  QCOMPARE(arguments.at(0).value<Location*>(), m_subject_p->m_currentLocation);
  QVERIFY(m_subject_p->m_currentLocation != 0);
}

void Ut_GpsController::testFakeGps()
{
  QSignalSpy spy(m_subject, SIGNAL(locationChanged(Location*)));

  m_subject_p->updateLocation(); // pretend GPS has given an update
  Location *gpsLocation = m_subject_p->m_currentLocation; // position from GPS
  Location *fakeLocation = new Location("fakegps");

  // make test call
  m_subject->useFakeGps( fakeLocation ); // ownership -> m_subject
  m_subject->getGps();

  // check effect
  QList<QVariant> arguments;

  // gps should be off
  QCOMPARE(m_subject_p->m_gpsOn, false);

  // should get two signals, one from useFakeGps() and one from getGps()
  QVERIFY2(spy.count()==2, "Should receive two signals" );

  // both args should be the fake gps position supplied to useFakeGps()
  arguments = spy.takeFirst();
  QCOMPARE( arguments.at(0).value<Location*>(), m_subject_p->m_currentLocation );
  QCOMPARE( arguments.at(0).value<Location*>()->label(), QString( "fakegps" ) );
  arguments = spy.takeFirst();
  QCOMPARE( arguments.at(0).value<Location*>(), m_subject_p->m_currentLocation );
  QCOMPARE( arguments.at(0).value<Location*>()->label(), QString( "fakegps" ) );
  QCOMPARE( m_subject_p->m_currentLocation, fakeLocation );

  // should not be the gpsLocation or zero
  QVERIFY(m_subject_p->m_currentLocation != gpsLocation);
  QVERIFY(m_subject_p->m_currentLocation != 0);

  // switch back to GPS
  m_subject->useLiveGps();
  m_subject->getGps();

  // gps should be on
  QCOMPARE(m_subject_p->m_gpsOn, true);

  QVERIFY2(spy.count()==1, "should get a locationChanged signal from getGps" );
  arguments = spy.takeFirst();
  QCOMPARE(arguments.at(0).value<Location*>(), m_subject_p->m_currentLocation);
  QCOMPARE( arguments.at(0).value<Location*>()->label(), QString( "livegps" ) );
  QVERIFY(m_subject_p->m_currentLocation != fakeLocation);

  // fake a GPS update
  m_subject_p->updateLocation(); // pretend GPS has given an update

  // get GPS location
  m_subject->getGps();

  // check effect
  QCOMPARE(spy.count(), 1);
  arguments = spy.takeFirst();
  QCOMPARE(arguments.at(0).value<Location*>(), m_subject_p->m_currentLocation);
  QCOMPARE( arguments.at(0).value<Location*>()->label(), QString( "livegps" ) );
  QVERIFY(m_subject_p->m_currentLocation != 0);
}

void Ut_GpsController::testLiveToFakeToLive()
{
  m_subject_p->updateLocation(); // pretend GPS has given an update
  Location *fakeLocation = new Location();

  m_subject->useFakeGps( fakeLocation ); // ownership -> m_subject
  m_subject->getGps();

  // switch back to live GPS
  m_subject->useLiveGps();
  m_subject->getGps();

  // fake a GPS update
  m_subject_p->updateLocation(); // pretend GPS has given an update

  // get GPS location
  m_subject->getGps();

  m_subject->useFakeGps( fakeLocation ); // ownership -> m_subject
  m_subject->getGps();

  // fake a GPS update
  m_subject_p->updateLocation(); // pretend GPS has given an update

  // get GPS location
  m_subject->getGps();
}

QTEST_APPLESS_MAIN(Ut_GpsController)
