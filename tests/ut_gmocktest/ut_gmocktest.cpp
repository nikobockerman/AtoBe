#include "mock_turtle.h"
#include "painter.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::AtLeast;


TEST(PainterTest, TestTurtlePenDownCalledAtLeastOnceWhenDrawCircleCalled)
{
    MockTurtle turtle;
    EXPECT_CALL(turtle, PenDown()).Times(AtLeast(1));

    Painter painter(&turtle);

    EXPECT_TRUE(painter.DrawCircle(0, 0, 10));
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
