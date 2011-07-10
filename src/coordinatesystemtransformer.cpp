#include "coordinatesystemtransformer.h"

#include <math.h>


using namespace QTM_NAMESPACE;

/**
 * A class representing geographical coordinates from the Finnish KKJ coordinate system.
 */
class KKJGeoCoordinate {
    // The latitude of the coordinate
    double mLatitude;
    // The longitude of the coordinate
    double mLongitude;

public:
    /**
     * An empty constructor.
     * Constructs a new KKJ geographical coordinate with default coordinate values.
     * Note that the constructed coordinate doesn't necessarily represent any real location
     * on earth.
     */
    KKJGeoCoordinate();

    /**
     * Constructs a new KKJ geographical coordinate.
     * @param latitude the latitude of the coordinate
     * @param longitude the longitude of the coordinate
     */
    KKJGeoCoordinate(double latitude, double longitude);

    /**
     * Gets the latitude of this coordinate.
     * @return the latitude of this coordinate
     */
    double latitude() const;

    /**
     * Gets the longitude of this coordinate.
     * @return the longitude of this coordinate
     */
    double longitude() const;

    /**
     * Sets the latitude of this coordinate.
     * @param latitude the new latitude
     */
    void setLatitude(double latitude);

    /**
     * Sets the longitude of this coordinate.
     * @param longitude the new latitude
     */
    void setLongitude(double longitude);

};


KKJGeoCoordinate::KKJGeoCoordinate() :
        mLatitude(0.0),
        mLongitude(0.0)
{
}

KKJGeoCoordinate::KKJGeoCoordinate(double latitude, double longitude) :
        mLatitude(latitude),
        mLongitude(longitude)
{
}

double KKJGeoCoordinate::latitude() const
{
    return mLatitude;
}

double KKJGeoCoordinate::longitude() const
{
    return mLongitude;
}

void KKJGeoCoordinate::setLatitude(double latitude)
{
    mLatitude = latitude;
}

void KKJGeoCoordinate::setLongitude(double longitude)
{
    mLongitude = longitude;
}


/**
 * A Hayford reference ellipsoid
 */
class HayfordEllipsoid {
public:
    // Equatorial radius
    static const double a;
    // Flattening
    static const double f;
    // Polar radius
    static const double b;
    // Polar radius squared
    static const double bb;
    // Polar radius of curvature
    static const double c;
    // First eccentricity squared
    static const double ee;
    // Second flattening
    static const double n;
    // Second flattening squared
    static const double nn;
};

const double HayfordEllipsoid::a = 6378388.0;
const double HayfordEllipsoid::f  = 1.0 / 297.0;
const double HayfordEllipsoid::b  = (1.0 - f) * a;
const double HayfordEllipsoid::bb = b * b;
const double HayfordEllipsoid::c  = (a / b) * a;
const double HayfordEllipsoid::ee = (a * a - bb) / bb; // should probably be (a * a - bb) / (a * a)
const double HayfordEllipsoid::n = (a - b) / (a + b);
const double HayfordEllipsoid::nn = n * n;



// Degrees to radians
double radians(double deg) {
    return deg * M_PI / 180.0;
}

// Radians to degrees
double degrees(double rad) {
    return rad * 180.0 / M_PI;
}


/**
 * A class providing KKJ zone information.
 */
class KKJZone {
private:
    // Storage for the central meridians and false eastings of the zones
    static const double KKJ_ZONE_INFO[6][2];

    // Minimum zone number
    static const int MIN_ZONE = 0;
    // Maximum zone number
    static const int MAX_ZONE = 5;

public:
    /**
     * Determines a zone number from the KKJ easting value. If the easting is not within any of
     * the zones, -1 is returned.
     * @param kkj the KKJ coordinate
     * @return the zone number or -1 on error
     */
    static int getZoneNumberFromEasting(const KKJGridCoordinate &kkj);

    /**
     * Determines a zone number from the KKJ longitude value. If the longitude is not within any of
     * the zones, -1 is returned.
     * @param kkj the KKJ coordinate
     * @return the zone number or -1 on error
     */
    static int getZoneNumberFromLongitude(const KKJGeoCoordinate &kkj);

    /**
     * Gets the central meridian in degrees of the given zone. The zone number must be
     * on the interval [0, 5]. If an invalid zone number is given, 0.0 is returned.
     * @param zoneNumber the zone number
     * @return the central meridian of the zone or 0.0 on error
     */
    static double getCentralMeridianOfZone(int zoneNumber);

    /**
     * Gets the false easting in metres of the given zone. The zone number must be
     * on the interval [0, 5]. If an invalid zone number is given, 0.0 is returned.
     * @param zoneNumber the zone number
     * @return the false easting of the zone or 0.0 on error
     */
    static double getFalseEastingOfZone(int zoneNumber);
};

                                        // central meridian
                                                  // false easting
const double KKJZone::KKJ_ZONE_INFO[6][2] = { {18.0,  500000.0},  // zone 0
                                              {21.0, 1500000.0},
                                              {24.0, 2500000.0},
                                              {27.0, 3500000.0},
                                              {30.0, 4500000.0},
                                              {33.0, 5500000.0} };// zone 5


int KKJZone::getZoneNumberFromEasting(const KKJGridCoordinate &kkj) {
    int zoneNumber = floor(kkj.easting() / 1000000.0);
    if (zoneNumber < MIN_ZONE || zoneNumber > MAX_ZONE) {
        zoneNumber = -1;
    }

    return zoneNumber;
}

int KKJZone::getZoneNumberFromLongitude(const KKJGeoCoordinate &kkj) {
    // determine the zonenumber from KKJ easting
    // takes KKJ zone which has center meridian
    // longitude nearest (in math value) to
    // the given KKJ longitude
    int zoneNumber = MAX_ZONE;
    while (zoneNumber >= MIN_ZONE) {
        if (fabs(kkj.longitude() - KKJ_ZONE_INFO[zoneNumber][0]) <= 1.5) {
            break;
        }
        zoneNumber--;
    }

    return zoneNumber;
}

double KKJZone::getCentralMeridianOfZone(int zoneNumber)
{
    if (zoneNumber >= MIN_ZONE && zoneNumber <= MAX_ZONE) {
        return KKJ_ZONE_INFO[zoneNumber][0];
    }

    return 0.0;
}

double KKJZone::getFalseEastingOfZone(int zoneNumber)
{
    if (zoneNumber >= MIN_ZONE && zoneNumber <= MAX_ZONE) {
        return KKJ_ZONE_INFO[zoneNumber][1];
    }

    return 0.0;
}


/**
 * Transforms a KKJ geographical coordinate to a WGS84 geographical coordinate.
 * @param fromCoordinate the input coordinate
 * @return the transformed coordinate
 */
QGeoCoordinate transformToWGS84GeoCoordinate(const KKJGeoCoordinate &fromCoordinate) {
    double kkjla = fromCoordinate.latitude();
    double kkjlo = fromCoordinate.longitude();

    double dLa = (0.124867E+01 + -0.269982E+00 * kkjla + 0.191330E+00 * kkjlo + 0.356119E-02 * kkjla * kkjla + -0.122312E-02 * kkjla * kkjlo + -0.335514E-03 * kkjlo * kkjlo) / 3600.0;
    double dLo = (-0.286111E+02 + 0.114183E+01 * kkjla + -0.581428E+00 * kkjlo + -0.152421E-01 * kkjla * kkjla + 0.118177E-01 * kkjla * kkjlo + 0.826646E-03 * kkjlo * kkjlo) / 3600.0;

    return QGeoCoordinate(kkjla + dLa, kkjlo + dLo);
}


/**
 * Transforms a WGS84 geographical coordinate to a KKJ geographical coordinate.
 * @param fromCoordinate the input coordinate
 * @return the transformed coordinate
 */
KKJGeoCoordinate transformToKKJGeoCoordinate(const QGeoCoordinate &fromCoordinate) {
    double longitude = fromCoordinate.longitude();
    double latitude = fromCoordinate.latitude();

    double dLa = (-0.124766E+01 + 0.269941E+00 * latitude + -0.191342E+00 * longitude + -0.356086E-02 * latitude * latitude + 0.122353E-02 * latitude * longitude + 0.335456E-03 * longitude * longitude) / 3600.0;
    double dLo = (0.286008E+02 + -0.114139E+01 * latitude + 0.581329E+00 * longitude + 0.152376E-01 * latitude * latitude + -0.118166E-01 * latitude * longitude + -0.826201E-03 * longitude * longitude) / 3600.0;

    return KKJGeoCoordinate(latitude + dLa, longitude + dLo);
}


/**
 * Transforms a KKJ geographical coordinate to a KKJ rectangular grid coordinate.
 * @param fromCoordinate the input coordinate
 * @param zoneNumber the zone number in which the input coordinate resides
 * @return the transformed coordinate
 */
KKJGridCoordinate transformToKKJGridCoordinate(const KKJGeoCoordinate &fromCoordinate) {
    int zoneNumber = KKJZone::getZoneNumberFromLongitude(fromCoordinate);
    double Lo = radians(fromCoordinate.longitude()) - radians(KKJZone::getCentralMeridianOfZone(zoneNumber));
    double cosLa = cos(radians(fromCoordinate.latitude()));
    double NN = HayfordEllipsoid::ee * cosLa * cosLa;
    double LaF = atan(tan(radians(fromCoordinate.latitude())) / cos(Lo * sqrt(1.0 + NN)));
    double cosLaF = cos(LaF);
    double t = (tan(Lo) * cosLaF) / sqrt(1.0 + HayfordEllipsoid::ee * cosLaF * cosLaF);
    double A = HayfordEllipsoid::a / (1.0 + HayfordEllipsoid::n);
    double A1 = A * (1.0 + HayfordEllipsoid::nn / 4.0 + HayfordEllipsoid::nn * HayfordEllipsoid::nn / 64.0);
    double A2 = A * 1.5 * HayfordEllipsoid::n * (1.0 - HayfordEllipsoid::nn / 8.0);
    double A3 = A * 0.9375 * HayfordEllipsoid::nn * (1.0 - HayfordEllipsoid::nn / 4.0);
    double A4 = A * 35.0 / 48.0 * HayfordEllipsoid::nn * HayfordEllipsoid::n;

    unsigned int outY = A1 * LaF - A2 * sin(2.0 * LaF) + A3 * sin(4.0 * LaF) - A4 * sin(6.0 * LaF);
    unsigned int outX = HayfordEllipsoid::c * log(t + sqrt(1.0 + t * t)) + 500000.0 + zoneNumber * 1000000.0;
    return KKJGridCoordinate(outY, outX);
}

/**
 * Transforms a KKJ rectangular grid coordinate to a KKJ geographical coordinate.
 * @param fromCoordinate the input coordinate
 * @return the transformed coordinate
 */
KKJGeoCoordinate transformToKKJGeoCoordinate(const KKJGridCoordinate &fromCoordinate) {
    // Scan iteratively the target area, until find matching
    // KKJ coordinate value. Area is defined with Hayford Ellipsoid.
    double minLo = 18.5;
    double maxLo = 32.0;
    double minLa = 59.0;
    double maxLa = 70.5;

    int i = 1;

    KKJGeoCoordinate ret;

    while (i < 35) {
        double deltaLo = maxLo - minLo;
        double deltaLa = maxLa - minLa;
        ret.setLongitude(minLo + 0.5 * deltaLo);
        ret.setLatitude(minLa + 0.5 * deltaLa);
        KKJGridCoordinate kkj = transformToKKJGridCoordinate(ret);
        if (kkj.northing() < fromCoordinate.northing()) {
            minLa = minLa + 0.45 * deltaLa;
        } else {
            maxLa = minLa + 0.55 * deltaLa;
        }

        if (kkj.easting() < fromCoordinate.easting()) {
            minLo = minLo + 0.45 * deltaLo;
        } else {
            maxLo = minLo + 0.55 * deltaLo;
        }

        i++;
    }

    return ret;
}


KKJGridCoordinate CoordinateSystemTransformer::transformToKKJ(const QGeoCoordinate &fromCoordinate)
{
    KKJGeoCoordinate tmpKKJ = transformToKKJGeoCoordinate(fromCoordinate);
    return transformToKKJGridCoordinate(tmpKKJ);
}

QGeoCoordinate CoordinateSystemTransformer::transformToWGS84(const KKJGridCoordinate &fromCoordinate)
{
    KKJGeoCoordinate tmpKKJ = transformToKKJGeoCoordinate(fromCoordinate);
    return transformToWGS84GeoCoordinate(tmpKKJ);
}
