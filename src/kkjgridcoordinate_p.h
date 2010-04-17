#ifndef KKJGRIDCOORDINATE_P_H
#define KKJGRIDCOORDINATE_P_H

#include <QtGlobal>

class KKJGridCoordinate;

/**
 * A private member class for class KKJGridCoordinate.
 */
class KKJGridCoordinatePrivate
{
public:
    /**
     * Destructor.
     */
    virtual ~KKJGridCoordinatePrivate();

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
    KKJGridCoordinate *q_ptr;

    Q_DECLARE_PUBLIC(KKJGridCoordinate)

};

#endif // KKJGRIDCOORDINATE_P_H
