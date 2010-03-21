#ifndef LOCATION_H
#define LOCATION_H

#include "location_p.h"

#include <QString>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QGeoPositionInfo>
#include <math.h>

QTM_USE_NAMESPACE

class Location : public QObject
{
Q_OBJECT

public:
  Location( const QString &x, const QString &y, const QString &label=QString() );
  Location( const QGeoPositionInfo &positionInfo, const QString &label=QString() );
  Location( const Location &from );
  Location &operator=( const Location &from );
  Location( const QString &label=QString() );

  ~Location();

  QString x() const;

  QString y() const;

  void setAddress( const QString &address ) const;
  QString address() const;

  void setLabel( const QString &label ) const;
  QString label() const;

  bool isValid() const;

public Q_SLOTS:
  void resolveAddress( const QString &address );

Q_SIGNALS:
  void becomeValid();

private Q_SLOTS:
  void replyFinished( QNetworkReply * reply );

private:
  LocationPrivate *q;
  QNetworkAccessManager *manager;

  typedef uint KKJ;

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
  static const double KkjZoneInfo[][2];

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

};

#endif // LOCATION_H
