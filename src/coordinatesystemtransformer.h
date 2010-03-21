#ifndef COORDINATESYSTEMTRANSFORMER_H
#define COORDINATESYSTEMTRANSFORMER_H

#include "kkj.h"
#include <QGeoCoordinate>

/**
 * A utility class for transforming coordinates from one coordinate system to another.
 */
class CoordinateSystemTransformer
{
public:
    /**
     * Makes a coordinate transformation from WGS84 coordinate system to KKJ rectangular
     * grid coordinates.
     * @param fromCoordinate the WGS84 coordinate that will be transformed.
     * @return the transformed coordinate in KKJ coordinate system.
     */
    static KKJ transformToKKJ(const QTM_NAMESPACE::QGeoCoordinate &fromCoordinate);

    /**
     * Makes a coordinate transformation from KKJ rectangular grid coordinate system
     * to WGS84 coordinate system.
     * @param fromCoordinate the KKJ coordinate that will be transformed.
     * @return the transformed coordinate in WGS84 coordinate system.
     */
    static QTM_NAMESPACE::QGeoCoordinate transformToWGS84(const KKJ &fromCoordinate);
};

#endif // COORDINATESYSTEMTRANSFORMER_H
