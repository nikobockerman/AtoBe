#ifndef ROUTEPOINTGENERATOR_H
#define ROUTEPOINTGENERATOR_H

#include "routepoint.h"
#include <QString>
#include <QDateTime>

namespace RoutePointGenerator
{
    RoutePoint* createPointStop(QDateTime arrival, QDateTime departure, QString x, QString y, QString name);
    RoutePoint* createPointPoint(QDateTime arrival, QDateTime departure, QString x, QString y);
    RoutePoint* createPointMapLocation(QDateTime arrival, QDateTime departure, QString x, QString y, QString name = QString());

    QDateTime parseDateTime(QString &date, QString &time);
};

#endif // ROUTEPOINTGENERATOR_H
