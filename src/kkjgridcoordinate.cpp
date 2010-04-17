#include "kkjgridcoordinate.h"
#include "kkjgridcoordinate_p.h"

KKJGridCoordinatePrivate::~KKJGridCoordinatePrivate()
{
}

void KKJGridCoordinatePrivate::init(unsigned int northing, unsigned int easting)
{
    this->northing = northing;
    this->easting = easting;
}


KKJGridCoordinate::KKJGridCoordinate(unsigned int northing, unsigned int easting) :
        d_ptr(new KKJGridCoordinatePrivate)
{
    Q_D(KKJGridCoordinate);
    d->q_ptr = this;
    d->init(northing, easting);
}

KKJGridCoordinate::KKJGridCoordinate(KKJGridCoordinatePrivate &dd, unsigned int northing, unsigned int easting) :
        d_ptr(&dd)
{
    Q_D(KKJGridCoordinate);
    d->q_ptr = this;
    d->init(northing, easting);
}

KKJGridCoordinate::~KKJGridCoordinate()
{
}

bool KKJGridCoordinate::operator==(const KKJGridCoordinate &rhs) const
{
    return northing() == rhs.northing() && easting() == rhs.easting();
}

KKJGridCoordinate& KKJGridCoordinate::operator=(const KKJGridCoordinate &rhs)
{
    Q_D(KKJGridCoordinate);
    d->northing = rhs.northing();
    d->easting = rhs.easting();

    return *this;
}

unsigned int KKJGridCoordinate::northing() const
{
    Q_D(const KKJGridCoordinate);
    return d->northing;
}

unsigned int KKJGridCoordinate::easting() const
{
    Q_D(const KKJGridCoordinate);
    return d->easting;
}
