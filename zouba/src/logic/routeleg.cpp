#include "routeleg.h"

RouteLeg::RouteLeg() :
    type(WALK), distance(0), time(), startPoint(new RoutePoint()), endPoint(new RoutePoint()), midRoute(), symbol()
{
}

RouteLeg::RouteLeg(LEG_TYPE type, double distance, QTime time, RoutePoint *start, RoutePoint *end, QList<RoutePoint*> midRoute, QString symbol) :
    type(type), distance(distance), time(time), startPoint(start), endPoint(end), midRoute(midRoute), symbol(symbol)
{
}

RouteLeg::RouteLeg(const RouteLeg &other) :
    type(other.type), distance(other.distance), time(other.time), startPoint(new RoutePoint(*other.startPoint)),
    endPoint(new RoutePoint(*other.endPoint)), midRoute(), symbol(other.symbol)
{
    QList<RoutePoint*>::const_iterator iter;
    for (iter = other.midRoute.constBegin(); iter != other.midRoute.constEnd(); iter++)
    {
        this->midRoute.append(new RoutePoint(**iter));
    }
}

RouteLeg& RouteLeg::operator=(const RouteLeg &other)
{
    if (this != &other)
    {
        RoutePoint *new_start = new RoutePoint(*other.startPoint);
        RoutePoint *new_end = new RoutePoint(*other.endPoint);

        QList<RoutePoint*> new_midpoints = QList<RoutePoint*>();
        QList<RoutePoint*>::const_iterator iter;
        for (iter = other.midRoute.constBegin(); iter != other.midRoute.constEnd(); iter++)
        {
            new_midpoints.append(new RoutePoint(**iter));
        }

        delete this->startPoint;
        delete this->endPoint;
        while (this->midRoute.size() > 0)
        {
            RoutePoint *point = this->midRoute.takeLast();
            delete point;
        }

        this->midRoute = new_midpoints;
        this->startPoint = new_start;
        this->endPoint = new_end;
        this->type = other.type;
        this->distance = other.distance;
        this->time = other.time;
        this->symbol = other.symbol;
    }

    return *this;
}

RouteLeg::~RouteLeg()
{
    delete this->startPoint;
    delete this->endPoint;
    while (this->midRoute.size() > 0)
    {
        RoutePoint *point = this->midRoute.takeLast();
        delete point;
    }
}
