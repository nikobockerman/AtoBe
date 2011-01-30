#ifndef ROUTEPOINT_H
#define ROUTEPOINT_H

#include <QDateTime>

enum POINT_TYPE {
    MAP_LOCATION,
    POINT,
    STOP
};

class RoutePoint
{
public:
    RoutePoint();
    RoutePoint(POINT_TYPE type, QDateTime arrival, QDateTime departure, QString x, QString y, QString name);
    //~RoutePoint();
    //RoutePoint(const RoutePoint&);
    //RoutePoint& operator=(const RoutePoint&);

    POINT_TYPE type;
    QDateTime arrival_time, departure_time;
    QString name, x, y;
};

#endif // ROUTEPOINT_H
