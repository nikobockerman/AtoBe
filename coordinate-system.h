#ifndef COORDINATE_SYSTEM_H
#define COORDINATE_SYSTEM_H

// Type for KKJ x/y coordinates
typedef unsigned int KKJ;

/**
 * Transformes WGS84 longitude/latitude coordinates to KKJ x/y coordinates.
 * @param longitude the input longitude in degrees
 * @param latitude the input latitude in degrees
 * @param outX the result x (easting)
 * @param outY the result y (northing)
 */
void WGS84lola_to_KKJxy(double longitude, double latitude, KKJ *outX, KKJ *outY);

/**
 * Transformes KKJ x/y coordinates to WGS84 longitude/latitude coordinates.
 * @param x the input x (easting)
 * @param y the input y (northing)
 * @param outLongitude the result longitude in degrees
 * @param outLatitude the result latitude in degrees
 */
void KKJxy_to_WGS84lola(KKJ x, KKJ y, double *outLongitude, double *outLatitude);

#endif
