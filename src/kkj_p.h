#ifndef KKJ_P_H
#define KKJ_P_H

#include <QtGlobal>

class KKJ;

/**
 * A private member class for class KKJ.
 */
class KKJPrivate
{
public:
    /**
     * Destructor.
     */
    virtual ~KKJPrivate();

private:
    /**
     * Initializes the private class.
     * @param northing the northing of the coordinate.
     * @param easting the easting of the coordinate.
     */
    void init(unsigned int northing, unsigned int easting);

    /// The northing of the coordinate.
    unsigned int northing;

    /// The easting of the coordinate.
    unsigned int easting;

    /// The concrete class owning this private implementation member.
    KKJ *q_ptr;

    Q_DECLARE_PUBLIC(KKJ)

};

#endif // KKJ_P_H
