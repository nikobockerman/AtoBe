#include <QObject>
#include <QtDebug>
#include <QByteArray>
#include "ut_route.h"

QByteArray sampleInput(
"\
<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?>\
<MTRXML version=\"1.0\">\
	<ROUTE from=\"start\" to=\"dest\">\
		<LENGTH time=\"14.411\" dist=\"2510.063\"/>\
		<POINT uid=\"start\" x=\"2551042.0\" y=\"6672829.0\">\
			<ARRIVAL date=\"20100207\" time=\"1815\"/>\
			<DEPARTURE date=\"20100207\" time=\"1815\"/>\
		</POINT>\
		<WALK>\
			<LENGTH time=\"4.475\" dist=\"357.069\"/>\
			<POINT uid=\"start\" x=\"2551042.0\" y=\"6672829.0\">\
				<ARRIVAL date=\"20100207\" time=\"1815\"/>\
				<DEPARTURE date=\"20100207\" time=\"1815\"/>\
			</POINT>\
			<MAPLOC x=\"2551034.9\" y=\"6672875.6\" type=\"7\">\
				<ARRIVAL date=\"20100207\" time=\"1816\"/>\
				<DEPARTURE date=\"20100207\" time=\"1816\"/>\
				<NAME lang=\"1\" val=\"Porkkalankatu\"/>\
			</MAPLOC>\
			<MAPLOC x=\"2550977.7\" y=\"6672869.1\" type=\"15\">\
				<ARRIVAL date=\"20100207\" time=\"1817\"/>\
				<DEPARTURE date=\"20100207\" time=\"1817\"/>\
			</MAPLOC>\
			<MAPLOC x=\"2550949.3\" y=\"6672867.5\" type=\"7\">\
				<ARRIVAL date=\"20100207\" time=\"1817\"/>\
				<DEPARTURE date=\"20100207\" time=\"1817\"/>\
				<NAME lang=\"1\" val=\"Porkkalankatu\"/>\
			</MAPLOC>\
			<MAPLOC x=\"2550817.2\" y=\"6672859.3\" type=\"7\">\
				<ARRIVAL date=\"20100207\" time=\"1819\"/>\
				<DEPARTURE date=\"20100207\" time=\"1819\"/>\
			</MAPLOC>\
			<MAPLOC x=\"2550808.5\" y=\"6672889.3\" type=\"11\">\
				<ARRIVAL date=\"20100207\" time=\"1820\"/>\
				<DEPARTURE date=\"20100207\" time=\"1820\"/>\
				<NAME lang=\"1\" val=\"Porkkalankatu\"/>\
			</MAPLOC>\
			<STOP code=\"6:1201129\" x=\"2550765.0\" y=\"6672886.0\" id=\"745\">\
				<ARRIVAL date=\"20100207\" time=\"1820\"/>\
				<DEPARTURE date=\"20100207\" time=\"1820\"/>\
				<NAME lang=\"1\" val=\"Länsiväylä\"/>\
				<NAME lang=\"2\" val=\"Västerleden\"/>\
			</STOP>\
		</WALK>\
		<LINE id=\"200\" code=\"1065A 2\" type=\"1\" mobility=\"3\">\
			<LENGTH time=\"5.000\" dist=\"1760.931\"/>\
			<STOP code=\"6:1201129\" x=\"2550765.0\" y=\"6672886.0\" id=\"745\" ord=\"30\">\
				<ARRIVAL date=\"20100207\" time=\"1820\"/>\
				<DEPARTURE date=\"20100207\" time=\"1820\"/>\
				<NAME lang=\"1\" val=\"Länsiväylä\"/>\
				<NAME lang=\"2\" val=\"Västerleden\"/>\
			</STOP>\
			<STOP code=\"6:1201131\" x=\"2550385.0\" y=\"6672760.0\" id=\"747\">\
				<ARRIVAL date=\"20100207\" time=\"1821\"/>\
				<DEPARTURE date=\"20100207\" time=\"1821\"/>\
				<NAME lang=\"1\" val=\"Salmisaari\"/>\
				<NAME lang=\"2\" val=\"Sundholmen\"/>\
			</STOP>\
			<STOP code=\"6:1310101\" x=\"2549608.0\" y=\"6672522.0\" id=\"1356\">\
				<ARRIVAL date=\"20100207\" time=\"1824\"/>\
				<DEPARTURE date=\"20100207\" time=\"1824\"/>\
				<NAME lang=\"1\" val=\"Lauttasaaren silta\"/>\
				<NAME lang=\"2\" val=\"Drumsö bro\"/>\
			</STOP>\
			<STOP code=\"6:1310103\" x=\"2549247.0\" y=\"6672446.0\" id=\"1358\" ord=\"33\">\
				<ARRIVAL date=\"20100207\" time=\"1825\"/>\
				<DEPARTURE date=\"20100207\" time=\"1825\"/>\
				<NAME lang=\"1\" val=\"Koillisväylä\"/>\
				<NAME lang=\"2\" val=\"Nordostpassagen\"/>\
			</STOP>\
		</LINE>\
		<WALK>\
			<LENGTH time=\"4.936\" dist=\"392.062\"/>\
			<STOP code=\"6:1310103\" x=\"2549247.0\" y=\"6672446.0\" id=\"1358\">\
				<ARRIVAL date=\"20100207\" time=\"1825\"/>\
				<DEPARTURE date=\"20100207\" time=\"1825\"/>\
				<NAME lang=\"1\" val=\"Koillisväylä\"/>\
				<NAME lang=\"2\" val=\"Nordostpassagen\"/>\
			</STOP>\
			<MAPLOC x=\"2549200.4\" y=\"6672433.4\" type=\"0\">\
				<ARRIVAL date=\"20100207\" time=\"1825\"/>\
				<DEPARTURE date=\"20100207\" time=\"1825\"/>\
				<NAME lang=\"1\" val=\"Taivaanvuohenkuja\"/>\
			</MAPLOC>\
			<MAPLOC x=\"2549151.2\" y=\"6672527.3\" type=\"0\">\
				<ARRIVAL date=\"20100207\" time=\"1827\"/>\
				<DEPARTURE date=\"20100207\" time=\"1827\"/>\
				<NAME lang=\"1\" val=\"Taivaanvuohentie\"/>\
			</MAPLOC>\
			<MAPLOC x=\"2549105.4\" y=\"6672573.6\" type=\"0\">\
				<ARRIVAL date=\"20100207\" time=\"1828\"/>\
				<DEPARTURE date=\"20100207\" time=\"1828\"/>\
			</MAPLOC>\
			<MAPLOC x=\"2549115.4\" y=\"6672595.1\" type=\"0\">\
				<ARRIVAL date=\"20100207\" time=\"1828\"/>\
				<DEPARTURE date=\"20100207\" time=\"1828\"/>\
			</MAPLOC>\
			<MAPLOC x=\"2549162.6\" y=\"6672633.1\" type=\"0\">\
				<ARRIVAL date=\"20100207\" time=\"1829\"/>\
				<DEPARTURE date=\"20100207\" time=\"1829\"/>\
			</MAPLOC>\
			<POINT uid=\"dest\" x=\"2549183.0\" y=\"6672570.0\">\
				<ARRIVAL date=\"20100207\" time=\"1829\"/>\
				<DEPARTURE date=\"20100207\" time=\"1829\"/>\
			</POINT>\
		</WALK>\
		<POINT uid=\"dest\" x=\"2549183.0\" y=\"6672570.0\">\
			<ARRIVAL date=\"20100207\" time=\"1829\"/>\
			<DEPARTURE date=\"20100207\" time=\"1829\"/>\
		</POINT>\
	</ROUTE>\
	<ROUTE from=\"start\" to=\"dest\">\
		<LENGTH time=\"13.411\" dist=\"2501.497\"/>\
		<POINT uid=\"start\" x=\"2551042.0\" y=\"6672829.0\">\
			<ARRIVAL date=\"20100207\" time=\"1821\"/>\
			<DEPARTURE date=\"20100207\" time=\"1821\"/>\
		</POINT>\
		<WALK>\
			<LENGTH time=\"4.475\" dist=\"357.069\"/>\
			<POINT uid=\"start\" x=\"2551042.0\" y=\"6672829.0\">\
				<ARRIVAL date=\"20100207\" time=\"1821\"/>\
				<DEPARTURE date=\"20100207\" time=\"1821\"/>\
			</POINT>\
			<MAPLOC x=\"2551034.9\" y=\"6672875.6\" type=\"7\">\
				<ARRIVAL date=\"20100207\" time=\"1822\"/>\
				<DEPARTURE date=\"20100207\" time=\"1822\"/>\
				<NAME lang=\"1\" val=\"Porkkalankatu\"/>\
			</MAPLOC>\
			<MAPLOC x=\"2550977.7\" y=\"6672869.1\" type=\"15\">\
				<ARRIVAL date=\"20100207\" time=\"1823\"/>\
				<DEPARTURE date=\"20100207\" time=\"1823\"/>\
			</MAPLOC>\
			<MAPLOC x=\"2550949.3\" y=\"6672867.5\" type=\"7\">\
				<ARRIVAL date=\"20100207\" time=\"1823\"/>\
				<DEPARTURE date=\"20100207\" time=\"1823\"/>\
				<NAME lang=\"1\" val=\"Porkkalankatu\"/>\
			</MAPLOC>\
			<MAPLOC x=\"2550817.2\" y=\"6672859.3\" type=\"7\">\
				<ARRIVAL date=\"20100207\" time=\"1825\"/>\
				<DEPARTURE date=\"20100207\" time=\"1825\"/>\
			</MAPLOC>\
			<MAPLOC x=\"2550808.5\" y=\"6672889.3\" type=\"11\">\
				<ARRIVAL date=\"20100207\" time=\"1826\"/>\
				<DEPARTURE date=\"20100207\" time=\"1826\"/>\
				<NAME lang=\"1\" val=\"Porkkalankatu\"/>\
			</MAPLOC>\
			<STOP code=\"6:1201227\" x=\"2550765.0\" y=\"6672886.0\" id=\"755\">\
				<ARRIVAL date=\"20100207\" time=\"1826\"/>\
				<DEPARTURE date=\"20100207\" time=\"1826\"/>\
				<NAME lang=\"1\" val=\"Länsiväylä\"/>\
				<NAME lang=\"2\" val=\"Västerleden\"/>\
			</STOP>\
		</WALK>\
		<LINE id=\"579\" code=\"2102T 1\" type=\"5\" mobility=\"3\">\
			<LENGTH time=\"4.000\" dist=\"1751.582\"/>\
			<STOP code=\"6:1201227\" x=\"2550765.0\" y=\"6672886.0\" id=\"755\" ord=\"3\">\
				<ARRIVAL date=\"20100207\" time=\"1826\"/>\
				<DEPARTURE date=\"20100207\" time=\"1826\"/>\
				<NAME lang=\"1\" val=\"Länsiväylä\"/>\
				<NAME lang=\"2\" val=\"Västerleden\"/>\
			</STOP>\
			<STOP code=\"6:1201231\" x=\"2550387.0\" y=\"6672761.0\" id=\"759\">\
				<ARRIVAL date=\"20100207\" time=\"1827\"/>\
				<DEPARTURE date=\"20100207\" time=\"1827\"/>\
				<NAME lang=\"1\" val=\"Salmisaari\"/>\
				<NAME lang=\"2\" val=\"Sundholmen\"/>\
			</STOP>\
			<STOP code=\"6:1310201\" x=\"2549630.0\" y=\"6672524.0\" id=\"1402\">\
				<ARRIVAL date=\"20100207\" time=\"1829\"/>\
				<DEPARTURE date=\"20100207\" time=\"1829\"/>\
				<NAME lang=\"1\" val=\"Lauttasaaren silta\"/>\
				<NAME lang=\"2\" val=\"Drumsö bro\"/>\
			</STOP>\
			<STOP code=\"6:1310203\" x=\"2549248.0\" y=\"6672446.0\" id=\"1404\" ord=\"6\">\
				<ARRIVAL date=\"20100207\" time=\"1830\"/>\
				<DEPARTURE date=\"20100207\" time=\"1830\"/>\
				<NAME lang=\"1\" val=\"Koillisväylä\"/>\
				<NAME lang=\"2\" val=\"Nordostpassagen\"/>\
			</STOP>\
		</LINE>\
		<WALK>\
			<LENGTH time=\"4.936\" dist=\"392.846\"/>\
			<STOP code=\"6:1310203\" x=\"2549248.0\" y=\"6672446.0\" id=\"1404\">\
				<ARRIVAL date=\"20100207\" time=\"1830\"/>\
				<DEPARTURE date=\"20100207\" time=\"1830\"/>\
				<NAME lang=\"1\" val=\"Koillisväylä\"/>\
				<NAME lang=\"2\" val=\"Nordostpassagen\"/>\
			</STOP>\
			<MAPLOC x=\"2549200.4\" y=\"6672433.4\" type=\"0\">\
				<ARRIVAL date=\"20100207\" time=\"1830\"/>\
				<DEPARTURE date=\"20100207\" time=\"1830\"/>\
				<NAME lang=\"1\" val=\"Taivaanvuohenkuja\"/>\
			</MAPLOC>\
			<MAPLOC x=\"2549151.2\" y=\"6672527.3\" type=\"0\">\
				<ARRIVAL date=\"20100207\" time=\"1832\"/>\
				<DEPARTURE date=\"20100207\" time=\"1832\"/>\
				<NAME lang=\"1\" val=\"Taivaanvuohentie\"/>\
			</MAPLOC>\
			<MAPLOC x=\"2549105.4\" y=\"6672573.6\" type=\"0\">\
				<ARRIVAL date=\"20100207\" time=\"1833\"/>\
				<DEPARTURE date=\"20100207\" time=\"1833\"/>\
			</MAPLOC>\
			<MAPLOC x=\"2549115.4\" y=\"6672595.1\" type=\"0\">\
				<ARRIVAL date=\"20100207\" time=\"1833\"/>\
				<DEPARTURE date=\"20100207\" time=\"1833\"/>\
			</MAPLOC>\
			<MAPLOC x=\"2549162.6\" y=\"6672633.1\" type=\"0\">\
				<ARRIVAL date=\"20100207\" time=\"1834\"/>\
				<DEPARTURE date=\"20100207\" time=\"1834\"/>\
			</MAPLOC>\
			<POINT uid=\"dest\" x=\"2549183.0\" y=\"6672570.0\">\
				<ARRIVAL date=\"20100207\" time=\"1834\"/>\
				<DEPARTURE date=\"20100207\" time=\"1834\"/>\
			</POINT>\
		</WALK>\
		<POINT uid=\"dest\" x=\"2549183.0\" y=\"6672570.0\">\
			<ARRIVAL date=\"20100207\" time=\"1834\"/>\
			<DEPARTURE date=\"20100207\" time=\"1834\"/>\
		</POINT>\
	</ROUTE>\
	<ROUTE from=\"start\" to=\"dest\">\
		<LENGTH time=\"13.411\" dist=\"2501.497\"/>\
		<POINT uid=\"start\" x=\"2551042.0\" y=\"6672829.0\">\
			<ARRIVAL date=\"20100207\" time=\"1829\"/>\
			<DEPARTURE date=\"20100207\" time=\"1829\"/>\
		</POINT>\
		<WALK>\
			<LENGTH time=\"4.475\" dist=\"357.069\"/>\
			<POINT uid=\"start\" x=\"2551042.0\" y=\"6672829.0\">\
				<ARRIVAL date=\"20100207\" time=\"1829\"/>\
				<DEPARTURE date=\"20100207\" time=\"1829\"/>\
			</POINT>\
			<MAPLOC x=\"2551034.9\" y=\"6672875.6\" type=\"7\">\
				<ARRIVAL date=\"20100207\" time=\"1830\"/>\
				<DEPARTURE date=\"20100207\" time=\"1830\"/>\
				<NAME lang=\"1\" val=\"Porkkalankatu\"/>\
			</MAPLOC>\
			<MAPLOC x=\"2550977.7\" y=\"6672869.1\" type=\"15\">\
				<ARRIVAL date=\"20100207\" time=\"1831\"/>\
				<DEPARTURE date=\"20100207\" time=\"1831\"/>\
			</MAPLOC>\
			<MAPLOC x=\"2550949.3\" y=\"6672867.5\" type=\"7\">\
				<ARRIVAL date=\"20100207\" time=\"1831\"/>\
				<DEPARTURE date=\"20100207\" time=\"1831\"/>\
				<NAME lang=\"1\" val=\"Porkkalankatu\"/>\
			</MAPLOC>\
			<MAPLOC x=\"2550817.2\" y=\"6672859.3\" type=\"7\">\
				<ARRIVAL date=\"20100207\" time=\"1833\"/>\
				<DEPARTURE date=\"20100207\" time=\"1833\"/>\
			</MAPLOC>\
			<MAPLOC x=\"2550808.5\" y=\"6672889.3\" type=\"11\">\
				<ARRIVAL date=\"20100207\" time=\"1834\"/>\
				<DEPARTURE date=\"20100207\" time=\"1834\"/>\
				<NAME lang=\"1\" val=\"Porkkalankatu\"/>\
			</MAPLOC>\
			<STOP code=\"6:1201227\" x=\"2550765.0\" y=\"6672886.0\" id=\"755\">\
				<ARRIVAL date=\"20100207\" time=\"1834\"/>\
				<DEPARTURE date=\"20100207\" time=\"1834\"/>\
				<NAME lang=\"1\" val=\"Länsiväylä\"/>\
				<NAME lang=\"2\" val=\"Västerleden\"/>\
			</STOP>\
		</WALK>\
		<LINE id=\"603\" code=\"2110T 1\" type=\"5\" mobility=\"3\">\
			<LENGTH time=\"4.000\" dist=\"1751.582\"/>\
			<STOP code=\"6:1201227\" x=\"2550765.0\" y=\"6672886.0\" id=\"755\" ord=\"3\">\
				<ARRIVAL date=\"20100207\" time=\"1834\"/>\
				<DEPARTURE date=\"20100207\" time=\"1834\"/>\
				<NAME lang=\"1\" val=\"Länsiväylä\"/>\
				<NAME lang=\"2\" val=\"Västerleden\"/>\
			</STOP>\
			<STOP code=\"6:1201231\" x=\"2550387.0\" y=\"6672761.0\" id=\"759\">\
				<ARRIVAL date=\"20100207\" time=\"1835\"/>\
				<DEPARTURE date=\"20100207\" time=\"1835\"/>\
				<NAME lang=\"1\" val=\"Salmisaari\"/>\
				<NAME lang=\"2\" val=\"Sundholmen\"/>\
			</STOP>\
			<STOP code=\"6:1310201\" x=\"2549630.0\" y=\"6672524.0\" id=\"1402\">\
				<ARRIVAL date=\"20100207\" time=\"1837\"/>\
				<DEPARTURE date=\"20100207\" time=\"1837\"/>\
				<NAME lang=\"1\" val=\"Lauttasaaren silta\"/>\
				<NAME lang=\"2\" val=\"Drumsö bro\"/>\
			</STOP>\
			<STOP code=\"6:1310203\" x=\"2549248.0\" y=\"6672446.0\" id=\"1404\" ord=\"6\">\
				<ARRIVAL date=\"20100207\" time=\"1838\"/>\
				<DEPARTURE date=\"20100207\" time=\"1838\"/>\
				<NAME lang=\"1\" val=\"Koillisväylä\"/>\
				<NAME lang=\"2\" val=\"Nordostpassagen\"/>\
			</STOP>\
		</LINE>\
		<WALK>\
			<LENGTH time=\"4.936\" dist=\"392.846\"/>\
			<STOP code=\"6:1310203\" x=\"2549248.0\" y=\"6672446.0\" id=\"1404\">\
				<ARRIVAL date=\"20100207\" time=\"1838\"/>\
				<DEPARTURE date=\"20100207\" time=\"1838\"/>\
				<NAME lang=\"1\" val=\"Koillisväylä\"/>\
				<NAME lang=\"2\" val=\"Nordostpassagen\"/>\
			</STOP>\
			<MAPLOC x=\"2549200.4\" y=\"6672433.4\" type=\"0\">\
				<ARRIVAL date=\"20100207\" time=\"1838\"/>\
				<DEPARTURE date=\"20100207\" time=\"1838\"/>\
				<NAME lang=\"1\" val=\"Taivaanvuohenkuja\"/>\
			</MAPLOC>\
			<MAPLOC x=\"2549151.2\" y=\"6672527.3\" type=\"0\">\
				<ARRIVAL date=\"20100207\" time=\"1840\"/>\
				<DEPARTURE date=\"20100207\" time=\"1840\"/>\
				<NAME lang=\"1\" val=\"Taivaanvuohentie\"/>\
			</MAPLOC>\
			<MAPLOC x=\"2549105.4\" y=\"6672573.6\" type=\"0\">\
				<ARRIVAL date=\"20100207\" time=\"1841\"/>\
				<DEPARTURE date=\"20100207\" time=\"1841\"/>\
			</MAPLOC>\
			<MAPLOC x=\"2549115.4\" y=\"6672595.1\" type=\"0\">\
				<ARRIVAL date=\"20100207\" time=\"1841\"/>\
				<DEPARTURE date=\"20100207\" time=\"1841\"/>\
			</MAPLOC>\
			<MAPLOC x=\"2549162.6\" y=\"6672633.1\" type=\"0\">\
				<ARRIVAL date=\"20100207\" time=\"1842\"/>\
				<DEPARTURE date=\"20100207\" time=\"1842\"/>\
			</MAPLOC>\
			<POINT uid=\"dest\" x=\"2549183.0\" y=\"6672570.0\">\
				<ARRIVAL date=\"20100207\" time=\"1842\"/>\
				<DEPARTURE date=\"20100207\" time=\"1842\"/>\
			</POINT>\
		</WALK>\
		<POINT uid=\"dest\" x=\"2549183.0\" y=\"6672570.0\">\
			<ARRIVAL date=\"20100207\" time=\"1842\"/>\
			<DEPARTURE date=\"20100207\" time=\"1842\"/>\
		</POINT>\
	</ROUTE>\
</MTRXML>\
"

);

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
  RouteData routeData = m_subject->parseReply( sampleInput );

  QCOMPARE( routeData.lineCode, QString( "2110T 1" ) );
  QCOMPARE( routeData.arrivalTime, QString( "1834" ) );
}

void Ut_Route::testSetFromLocation()
{
  Location work( "2551042", "6672829" );
  m_subject->setFromLocation( work );
  QCOMPARE( work.x, m_subject->fromLocation().x );
  QCOMPARE( work.y, m_subject->fromLocation().y );
}

void Ut_Route::testSetToLocation()
{
  Location work( "2551042", "6672829" );
  m_subject->setToLocation( work );
  QCOMPARE( work.x, m_subject->toLocation().x );
  QCOMPARE( work.y, m_subject->toLocation().y );
}

QTEST_MAIN(Ut_Route)
