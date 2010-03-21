#ifndef PAINTER_H
#define PAINTER_H

#include <QObject>

class Turtle;

class Painter : public QObject
{
    Q_OBJECT

    Turtle *turtle;

public:
    Painter(Turtle *turtle);
    virtual ~Painter();

    bool DrawCircle(int x, int y, int radius);

signals:
    void DrawCircleCalled(int x, int y, int radius);
};

#endif // PAINTER_H
