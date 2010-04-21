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

  for( int routeIndex=0; routeIndex<routeData.count(); ++routeIndex ) {
    const RouteData &thisRouteData     = routeData.at( routeIndex );
    const RouteData &thisExpectedRoute = expectedResults.at( routeIndex );

    QCOMPARE( thisRouteData.m_tripTime,        thisExpectedRoute.m_tripTime );
    QCOMPARE( thisRouteData.m_tripDistance,    thisExpectedRoute.m_tripDistance );
    QCOMPARE( thisRouteData.m_departureTime,   thisExpectedRoute.m_departureTime );
    QCOMPARE( thisRouteData.m_lineCode,        thisExpectedRoute.m_lineCode );
    QCOMPARE( thisRouteData.m_legData.count(), thisExpectedRoute.m_legData.count() );

    for( int legIndex=0; legIndex<thisRouteData.m_legData.count(); ++legIndex ) {
      const LegData &thisLegData     = thisRouteData.m_legData.at( legIndex );
      const LegData &thisExpectedLeg = thisExpectedRoute.m_legData.at( legIndex );

      QCOMPARE( thisLegData.m_how,           thisExpectedLeg.m_how );
      QCOMPARE( thisLegData.m_tripTime,      thisExpectedLeg.m_tripTime );
      QCOMPARE( thisLegData.m_tripDistance,  thisExpectedLeg.m_tripDistance );
      QCOMPARE( thisLegData.m_departureTime, thisExpectedLeg.m_departureTime );
      QCOMPARE( thisLegData.m_arrivalTime,   thisExpectedLeg.m_arrivalTime );
      QCOMPARE( thisLegData.m_lineCode,      thisExpectedLeg.m_lineCode );
    }
  }
}

void Ut_Route::testParseReply_data()
{
  QTest::addColumn<QByteArray>("xmlInput");
  QTest::addColumn< QList<RouteData> >("expectedResults");

  QTest::newRow("single route")
    << sampleInput[0]
    << ( QList<RouteData>()
        // Summary :    TTime     TDist       First Vehicle
        << ( RouteData( "14.411", "2510.063", "18:20", "65A" )
          //          How     TTime    TDist       Depart   Arrive   Line
          << LegData( "WALK", "4.475", "357.069",  "18:15", "18:20" )
          << LegData( "LINE", "5.000", "1760.931", "18:20", "18:25", "65A" )
          << LegData( "WALK", "4.936", "392.062",  "18:25", "18:29" )
          )
        // Summary :    TTime     TDist       First Vehicle
        << ( RouteData( "13.411", "2501.497", "18:26", "102T" )
          //          How     TTime    TDist       Depart   Arrive   Line
          << LegData( "WALK", "4.475", "357.069",  "18:21", "18:26" )
          << LegData( "LINE", "4.000", "1751.582", "18:26", "18:30", "102T" )
          << LegData( "WALK", "4.936", "392.846",  "18:30", "18:34" )
          )
        // Summary :    TTime     TDist       First Vehicle
        << ( RouteData( "13.411", "2501.497", "18:34", "110T" )
          //          How     TTime    TDist       Depart   Arrive   Line
          << LegData( "WALK", "4.475", "357.069",  "18:29", "18:34" )
          << LegData( "LINE", "4.000", "1751.582", "18:34", "18:38", "110T" )
          << LegData( "WALK", "4.936", "392.846",  "18:38", "18:42" )
          )
        );

  QTest::newRow("route with bus change")
    << sampleInput[1]
    << ( QList<RouteData>()
        // Summary :    TTime     TDist       First Vehicle
        << ( RouteData( "28.633", "8902.040", "08:18",  "111" )
          //          How     TTime    TDist       Depart   Arrive   Line
          << LegData( "WALK", "3.479", "254.753",  "08:14", "08:18" )
          << LegData( "LINE", "8.000", "5225.092", "08:18", "08:26", "111" )
          << LegData( "LINE", "5.000", "2926.431", "08:32", "08:37", "121T" )
          << LegData( "WALK", "6.154", "495.764",  "08:37", "08:43" )
          )
        // Summary :    TTime     TDist       First Vehicle
        << ( RouteData( "25.633", "8902.040", "08:33",  "111" )
          //          How     TTime    TDist       Depart   Arrive   Line
          << LegData( "WALK", "3.479", "254.753",  "08:29", "08:33" )
          << LegData( "LINE", "8.000", "5225.092", "08:33", "08:41", "111" )
          << LegData( "LINE", "5.000", "2926.431", "08:44", "08:49", "102T" )
          << LegData( "WALK", "6.154", "495.764",  "08:49", "08:55" )
          )
        // Summary :    TTime     TDist        First Vehicle
        << ( RouteData( "33.510", "11193.458", "08:34", "111T" )
          //          How     TTime    TDist       Depart   Arrive   Line
          << LegData( "WALK", "2.356", "172.693",  "08:31", "08:34" )
          << LegData( "LINE", "6.000", "3392.054", "08:34", "08:40", "111T" )
          << LegData( "LINE", "5.000", "4206.516", "08:43", "08:48", "112" )
          << LegData( "LINE", "5.000", "2926.431", "08:54", "08:59", "102T" )
          << LegData( "WALK", "6.154", "495.764",  "08:59", "09:05" )
          )
        // Summary :    TTime     TDist       First Vehicle
        << ( RouteData( "29.633", "8902.040", "08:50",  "111" )
          //          How     TTime    TDist       Depart   Arrive   Line
          << LegData( "WALK", "3.479", "254.753",  "08:46", "08:50" )
          << LegData( "LINE", "8.000", "5225.092", "08:50", "08:58", "111" )
          << LegData( "LINE", "5.000", "2926.431", "09:05", "09:10", "102T" )
          << LegData( "WALK", "6.154", "495.764",  "09:10", "09:16" )
          )
        // Summary :    TTime     TDist       First Vehicle
        << ( RouteData( "29.633", "8902.040", "09:07",  "111" )
          //          How     TTime    TDist       Depart   Arrive   Line
          << LegData( "WALK", "3.479", "254.753",  "09:03", "09:07" )
          << LegData( "LINE", "8.000", "5225.092", "09:07", "09:15", "111" )
          << LegData( "LINE", "5.000", "2926.431", "09:22", "09:27", "160T" )
          << LegData( "WALK", "6.154", "495.764",  "09:27", "09:33" )
          )
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
