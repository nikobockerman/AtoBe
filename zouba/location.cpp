#include "location.h"

#include "location_p.h"

#include "ytv.h"

#include <QString>
#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QXmlStreamReader>
#include <QDebug>
#include <QXmlStreamAttributes>
#include <QStringRef>
#include <QGeoPositionInfo>

#include <math.h>

const double Location::KkjZoneInfo[6][2] = {
  {18.0,  500000.0},
  {21.0, 1500000.0},
  {24.0, 2500000.0},
  {27.0, 3500000.0},
  {30.0, 4500000.0},
  {33.0, 5500000.0}
};

QTM_USE_NAMESPACE

Location::Location( QString x, QString y ) :
  q( new LocationPrivate( x, y ) ),
  manager( new QNetworkAccessManager(this) )
{
  connect( manager, SIGNAL( finished(QNetworkReply*) ), this, SLOT( replyFinished(QNetworkReply*) ) );
}

Location::Location( const QGeoPositionInfo &positionInfo ) :
  q( new LocationPrivate() ),
  manager(0)
{
  qreal latitude = positionInfo.coordinate().latitude();
  qreal longitude = positionInfo.coordinate().longitude();

  KKJ outX(0);
  KKJ outY(0);

  WGS84lola_to_KKJxy( longitude, latitude, &outX, &outY);

  q->setX( outX );
  q->setY( outY );
  q->setValid( true );
}

Location::Location( const Location &from ) :
  QObject(0),
  q( new LocationPrivate() ),
  manager(0)
{
  q->setX( from.x() );
  q->setY( from.y() );
  q->setValid( from.isValid() );
  if ( from.manager != 0 ) {
    manager = new QNetworkAccessManager(this);
    connect( manager, SIGNAL( finished(QNetworkReply*) ), this, SLOT( replyFinished(QNetworkReply*) ) );
  }
}

Location::Location() :
  q( new LocationPrivate() ),
  manager( new QNetworkAccessManager(this) )
{
  connect( manager, SIGNAL( finished(QNetworkReply*) ), this, SLOT( replyFinished(QNetworkReply*) ) );
}

Location::~Location()
{
  delete q;
  q=0;
  delete manager;
  manager=0;
}

Location &Location::operator=( const Location &from )
{
  q = new LocationPrivate();
  q->setX( from.x() );
  q->setY( from.y() );
  q->setValid( from.isValid() );
  if ( from.manager != 0 ) {
    manager = new QNetworkAccessManager(this);
    connect( manager, SIGNAL( finished(QNetworkReply*) ), this, SLOT( replyFinished(QNetworkReply*) ) );
  } else {
    manager = 0;
  }
  
  return *this;
}

void Location::resolveAddress( QString address )
{
  QUrl fullUrl( Ytv::Url );

  fullUrl.addEncodedQueryItem( "key", address.toAscii().toPercentEncoding() );
  fullUrl.addQueryItem( "user", Ytv::Username );
  fullUrl.addQueryItem( "pass", Ytv::Password );

  manager->get( QNetworkRequest( fullUrl ) );
}

void Location::replyFinished( QNetworkReply * reply )
{
  q->parseReply( reply->readAll() );

  if ( isValid() ) {
    emit( becomeValid() );
  }
}

QString Location::x() const
{
  return q->x();
}

QString Location::y() const
{
  return q->y();
}

bool Location::isValid() const
{
  return q->isValid();
}


// Degrees to radians
double Location::radians(double deg)
{
  return deg * M_PI / 180.0;
}

// Radians to degrees
double Location::degrees(double rad)
{
  return rad * 180.0 / M_PI;
}

// Function:  KKJ_Zone_I
int Location::KKJ_Zone_I(KKJ easting)
{
  int zoneNumber = floor(easting / 1000000.0);
  if (zoneNumber < 0 || zoneNumber > 5) {
    zoneNumber = -1;
  }

  return zoneNumber;
}

// Function:  KKJ_Zone_Lo
int Location::KKJ_Zone_Lo(double kkjlo)
{
  // determine the zonenumber from KKJ easting
  // takes KKJ zone which has center meridian
  // longitude nearest (in math value) to
  // the given KKJ longitude
  int zoneNumber = 5;
  while (zoneNumber >= 0) {
    if (fabs(kkjlo - KkjZoneInfo[zoneNumber][0]) <= 1.5) {
      break;
    }
    zoneNumber--;
  }

  return zoneNumber;
}


// Function:  KKJlalo_to_WGS84lalo
void Location::KKJlola_to_WGS84lola(double kkjlo, double kkjla, double *outLongitude, double *outLatitude)
{
  double dLa = radians(0.124867E+01 + -0.269982E+00 * kkjla + 0.191330E+00 * kkjlo + 0.356119E-02 * kkjla * kkjla + -0.122312E-02 * kkjla * kkjlo + -0.335514E-03 * kkjlo * kkjlo) / 3600.0;
  double dLo = radians(-0.286111E+02 + 0.114183E+01 * kkjla + -0.581428E+00 * kkjlo + -0.152421E-01 * kkjla * kkjla + 0.118177E-01 * kkjla * kkjlo + 0.826646E-03 * kkjlo * kkjlo) / 3600.0;

  *outLatitude = degrees(radians(kkjla) + dLa);
  *outLongitude = degrees(radians(kkjlo) + dLo);
}


// Function:  WGS84lalo_to_KKJlalo
void Location::WGS84lola_to_KKJlola(double longitude, double latitude, double *outLongitude, double *outLatitude) 
{
  double dLa = radians(-0.124766E+01 + 0.269941E+00 * latitude + -0.191342E+00 * longitude + -0.356086E-02 * latitude * latitude + 0.122353E-02 * latitude * longitude + 0.335456E-03 * longitude * longitude) / 3600.0;
  double dLo = radians(0.286008E+02 + -0.114139E+01 * latitude + 0.581329E+00 * longitude + 0.152376E-01 * latitude * latitude + -0.118166E-01 * latitude * longitude + -0.826201E-03 * longitude * longitude) / 3600.0;

  *outLatitude = degrees(radians(latitude) + dLa);
  *outLongitude = degrees(radians(longitude) + dLo);
}


// Function:  KKJlalo_to_KKJxy
void Location::KKJlola_to_KKJxy(double lon, double lat, int zoneNumber, KKJ *outX, KKJ *outY) 
{
  // Hayford ellipsoid
  double a = 6378388.0;
  double f  = 1.0 / 297.0;
  double b  = (1.0 - f) * a;
  double bb = b * b;
  double c  = (a / b) * a;
  double ee = (a * a - bb) / bb;
  double n = (a - b) / (a + b);
  double nn = n * n;

  double Lo = radians(lon) - radians(KkjZoneInfo[zoneNumber][0]);
  double cosLa = cos(radians(lat));
  double NN = ee * cosLa * cosLa;
  double LaF = atan(tan(radians(lat)) / cos(Lo * sqrt(1.0 + NN)));
  double cosLaF = cos(LaF);
  double t = (tan(Lo) * cosLaF) / sqrt(1.0 + ee * cosLaF * cosLaF);
  double A = a / (1.0 + n);
  double A1 = A * (1.0 + nn / 4.0 + nn * nn / 64.0);
  double A2 = A * 1.5 * n * (1.0 - nn / 8.0);
  double A3 = A * 0.9375 * nn * (1.0 - nn / 4.0);
  double A4 = A * 35.0 / 48.0 * nn * n;

  *outY = A1 * LaF - A2 * sin(2.0 * LaF) + A3 * sin(4.0 * LaF) - A4 * sin(6.0 * LaF);
  *outX = c * log(t + sqrt(1.0 + t * t)) + 500000.0 + zoneNumber * 1000000.0;
}

// Function:  KKJxy_to_KKJlalo
void Location::KKJxy_to_KKJlola(KKJ x, KKJ y, double *outLongitude, double *outLatitude)
{
  // Scan iteratively the target area, until find matching
  // KKJ coordinate value.  Area is defined with Hayford Ellipsoid.
  int zoneNumber = KKJ_Zone_I(x);
  double minLo = radians(18.5);
  double maxLo = radians(32.0);
  double minLa = radians(59.0);
  double maxLa = radians(70.5);

  int i = 1;
  KKJ tmpX, tmpY;

  while (i < 35) {
    double deltaLo = maxLo - minLo;
    double deltaLa = maxLa - minLa;
    *outLongitude = degrees(minLo + 0.5 * deltaLo);
    *outLatitude = degrees(minLa + 0.5 * deltaLa);
    KKJlola_to_KKJxy(*outLongitude, *outLatitude, zoneNumber, &tmpX, &tmpY);
    if (tmpY < y) {
      minLa = minLa + 0.45 * deltaLa;
    } else {
      maxLa = minLa + 0.55 * deltaLa;
    }

    if (tmpX < x) {
      minLo = minLo + 0.45 * deltaLo;
    } else {
      maxLo = minLo + 0.55 * deltaLo;
    }

    i++;
  }
}

void Location::WGS84lola_to_KKJxy(double longitude, double latitude, KKJ *outX, KKJ *outY)
{
  double kkjlo, kkjla;

  WGS84lola_to_KKJlola(longitude, latitude, &kkjlo, &kkjla);
  int zoneNumber = KKJ_Zone_Lo(kkjlo);
  KKJlola_to_KKJxy(kkjlo, kkjla, zoneNumber, outX, outY);
}

void Location::KKJxy_to_WGS84lola(KKJ x, KKJ y, double *outLongitude, double *outLatitude)
{
  double kkjlo, kkjla;

  KKJxy_to_KKJlola(x, y, &kkjlo, &kkjla);
  KKJlola_to_WGS84lola(kkjlo, kkjla, outLongitude, outLatitude);

}

