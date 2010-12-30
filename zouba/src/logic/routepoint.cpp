#include "routepoint.h"

RoutePoint::RoutePoint() :
    type(POINT), arrival_time(), departure_time(), name(), x(), y()
{
}

RoutePoint::RoutePoint(POINT_TYPE type, QDateTime arrival, QDateTime departure, QString x, QString y, QString name) :
    type(type), arrival_time(arrival), departure_time(departure), name(name), x(x), y(y)
{
}

/*RoutePoint::~RoutePoint()
{
    delete this->arrival_time;
    delete this->departure_time;
}*/

/*RoutePoint::RoutePoint(const RoutePoint& other) :
    type(other.type), arrival_time(new QDateTime(*other.arrival_time)), departure_time(new QDateTime(*other.departure_time)),
    name(other.name), x(other.x), y(other.y)
{
}*/

/*RoutePoint& RoutePoint::operator=(const RoutePoint& other)
{
    if (this != &other)
    {
        QDateTime *new_arrival = new QDateTime(*other.arrival_time);
        QDateTime *new_departure = new QDateTime(*other.departure_time);

        delete this->arrival_time;
        delete this->departure_time;

        this->arrival_time = new_arrival;
        this->departure_time = new_departure;
        this->type = other.type;
        this->name = other.name;
        this->x = other.x;
        this->y = other.y;
    }

    return *this;
}*/
