#include "painter.h"
#include "turtle.h"

Painter::Painter(Turtle *turtle) :
        turtle(turtle)
{
}

Painter::~Painter() {
}

bool Painter::DrawCircle(int x, int y, int radius) {
    turtle->PenDown();
    emit DrawCircleCalled(x, y, radius);
    return true;
}
