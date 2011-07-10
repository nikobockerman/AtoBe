#ifndef ROUTELEG_H
#define ROUTELEG_H

#include "location.h"
//#include "route.h"
#include "routepoint.h"
#include <QString>
#include <QList>
#include <QTime>

//namespace RouteLeg {
enum LEG_TYPE {
    BUS,
    FERRY,
    SUB,
    TRAIN,
    TRAM,
    WALK
};


class RouteLeg
{
public:
    RouteLeg();
    RouteLeg(LEG_TYPE type, double distance, QTime time, RoutePoint *start, RoutePoint *end, QList<RoutePoint*> midRoute, QString symbol);
    RouteLeg(const RouteLeg&);
    RouteLeg& operator=(const RouteLeg&);
    ~RouteLeg();

    LEG_TYPE type;
    double distance;
    QTime time;
    RoutePoint *startPoint;
    RoutePoint *endPoint;
    QList<RoutePoint*> midRoute;
    QString symbol;
};

#endif // ROUTELEG_H
