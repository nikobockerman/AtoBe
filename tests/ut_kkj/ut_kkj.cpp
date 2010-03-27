#include "kkj.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(KKJ, ConstructorValuesReceivedViaGetters)
{
    unsigned int northing = 6682815;
    unsigned int easting = 2556686;
    KKJ kkj(northing , easting);
    ASSERT_EQ(northing, kkj.northing());
    ASSERT_EQ(easting, kkj.easting());
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
