#ifndef STLHELPERS_H
#define STLHELPERS_H

#include <ostream>
#include "kkjgridcoordinate.h"
#include <QGeoCoordinate>

std::ostream& operator<<(std::ostream& stream, const KKJGridCoordinate &val)
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
