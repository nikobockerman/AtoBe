#ifndef GPSLOCATION_H
#define GPSLOCATION_H

#include <QObject>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>
#include <math.h>

#include "location.h"

typedef uint KKJ;

QTM_USE_NAMESPACE;

class GpsLocation : public QObject, public Location
{
    Q_OBJECT
public:
    explicit GpsLocation(QObject *parent = 0);
    ~GpsLocation();

    bool isUpdating() const;

signals:
    void gpsLocationChanged(GpsLocation *newLocation);
    void gpsLocationUpdatingChanged(bool isEnabled);

public slots:
    void enableGps(bool enable);

private slots:
    void updateLocation( QGeoPositionInfo positionInfo );
    void timeout();

private:
    void calculateXY();

    QGeoPositionInfoSource *m_gps;
    bool m_active;
    qreal latitude, longitude;

};

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

// Degrees to radians
double radians(double deg);

// Radians to degrees
double degrees(double rad);

// Constants
// Longitude0 and Center meridian of KKJ bands
//static const double KkjZoneInfo[][2];

// Function:  KKJ_Zone_I
int KKJ_Zone_I(KKJ easting);

// Function:  KKJ_Zone_Lo
int KKJ_Zone_Lo(double kkjlo);

// Function:  KKJlalo_to_WGS84lalo
void KKJlola_to_WGS84lola(double kkjlo, double kkjla, double *outLongitude, double *outLatitude);

// Function:  WGS84lalo_to_KKJlalo
void WGS84lola_to_KKJlola(double longitude, double latitude, double *outLongitude, double *outLatitude);

// Function:  KKJlalo_to_KKJxy
void KKJlola_to_KKJxy(double lon, double lat, int zoneNumber, KKJ *outX, KKJ *outY);

// Function:  KKJxy_to_KKJlalo
void KKJxy_to_KKJlola(KKJ x, KKJ y, double *outLongitude, double *outLatitude);


#endif // GPSLOCATION_H
