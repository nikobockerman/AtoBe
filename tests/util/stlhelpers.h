#ifndef STLHELPERS_H
#define STLHELPERS_H

#include <ostream>
#include "kkj.h"
#include <QGeoCoordinate>

std::ostream& operator<<(std::ostream& stream, const KKJ &val)
{
    stream << val.northing() << ", " << val.easting();
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const QTM_NAMESPACE::QGeoCoordinate &val)
{
    stream << val.latitude() << ", " << val.longitude();
    return stream;
}

#endif // STLHELPERS_H
