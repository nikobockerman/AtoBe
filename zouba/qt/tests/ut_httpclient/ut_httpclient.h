#ifndef UT_HTTPCLIENT_H
#define UT_HTTPCLIENT_H

#include <QtTest/QtTest>
#include <QObject>

#include <httpclient_p.h>

Q_DECLARE_METATYPE(HttpClientPrivate*);

class Ut_HttpClient : public QObject
{
    Q_OBJECT

public:

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testParseReply();

private:
    HttpClientPrivate *m_subject;
};
#endif // UT_HTTPCLIENT_H
