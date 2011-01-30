#include "routeleggenerator.h"

#include "routepoint.h"
#include "routeleg.h"

#include <QString>
#include <QStringList>
#include <QList>
#include <QTime>

static const QString WALK_SYMBOL = QString("Walk");
static const QString SUB_SYMBOL = QString("M");


RouteLeg* RouteLegGenerator::createLegWalk(double distance, QTime time, RoutePoint *startPoint, RoutePoint *endPoint, QList<RoutePoint*> midpoints)
{
    return new RouteLeg(WALK, distance, time, startPoint, endPoint, midpoints, WALK_SYMBOL);
}

RouteLeg* RouteLegGenerator::createLegBus(double distance, QTime time, RoutePoint *startPoint, RoutePoint *endPoint, QList<RoutePoint*> midpoints, QString line_symbol)
{
    return new RouteLeg(BUS, distance, time, startPoint, endPoint, midpoints, line_symbol);
}

RouteLeg* RouteLegGenerator::createLegTram(double distance, QTime time, RoutePoint *startPoint, RoutePoint *endPoint, QList<RoutePoint*> midpoints, QString line_symbol)
{
    return new RouteLeg(TRAM, distance, time, startPoint, endPoint, midpoints, line_symbol);
}

RouteLeg* RouteLegGenerator::createLegTrain(double distance, QTime time, RoutePoint *startPoint, RoutePoint *endPoint, QList<RoutePoint*> midpoints, QString line_symbol)
{
    return new RouteLeg(TRAIN, distance, time, startPoint, endPoint, midpoints, line_symbol);
}

RouteLeg* RouteLegGenerator::createLegSub(double distance, QTime time, RoutePoint *startPoint, RoutePoint *endPoint, QList<RoutePoint*> midpoints)
{
    return new RouteLeg(SUB, distance, time, startPoint, endPoint, midpoints, SUB_SYMBOL);
}

RouteLeg* RouteLegGenerator::createLegFerry(double distance, QTime time, RoutePoint *startPoint, RoutePoint *endPoint, QList<RoutePoint*> midpoints)
{
    return new RouteLeg(FERRY, distance, time, startPoint, endPoint, midpoints, SUB_SYMBOL);
}


QTime RouteLegGenerator::parseTime(QString time)
{
    QStringList split = time.split(".");
    QString min = split.at(0);
    int minutes = min.toInt();
    int hours = 0;
    while (minutes >= 60)
    {
        hours++;
        minutes -= 60;
    }
    QString search = QString::number(hours) + "." + QString::number(minutes) + "." + split.at(1);

    return QTime::fromString(search, "mm.zzz");
}
