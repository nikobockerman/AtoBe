#include "kkj.h"
#include "kkj_p.h"

KKJPrivate::~KKJPrivate()
{
}

void KKJPrivate::init(unsigned int northing, unsigned int easting)
{
    this->northing = northing;
    this->easting = easting;
}


KKJ::KKJ(unsigned int northing, unsigned int easting) :
        d_ptr(new KKJPrivate)
{
    Q_D(KKJ);
    d->q_ptr = this;
    d->init(northing, easting);
}

KKJ::KKJ(KKJPrivate &dd, unsigned int northing, unsigned int easting) :
        d_ptr(&dd)
{
    Q_D(KKJ);
    d->q_ptr = this;
    d->init(northing, easting);
}

KKJ::~KKJ()
{
}

bool KKJ::operator==(const KKJ &rhs) const
{
    return northing() == rhs.northing() && easting() == rhs.easting();
}

KKJ& KKJ::operator=(const KKJ &rhs)
{
    Q_D(KKJ);
    d->northing = rhs.northing();
    d->easting = rhs.easting();

    return *this;
}

unsigned int KKJ::northing() const
{
    Q_D(const KKJ);
    return d->northing;
}

unsigned int KKJ::easting() const
{
    Q_D(const KKJ);
    return d->easting;
}
