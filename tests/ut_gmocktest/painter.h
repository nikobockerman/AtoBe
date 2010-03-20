#ifndef PAINTER_H
#define PAINTER_H

class Turtle;

class Painter
{
    Turtle *turtle;

public:
    Painter(Turtle *turtle);
    virtual ~Painter();

    bool DrawCircle(int x, int y, int radius);
};

#endif // PAINTER_H
