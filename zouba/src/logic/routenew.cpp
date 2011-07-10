#include "routenew.h"

#include <QDebug>

RouteNew::RouteNew() :
    startTime(), endTime(), startPoint(new RoutePoint()), endPoint(new RoutePoint()), walkingDistance(0.0), distance(0.0), route()
{
}

RouteNew::RouteNew(QDateTime startTime, QDateTime endTime, RoutePoint *startPoint, RoutePoint *endPoint, double walkingDistance, double distance, QList<RouteLeg*> route) :
    startTime(startTime), endTime(endTime), startPoint(startPoint), endPoint(endPoint), walkingDistance(walkingDistance), distance(distance), route(route)
{
}

RouteNew::RouteNew(const RouteNew &other) :
    startTime(other.startTime), endTime(other.endTime), walkingDistance(other.walkingDistance), distance(other.distance), route()
{
    qDebug() << "Starting RouteNew copy constructor.";
    this->startPoint = new RoutePoint(*other.startPoint);
    this->endPoint = new RoutePoint(*other.endPoint);

    QList<RouteLeg*>::const_iterator iter;
    for (iter = other.route.constBegin(); iter != other.route.constEnd(); iter++)
        this->route.append(new RouteLeg(**iter));

    qDebug() << "Finishing RouteNew copy constructor.";
}

RouteNew& RouteNew::operator=(const RouteNew &other)
{
    if (this != &other)
    {
        RoutePoint *new_start = new RoutePoint(*other.startPoint);
        RoutePoint *new_end = new RoutePoint(*other.endPoint);

        QList<RouteLeg*> new_routelegs = QList<RouteLeg*>();
        QList<RouteLeg*>::const_iterator iter;
        for (iter = other.route.constBegin(); iter != other.route.constEnd(); iter++)
        {
            new_routelegs.append(new RouteLeg(**iter));
        }

        delete this->startPoint;
        delete this->endPoint;
        while (this->route.size() > 0)
        {
            RouteLeg *leg = this->route.takeLast();
            delete leg;
        }

        this->route = new_routelegs;
        this->startPoint = new_start;
        this->endPoint = new_end;
        this->startTime = other.startTime;
        this->endTime = other.endTime;
        this->walkingDistance = other.walkingDistance;
        this->distance = other.distance;
    }

    return *this;
}

RouteNew::~RouteNew()
{
    delete this->startPoint;
    delete this->endPoint;
    while (this->route.size() > 0)
    {
        RouteLeg *leg = this->route.takeLast();
        delete leg;
    }
}
