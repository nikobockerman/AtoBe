#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(TestSuiteName, TestMethodName)
{
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
