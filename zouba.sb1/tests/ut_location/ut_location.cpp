#include <QObject>
#include <QtDebug>
#include <QByteArray>
#include <QGeoPositionInfo>
#include "location.h"
#include "location_p.h"
#include "ut_location.h"

QTM_USE_NAMESPACE

QByteArray sampleInput(
"\
<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?><MTRXML version=\"1.0\">\
<GEOCODE key=\"taivaanvuohentie 7,helsinki\">\
<LOC name1=\"Taivaanvuohentie\" number=\"7\" city=\"Helsinki\" code=\"\" address=\"\" type=\"900\" category=\"street\" x=\"2549182\" y=\"6672569\" lon=\"24.88256\" lat=\"60.16183\" />\
</GEOCODE>\
</MTRXML>\
"

);

void Ut_Location::init()
{
}

void Ut_Location::cleanup()
{
}

void Ut_Location::initTestCase()
{
}

void Ut_Location::cleanupTestCase()
{
}

void Ut_Location::testParseReply()
{
  LocationPrivate m_subject;

  m_subject.parseReply( sampleInput );

  QCOMPARE( m_subject.x(), QString( "2549182" ) );
  QCOMPARE( m_subject.y(), QString( "6672569" ) );
}

void Ut_Location::testSet()
{
  LocationPrivate m_subject;

  QString x( "2549182" );
  QString y( "6672569" );
  m_subject.setX( x );
  m_subject.setY( y );
  QCOMPARE( x, m_subject.x() );
  QCOMPARE( y, m_subject.y() );
}

void Ut_Location::testConstructorQGeoPositionInfo()
{
  QGeoPositionInfo thisPositionInfo( QGeoCoordinate( 60.16183, 24.88256 ), QDateTime( QDate( 1965, 11, 11 ) ) );
  Location subject( thisPositionInfo );

  QString x( "2549182" );
  QString y( "6672569" );
  QCOMPARE( subject.x(), x );
  QCOMPARE( subject.y(), y );
}

QTEST_MAIN(Ut_Location)
