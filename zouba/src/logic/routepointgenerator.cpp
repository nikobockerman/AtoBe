#include "routepointgenerator.h"

#include "routepoint.h"
#include <QString>
#include <QDateTime>

static const QString DEFAULT_NAME = QString("");


RoutePoint* RoutePointGenerator::createPointStop(QDateTime arrival, QDateTime departure, QString x, QString y, QString name)
{
    return new RoutePoint(STOP, arrival, departure, x, y, name);
}

RoutePoint* RoutePointGenerator::createPointPoint(QDateTime arrival, QDateTime departure, QString x, QString y)
{
    return new RoutePoint(POINT, arrival, departure, x, y, DEFAULT_NAME);
}

RoutePoint* RoutePointGenerator::createPointMapLocation(QDateTime arrival, QDateTime departure, QString x, QString y, QString name)
{
    return new RoutePoint(MAP_LOCATION, arrival, departure, x, y, name);
}

QDateTime RoutePointGenerator::parseDateTime(QString &date, QString &time)
{
    return QDateTime::fromString(date + time, "yyyyMMddHHmm");
}
