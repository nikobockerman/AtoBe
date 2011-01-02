#include "routefinder.h"
#include "location.h"
#include "locationfinder.h"
#include "ytv.h"
#include "routenew.h"
#include "routepointgenerator.h"
#include "routeleggenerator.h"

#include <QDebug>
#include <QXmlStreamReader>
#include <QStringList>
#include <QDateTime>
#include <QList>
#include <stdexcept>
#include <QCoreApplication>
#include <QEventLoop>

Location* getTopLocation(LocationFinder* finder);


RouteFinder::RouteFinder(const Location &from, const Location &to, QObject *parent) :
    QObject(parent), from(new Location(from)), to(new Location(to)),
    reply(NULL), routes(QList<RouteNew*>())
{
    this->fromFinder = NULL;
    if (!this->from->isValid())
    {
        qDebug() << "Find location for from address.";
        this->fromFinder = new LocationFinder(this->from->address());
        this->connect(this->fromFinder, SIGNAL(finished()), SLOT(fromLocationFound()));
    }

    this->toFinder = NULL;
    if (!this->to->isValid())
    {
        qDebug() << "Find location for to address.";
        this->toFinder = new LocationFinder(this->to->address());
        this->connect(this->toFinder, SIGNAL(finished()), SLOT(toLocationFound()));
    }

    if (this->fromFinder == NULL && this->toFinder == NULL)
        this->startRouteSearch();
}

void RouteFinder::fromLocationFound()
{
    qDebug() << "FROM location request is finished.";
    if (!this->fromFinder->responseWasValid())
    {
        qDebug() << "Response from ytv for FROM location was not valid.";
        return;
    }
    if (this->fromFinder->numberOfLocationsFound() == 0)
    {
        qDebug() << "No locations were found for FROM location";
        return;
    }
    this->from = getTopLocation(this->fromFinder);

    if (this->to->isValid())
        this->startRouteSearch();
}

void RouteFinder::toLocationFound()
{
    qDebug() << "TO location request is finished.";
    if (!this->toFinder->responseWasValid())
    {
        qDebug() << "Response from ytv for TO location was not valid.";
        return;
    }
    if (this->toFinder->numberOfLocationsFound() == 0)
    {
        qDebug() << "No locations were found for TO location";
        return;
    }
    this->to = getTopLocation(this->toFinder);

    if (this->from->isValid())
        this->startRouteSearch();
}

void RouteFinder::startRouteSearch()
{
    qDebug() << "Ready to search for route now.";

    QUrl fullUrl( Ytv::Url );

    QStringList a;
    a << this->from->x() << this->from->y();
    QStringList b;
    b << this->to->x() << this->to->y();

    fullUrl.addQueryItem( "a", a.join(",") );
    fullUrl.addQueryItem( "b", b.join(",") );
    fullUrl.addQueryItem( "show", QString::number(Ytv::ShowFiveResults) );
    fullUrl.addQueryItem( "walkspeed", QString::number(Ytv::WalkSpeedFast) );
    fullUrl.addQueryItem( "optimize", QString::number(Ytv::OptimizeDefault) );
    fullUrl.addQueryItem( "user", Ytv::Username);
    fullUrl.addQueryItem( "pass", Ytv::Password);

    qDebug() << "The query url: " << fullUrl.toString();

    this->reply = Ytv::manager.get(QNetworkRequest(fullUrl));
    this->connect(this->reply, SIGNAL(finished()), SLOT(requestFinished()));
}

RouteFinder::~RouteFinder()
{
    delete this->from;
    delete this->to;
    delete this->fromFinder;
    delete this->toFinder;
    if (this->reply)
        this->reply->deleteLater();

    while (!this->routes.isEmpty())
    {
        RouteNew* route = this->routes.takeLast();
        delete route;
    }
}

Location* getTopLocation(LocationFinder* finder)
{
    Location* ret;
    if (finder->numberOfPlaces() > 0)
        ret = finder->getPlace(0);
    else if (finder->numberOfRoadNames() > 0)
        ret = finder->getRoadName(0);
    else if (finder->numberOfStops() > 0)
        ret = finder->getStop(0);
    else
        throw std::runtime_error("No locations found from given LocationFinder.");

    return ret;
}

int RouteFinder::getNumberOfRoutes() const
{
    return this->routes.size();
}

RouteNew* RouteFinder::getRoute(int index) const
{
    if (index < 0 || index >= this->routes.size() )
        throw std::invalid_argument("Given index out of bounds.");
    RouteNew *ret = new RouteNew(*(this->routes.at(index)));
    return ret;
}

QString parseLineSymbol(QString &code)
{
    /*
Line code in the routing response is a unique code from the Register of Public Transport (JORE). The code the passengers know and which can be seen on the bus can be parsed from the JORE-code with the help of transport type id (attribute type in the response).

Please note that there are some special cases such as 1300-series (subway), 1100-series (Helsinki night buses) and 1019 (ferry to Suomenlinna).
JORE line codes are always 7 characters long. For example “2102T 1” which is JORE code for line 102T.

The code consists of following parts:
1. character = area/transport type code (e.g. 2)
2.-4. character = line code (e.g. 102)
5. character = letter variant (e.g. T)
6. character = letter variant or numeric variant (numeric variants are usually not used for base routes and are not shown to the end users)
7. character = direction (always 1 or 2), not shown to end users

More detailed instructions can be asked from YTV.
Area/transport types are:
1=Helsinki internal traffic
2=Espoo internal bus traffic and regional bus traffic from Helsinki to Espoo
3=Local trains
4=Vantaa internal bus traffic and regional bus traffic from Helsinki to Vantaa
5=Regional transverse traffic in Espoo - Helsinki - Vantaa
6=not in use
7=U-lines (buses that drive also outside the YTV area of service)
*/

    QString retVal;

    QString areaTransportTypeCode( code.mid(0,1) );
    QString lineCode( code.mid(1,3) );
    QString letterVariant( code.mid(4,1) );
    QString letterNumberVariant( code.mid(5,1) );
    QString direction( code.mid(6,1) );

    lineCode.setNum( lineCode.toInt() );

    retVal = lineCode;

    if ( letterVariant != " " )
    {
        retVal += letterVariant;
    }

    return retVal;
}


QDateTime parseArrivalDeparture(QXmlStreamReader &reader)
{
    //qDebug() << "Parsing ARRIVAL or DEPARTURE";

    QXmlStreamAttributes attributes(reader.attributes());
    QString date = attributes.value("date").toString();
    QString time = attributes.value("time").toString();
    QDateTime arrdep = RoutePointGenerator::parseDateTime(date, time);

    reader.readNext();

    //qDebug() << "ARRIVAL or DEPARTURE parsed";

    return arrdep;
}

RoutePoint* parsePoint(QXmlStreamReader &reader)
{
    //qDebug() << "Parsing POINT";

    QDateTime arrival, departure;
    QString x, y;

    QXmlStreamAttributes attributes(reader.attributes());
    x = attributes.value("x").toString();
    y = attributes.value("y").toString();

    while (!reader.atEnd() && !(reader.name() == "POINT" && reader.tokenType() == QXmlStreamReader::EndElement))
    {
        reader.readNext();

        if (reader.name() == "ARRIVAL" && reader.isStartElement())
        {
            arrival = parseArrivalDeparture(reader);
        }
        else if (reader.name() == "DEPARTURE" && reader.isStartElement())
        {
            departure = parseArrivalDeparture(reader);
        }
    }

    RoutePoint *point = RoutePointGenerator::createPointPoint(arrival, departure, x, y);

    //qDebug() << "POINT parsed";

    return point;
}

RoutePoint* parseMapLoc(QXmlStreamReader &reader)
{
    //qDebug() << "Parsing MAPLOC";

    QDateTime arrival, departure;
    QString x, y, name;

    QXmlStreamAttributes attributes(reader.attributes());
    x = attributes.value("x").toString();
    y = attributes.value("y").toString();

    while (!reader.atEnd() && !(reader.name() == "MAPLOC" && reader.tokenType() == QXmlStreamReader::EndElement))
    {
        reader.readNext();

        if (reader.name() == "ARRIVAL" && reader.isStartElement())
        {
            arrival = parseArrivalDeparture(reader);
        }
        else if (reader.name() == "DEPARTURE" && reader.isStartElement())
        {
            departure = parseArrivalDeparture(reader);
        }
        else if (reader.name() == "NAME" && reader.isStartElement())
        {
            // There may be zero, one or two NAME elements.
            // Finnish name has attribute lang="1".
            // Swedish name has attribute lang="2".
            if (reader.attributes().value("lang") == "1")
                name = reader.attributes().value("val").toString();
        }
    }

    RoutePoint* point = RoutePointGenerator::createPointMapLocation(arrival, departure, x, y, name);

    //qDebug() << "MAPLOC parsed";

    return point;
}

RoutePoint* parseStop(QXmlStreamReader &reader)
{
    //qDebug() << "Parsing STOP";

    QDateTime arrival, departure;
    QString x, y, name;

    QXmlStreamAttributes attributes(reader.attributes());
    x = attributes.value("x").toString();
    y = attributes.value("y").toString();

    while (!reader.atEnd() && !(reader.name() == "STOP" && reader.tokenType() == QXmlStreamReader::EndElement))
    {
        reader.readNext();

        if (reader.name() == "ARRIVAL" && reader.isStartElement())
        {
            arrival = parseArrivalDeparture(reader);
        }
        else if (reader.name() == "DEPARTURE" && reader.isStartElement())
        {
            departure = parseArrivalDeparture(reader);
        }
        else if (reader.name() == "NAME" && reader.isStartElement())
        {
            // There may be one or two NAME elements.
            // Finnish name has attribute lang="1".
            // Swedish name has attribute lang="2".
            if (reader.attributes().value("lang") == "1")
                name = reader.attributes().value("val").toString();
        }
    }

    RoutePoint* point = RoutePointGenerator::createPointStop(arrival, departure, x, y, name);

    //qDebug() << "STOP parsed";

    return point;
}

void parseLength(QXmlStreamReader &reader, QTime &time, double &distance)
{
    //qDebug() << "Parsing LENGTH";
    QXmlStreamAttributes attributes(reader.attributes());
    time = RouteLegGenerator::parseTime(attributes.value("time").toString());
    distance = attributes.value("dist").toString().toDouble();

    reader.readNext();

    //qDebug() << "LENGTH parsed";

    return;
}

RouteLeg* parseWalk(QXmlStreamReader &reader)
{
    //qDebug() << "Parsing WALK";

    double distance;
    QTime time;
    RoutePoint *startPoint, *endPoint;
    QList<RoutePoint*> midpoints;// = QList<RoutePoint*>();

    bool startFound = false;
    bool endFound = false;

    while (!reader.atEnd() && !(reader.name() == "WALK" && reader.tokenType() == QXmlStreamReader::EndElement))
    {
        reader.readNext();

        if (reader.name() == "LENGTH" && reader.isStartElement())
        {
            // One LENGTH element in WALK.
            parseLength(reader, time, distance);
        }
        else if (reader.name() == "POINT" && reader.isStartElement())
        {
            // Multiple POINT, MAPLOC or STOP elements may be found. All but first and last will be appended to midpoints list.
            // If first one is not found yet, don't append point to list, but store it to startPoint.
            // If first one is found but last one is not, don't append to list, but store it to endPoint.
            // Else, append endPoint to list and store new one to endPoint.
            if (!startFound)
            {
                startPoint = parsePoint(reader);
                startFound = true;
            }
            else if (!endFound)
            {
                endPoint = parsePoint(reader);
                endFound = true;
            }
            else
            {
                midpoints.append(endPoint);
                endPoint = parsePoint(reader);
            }
        }
        else if (reader.name() == "MAPLOC" && reader.isStartElement())
        {
            // Read comments from above. POINT
            if (!startFound)
            {
                startPoint = parseMapLoc(reader);
                startFound = true;
            }
            else if (!endFound)
            {
                endPoint = parseMapLoc(reader);
                endFound = true;
            }
            else
            {
                midpoints.append(endPoint);
                endPoint = parseMapLoc(reader);
            }
        }
        else if (reader.name() == "STOP" && reader.isStartElement())
        {
            // Read comments from above. POINT
            if (!startFound)
            {
                startPoint = parseStop(reader);
                startFound = true;
            }
            else if (!endFound)
            {
                endPoint = parseStop(reader);
                endFound = true;
            }
            else
            {
                midpoints.append(endPoint);
                endPoint = parseStop(reader);
            }
        }
    }

    RouteLeg *walk = RouteLegGenerator::createLegWalk(distance, time, startPoint, endPoint, midpoints);

    //qDebug() << "WALK parsed.";

    return walk;
}

RouteLeg* parseLine(QXmlStreamReader &reader)
{
    //qDebug() << "Parsing LINE";

    double distance;
    QTime time;
    RoutePoint *startPoint, *endPoint;
    QList<RoutePoint*> midpoints;// = QList<RoutePoint*>();

    bool startFound = false;
    bool endFound = false;

    QXmlStreamAttributes attributes(reader.attributes());
    QString code = attributes.value("code").toString();
    int type = attributes.value("type").toString().toInt();

    while (!reader.atEnd() && !(reader.name() == "LINE" && reader.tokenType() == QXmlStreamReader::EndElement))
    {
        reader.readNext();

        if (reader.name() == "LENGTH" && reader.isStartElement())
        {
            // One LENGTH element in WALK.
            parseLength(reader, time, distance);
        }
        else if (reader.name() == "STOP" && reader.isStartElement())
        {
            // Multiple STOP elements may be found. No other LEG_TYPEs are possible. All but first and last will be appended to midpoints list.
            // If first one is not found yet, don't append point to list, but store it to startPoint.
            // If first one is found but last one is not, don't append to list, but store it to endPoint.
            // Else, append endPoint to list and store new one to endPoint.
            if (!startFound)
            {
                startPoint = parseStop(reader);
                startFound = true;
            }
            else if (!endFound)
            {
                endPoint = parseStop(reader);
                endFound = true;
            }
            else
            {
                midpoints.append(endPoint);
                endPoint = parseStop(reader);
            }
        }
    }

    /* Types from reittiopas:
        Transport types:
        1 Helsinki/bus
        2 Helsinki/tram
        3 Espoo internal
        4 Vantaa internal
        5 Regional traffic
        6 Metro traffic
        7 Ferry
        8 U-lines
        9 Other local traffic
        10 Long-distance traffic
        11 Express
        12 VR local traffic
        13 VR long-distance traffic
        14 All
        21 Helsinki service lines
        22 Helsinki night traffic
        23 Espoo service lines
        24 Vantaa service lines
        25 Regional night traffic
        (types 9,10,11,13,14 are not used in the data)
*/
    RouteLeg* line = NULL;
    if (type == 6)
    {
        // Metro
        line = RouteLegGenerator::createLegSub(distance, time, startPoint, endPoint, midpoints);
    }
    else if (type == 2)
    {
        // Tram
        QString symbol = parseLineSymbol(code);
        line = RouteLegGenerator::createLegTram(distance, time, startPoint, endPoint, midpoints, symbol);
    }
    else if (type == 1 || type == 3 || type == 4 || type == 5 || type == 8 || type == 21 || type == 22 || type == 23 || type == 24 || type == 25)
    {
        // Bus
        QString symbol = parseLineSymbol(code);
        line = RouteLegGenerator::createLegBus(distance, time, startPoint, endPoint, midpoints, symbol);
    }
    else if (type == 7)
    {
        // Ferry
        line = RouteLegGenerator::createLegFerry(distance, time, startPoint, endPoint, midpoints);
    }
    else if (type == 12)
    {
        // Train
        QString symbol = parseLineSymbol(code);
        symbol = symbol.mid(1,1);
        line = RouteLegGenerator::createLegTrain(distance, time, startPoint, endPoint, midpoints, symbol);
    }
    else
        qDebug() << "Type mismatch (" << type << "!!!! Returning NULL!!!!";

    //qDebug() << "LINE parsed.";

    return line;
}

RouteNew* parseRoute(QXmlStreamReader &reader)
{
    QDateTime routeStartTime;
    QDateTime routeEndTime;
    RoutePoint *routeStartPoint;
    RoutePoint *routeEndPoint;
    double routeWalkingDistance = 0.0;
    double routeDistance;
    QList<RouteLeg*> routeSubRoute;

    //qDebug() << "Parsing route";
    while (!reader.atEnd() && !(reader.name() == "ROUTE" && reader.tokenType() == QXmlStreamReader::EndElement))
    {
        // No attributes
        reader.readNext();

        if (reader.name() == "LENGTH" && reader.isStartElement())
        {
            // Only one LENGTH element per route.
            QTime time;
            parseLength(reader, time, routeDistance);
        }
        else if (reader.name() == "POINT" && reader.isStartElement())
        {
            // Two POINT elements per route. One for start and dest points.
            // Start point has attribute uid="start" and dest has attribute uid="dest".
            if (reader.attributes().value("uid") == "start")
                routeStartPoint = parsePoint(reader);
            else if (reader.attributes().value("uid") == "dest")
                routeEndPoint = parsePoint(reader);
        }
        else if (reader.name() == "WALK" && reader.isStartElement())
        {
            routeSubRoute.append(parseWalk(reader));
        }
        else if (reader.name() == "LINE" && reader.isStartElement())
        {
            routeSubRoute.append(parseLine(reader));
        }
    }

    routeStartTime = routeStartPoint->departure_time;
    routeEndTime = routeEndPoint->arrival_time;
    RouteNew *route = new RouteNew(routeStartTime, routeEndTime, routeStartPoint, routeEndPoint, routeWalkingDistance, routeDistance, routeSubRoute);

    //qDebug() << "Route parsed.";

    return route;
}

void RouteFinder::requestFinished()
{
    //qDebug() << "Route response received from Ytv.";

    QXmlStreamReader xml(this->reply->readAll());

    //this->reply->disconnect(this, SLOT(requestFinished()));
    this->reply->deleteLater();
    this->reply = NULL;

    while (!xml.atEnd())
    {
        //qDebug() << "Reading next element";
        xml.readNext();

        QString xmlName(xml.name().toString());

        //qDebug() << "Element name: " + xmlName + " Type: " + xml.tokenString();
        if (xmlName == "ROUTE" && xml.isStartElement())
        {
            this->routes.append(parseRoute(xml));
        }
    }

    //qDebug() << "Finished processing RouteFinder";
    emit(finished());
    return;
}
