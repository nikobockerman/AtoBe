#include "mock_turtle.h"
#include "painter.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <QSignalSpy>
#include "stlhelpers4qt.h"

using ::testing::AtLeast;

TEST(PainterTest, TestTurtlePenDownCalledAtLeastOnceWhenDrawCircleCalled)
{
    MockTurtle turtle;
    EXPECT_CALL(turtle, PenDown()).Times(AtLeast(1));

    Painter painter(&turtle);

    EXPECT_TRUE(painter.DrawCircle(0, 0, 10));
}

TEST(PainterTest, TestSignalEmittedWhenDrawCircleCalled)
{
    MockTurtle turtle;

    Painter painter(&turtle);

    QSignalSpy spy(&painter, SIGNAL(DrawCircleCalled(int,int,int)));

    painter.DrawCircle(0, 0, 10);
    ASSERT_EQ(1, spy.count());
    QList<QVariant> expected = QList<QVariant>() << 0 << 0 << 10;
    ASSERT_EQ(expected, spy.at(0));
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
