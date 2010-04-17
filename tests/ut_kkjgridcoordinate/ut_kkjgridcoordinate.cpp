#include "kkjgridcoordinate.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "stlhelpers.h"

class KKJGridCoordinateTest : public ::testing::Test
{
public:
    const unsigned int northing;
    const unsigned int easting;

    KKJGridCoordinateTest() :
        northing(6682815),
        easting(2556686)
    {
    }
};

TEST_F(KKJGridCoordinateTest, ConstructorValuesReceivedViaGetters)
{
    KKJGridCoordinate kkj(northing , easting);
    ASSERT_EQ(northing, kkj.northing());
    ASSERT_EQ(easting, kkj.easting());
}

TEST_F(KKJGridCoordinateTest, EqualsOperatorReturnsTrueForEqualCoordinates)
{
    KKJGridCoordinate kkj1(northing, easting);
    KKJGridCoordinate kkj2(northing, easting);
    ASSERT_TRUE(kkj1 == kkj2);
}

TEST_F(KKJGridCoordinateTest, EqualsOperatorReturnsFalseForCoordinatesWithDifferentNorthing)
{
    KKJGridCoordinate kkj1(northing - 1, easting);
    KKJGridCoordinate kkj2(northing, easting);
    ASSERT_FALSE(kkj1 == kkj2);
}

TEST_F(KKJGridCoordinateTest, EqualsOperatorReturnsFalseForCoordinatesWithDifferentEasting)
{
    KKJGridCoordinate kkj1(northing, easting - 1);
    KKJGridCoordinate kkj2(northing, easting);
    ASSERT_FALSE(kkj1 == kkj2);
}

TEST_F(KKJGridCoordinateTest, AssignmentOperator)
{
    const KKJGridCoordinate kkj1(northing, easting);
    KKJGridCoordinate kkj2(0, 0);
    kkj2 = kkj1;
    ASSERT_EQ(northing, kkj2.northing());
    ASSERT_EQ(easting, kkj2.easting());
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
