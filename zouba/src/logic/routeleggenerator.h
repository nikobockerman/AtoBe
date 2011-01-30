#ifndef ROUTELEGGENERATOR_H
#define ROUTELEGGENERATOR_H

#include "routepoint.h"
#include "routeleg.h"
#include <QString>
#include <QTime>

namespace RouteLegGenerator
{
    RouteLeg* createLegWalk(double distance, QTime time, RoutePoint *startPoint, RoutePoint *endPoint, QList<RoutePoint*> midpoints);
    RouteLeg* createLegBus(double distance, QTime time, RoutePoint *startPoint, RoutePoint *endPoint, QList<RoutePoint*> midpoints, QString line_symbol);
    RouteLeg* createLegTram(double distance, QTime time, RoutePoint *startPoint, RoutePoint *endPoint, QList<RoutePoint*> midpoints, QString line_symbol);
    RouteLeg* createLegTrain(double distance, QTime time, RoutePoint *startPoint, RoutePoint *endPoint, QList<RoutePoint*> midpoints, QString line_symbol);
    RouteLeg* createLegSub(double distance, QTime time, RoutePoint *startPoint, RoutePoint *endPoint, QList<RoutePoint*> midpoints);
    RouteLeg* createLegFerry(double distance, QTime time, RoutePoint *startPoint, RoutePoint *endPoint, QList<RoutePoint*> midpoints);

    QTime parseTime(QString time);
};

#endif // ROUTELEGGENERATOR_H
