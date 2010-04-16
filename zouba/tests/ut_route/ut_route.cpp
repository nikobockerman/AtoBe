#include <QObject>
#include <QtDebug>
#include <QByteArray>
#include "ut_route.h"

#include "ut_sampleinput.h"

void Ut_Route::init()
{
    m_subject = new RoutePrivate();
}

void Ut_Route::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_Route::initTestCase()
{
}

void Ut_Route::cleanupTestCase()
{
}

void Ut_Route::testParseReply()
{
  QFETCH(QByteArray, xmlInput);
  QFETCH(QList<RouteData>, expectedResults);

  QList<RouteData> routeData = m_subject->parseReply( xmlInput );

  QCOMPARE( routeData.count(), expectedResults.count() );

  for( int index=0; index<routeData.count(); ++index ) {
    QCOMPARE( routeData.at( index ).lineCode,    expectedResults.at( index ).lineCode );
    QCOMPARE( routeData.at( index ).arrivalTime, expectedResults.at( index ).arrivalTime );
  }
}

void Ut_Route::testParseReply_data()
{
  QTest::addColumn<QByteArray>("xmlInput");
  QTest::addColumn< QList<RouteData> >("expectedResults");

  QTest::newRow("single route")
    << sampleInput[0]
    << ( QList<RouteData>()
        << RouteData( "65A", "18:20" )
        << RouteData( "102T", "18:26" )
        << RouteData( "110T", "18:34" )
        );

  QTest::newRow("route with bus change")
    << sampleInput[1]
    << ( QList<RouteData>()
        << RouteData( "111",  "08:18" )
        << RouteData( "111",  "08:33" )
        << RouteData( "111T", "08:34" )
        << RouteData( "111",  "08:50" )
        << RouteData( "111",  "09:07" )
        );
}

void Ut_Route::testSetFromLocation()
{
  Location work( "2551042", "6672829" );
  QCOMPARE( m_subject->fromValid(), false );
  m_subject->setFromLocation( &work );
  QCOMPARE( m_subject->fromLocation()->x(), work.x() );
  QCOMPARE( m_subject->fromLocation()->y(), work.y() );
  QCOMPARE( m_subject->fromValid(), true );
}

void Ut_Route::testSetToLocation()
{
  Location work( "2551042", "6672829" );
  QCOMPARE( m_subject->toValid(), false );
  m_subject->setToLocation( &work );
  QCOMPARE( m_subject->toLocation()->x(), work.x() );
  QCOMPARE( m_subject->toLocation()->y(), work.y() );
  QCOMPARE( m_subject->toValid(), true );
}

QTEST_APPLESS_MAIN(Ut_Route)
