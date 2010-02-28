#include <QObject>
#include <QtDebug>
#include <QByteArray>
#include "ut_location.h"

QByteArray sampleInput(
"\
<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?><MTRXML version=\"1.0\">\
<GEOCODE key=\"taivaanvuohentie 7,helsinki\">\
<LOC name1=\"Taivaanvuohentie\" number=\"7\" city=\"Helsinki\" code=\"\" address=\"\" type=\"900\" category=\"street\" x=\"2549183\" y=\"6672570\" lon=\"24.88256\" lat=\"60.16183\" />\
</GEOCODE>\
</MTRXML>\
"

);

void Ut_Location::init()
{
    m_subject = new LocationPrivate();
}

void Ut_Location::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_Location::initTestCase()
{
}

void Ut_Location::cleanupTestCase()
{
}

void Ut_Location::testParseReply()
{
  m_subject->parseReply( sampleInput );

  QCOMPARE( m_subject->x(), QString( "2549183" ) );
  QCOMPARE( m_subject->y(), QString( "6672570" ) );
}

void Ut_Location::testSet()
{
  QString x( "2549183" );
  QString y( "6672570" );
  m_subject->setX( x );
  m_subject->setY( y );
  QCOMPARE( x, m_subject->x() );
  QCOMPARE( y, m_subject->y() );
}

QTEST_MAIN(Ut_Location)
