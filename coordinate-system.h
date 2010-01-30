#ifndef COORDINATE_SYSTEM_H
#define COORDINATE_SYSTEM_H

void wgs84_to_kkj2(double inLatitude, double inLongitude, double *outLatitude, double *outLongitude);

void kkj2_to_wgs84(double inLatitude, double inLongitude, double *outLatitude, double *outLongitude);

#endif
