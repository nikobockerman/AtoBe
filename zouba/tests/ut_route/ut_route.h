#ifndef UT_ROUTE_H
#define UT_ROUTE_H

#include <QtTest/QtTest>
#include <QObject>

#include <route_p.h>

Q_DECLARE_METATYPE(RoutePrivate*);

class Ut_Route : public QObject
{
    Q_OBJECT

public:

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testParseReply();
    void testSetFromLocation();
    void testSetToLocation();

private:
    RoutePrivate *m_subject;
};
#endif // UT_ROUTE_H
