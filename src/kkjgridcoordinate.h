#ifndef KKJGRIDCOORDINATE_H
#define KKJGRIDCOORDINATE_H

#include <QtGlobal>

class KKJGridCoordinatePrivate;

/**
 * A class representing the Finnish KKJ coordinate.
 * This is the rectangular grid coordinate version.
 */
class KKJGridCoordinate
{
public:
    /**
     * Constructs a new KKJ coordinate with the given values.
     * @param northing the northing coordinate.
     * @param easting the easting coordinate.
     */
    KKJGridCoordinate(unsigned int northing, unsigned int easting);

    /**
     * Destructor.
     */
    virtual ~KKJGridCoordinate();

    /**
     * Equals operator.
     * Tests the equality of this coordinate and another coordinate and returns \c true
     * if the coordinates represent the same position.
     * @param rhs the other coordinate to test against.
     * @return \c true if the coordinates are the same, \c false otherwise.
     */
    bool operator==(const KKJGridCoordinate &rhs) const;

    /**
     * Assignment operator.
     * @param rhs the object that is copied.
     * @return this object.
     */
    KKJGridCoordinate& operator=(const KKJGridCoordinate &rhs);

    /**
     * Returns the northing of the coordinate.
     * @return the northing.
     */
    unsigned int northing() const;

    /**
     * Returns the easting of the coordinate.
     * @return the easting.
     */
    unsigned int easting() const;

protected:
    /**
     * Constructs a new KKJ coordinate with the given values.
     * @param dd a private implementation member.
     * @param northing the northing coordinate.
     * @param easting the easting coordinate.
     */
    KKJGridCoordinate(KKJGridCoordinatePrivate &dd, unsigned int northing, unsigned int easting);


private:
    /// Pointer to the private member
    KKJGridCoordinatePrivate *const d_ptr;

    Q_DECLARE_PRIVATE(KKJGridCoordinate)

};

#endif // KKJGRIDCOORDINATE_H
