#include "kkj.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "stlhelpers.h"

class KKJTest : public ::testing::Test
{
public:
    const unsigned int northing;
    const unsigned int easting;

    KKJTest() :
        northing(6682815),
        easting(2556686)
    {
    }
};

TEST_F(KKJTest, ConstructorValuesReceivedViaGetters)
{
    KKJ kkj(northing , easting);
    ASSERT_EQ(northing, kkj.northing());
    ASSERT_EQ(easting, kkj.easting());
}

TEST_F(KKJTest, EqualsOperatorReturnsTrueForEqualCoordinates)
{
    KKJ kkj1(northing, easting);
    KKJ kkj2(northing, easting);
    ASSERT_TRUE(kkj1 == kkj2);
}

TEST_F(KKJTest, EqualsOperatorReturnsFalseForCoordinatesWithDifferentNorthing)
{
    KKJ kkj1(northing - 1, easting);
    KKJ kkj2(northing, easting);
    ASSERT_FALSE(kkj1 == kkj2);
}

TEST_F(KKJTest, EqualsOperatorReturnsFalseForCoordinatesWithDifferentEasting)
{
    KKJ kkj1(northing, easting - 1);
    KKJ kkj2(northing, easting);
    ASSERT_FALSE(kkj1 == kkj2);
}

TEST_F(KKJTest, AssignmentOperator)
{
    const KKJ kkj1(northing, easting);
    KKJ kkj2(0, 0);
    kkj2 = kkj1;
    ASSERT_EQ(northing, kkj2.northing());
    ASSERT_EQ(easting, kkj2.easting());
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
