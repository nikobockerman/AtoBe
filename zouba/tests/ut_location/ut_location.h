#ifndef UT_LOCATION_H
#define UT_LOCATION_H

#include <QtTest/QtTest>
#include <QObject>

#include <location_p.h>

Q_DECLARE_METATYPE(LocationPrivate*);

class Ut_Location : public QObject
{
    Q_OBJECT

public:

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testParseReply();
    void testSet();

private:
    LocationPrivate *m_subject;
};
#endif // UT_LOCATION_H
