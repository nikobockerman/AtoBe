#include "kkj.h"

KKJ::KKJ(unsigned int northing, unsigned int easting) :
        mNorthing(northing),
        mEasting(easting)
{
}

KKJ::~KKJ()
{
}

unsigned int KKJ::northing() const
{
    return mNorthing;
}

unsigned int KKJ::easting() const
{
    return mEasting;
}
