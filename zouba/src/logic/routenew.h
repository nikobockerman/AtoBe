#ifndef ROUTENEW_H
#define ROUTENEW_H

#include "routepoint.h"
#include "routeleg.h"
#include <QDateTime>

class RouteNew
{
public:
    RouteNew();
    RouteNew(QDateTime startTime, QDateTime endTime, RoutePoint *startPoint, RoutePoint *endPoint, double walkingDistance, double distance, QList<RouteLeg*> route);
    RouteNew(const RouteNew&);
    RouteNew& operator=(const RouteNew&);
    ~RouteNew();

    QDateTime startTime;
    QDateTime endTime;
    RoutePoint *startPoint;
    RoutePoint *endPoint;
    double walkingDistance;
    double distance;
    QList<RouteLeg*> route;

};

#endif // ROUTENEW_H
