#ifndef KKJ_H
#define KKJ_H

#include <QtGlobal>

class KKJPrivate;

/**
 * A class representing the Finnish KKJ coordinate.
 */
class KKJ
{
public:
    /**
     * Constructs a new KKJ coordinate with the given values.
     * @param northing the northing coordinate.
     * @param easting the easting coordinate.
     */
    KKJ(unsigned int northing, unsigned int easting);

    /**
     * Destructor.
     */
    virtual ~KKJ();

    /**
     * Equals operator.
     * Tests the equality of this coordinate and another coordinate and returns \c true
     * if the coordinates represent the same position.
     * @param rhs the other coordinate to test against.
     * @return \c true if the coordinates are the same, \c false otherwise.
     */
    bool operator==(const KKJ &rhs) const;

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
    KKJ(KKJPrivate &dd, unsigned int northing, unsigned int easting);


private:
    /// Pointer to the private member
    KKJPrivate *const d_ptr;

    Q_DECLARE_PRIVATE(KKJ)

};

#endif // KKJ_H
