#ifndef KKJ_H
#define KKJ_H

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
     * Returns the northing of the coordinate.
     * @return the northing.
     */
    unsigned int northing() const;

    /**
     * Returns the easting of the coordinate.
     * @return the easting.
     */
    unsigned int easting() const;

private:
    unsigned int mNorthing;
    unsigned int mEasting;
};

#endif // KKJ_H
