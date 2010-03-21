#ifndef UT_TEMPLATE_H
#define UT_TEMPLATE_H

#include <QObject>

class Ut_template : public QObject
{
    Q_OBJECT

private slots:
    // Will be called before the first testfunction is executed.
    void initTestCase();
    // Will be called after the last testfunction was executed.
    void cleanupTestCase();
    // Will be called before each testfunction is executed.
    void init();
    // Will be called after every testfunction.
    void cleanup();

};

#endif // UT_TEMPLATE_H
