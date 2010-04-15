#ifndef UT_GPSCONTROLLER_H
#define UT_GPSCONTROLLER_H

#include <QtTest/QtTest>
#include <QObject>

class GpsController;
class MyGpsControllerPrivate;
class Location;

Q_DECLARE_METATYPE(GpsController*);
Q_DECLARE_METATYPE(MyGpsControllerPrivate*);
Q_DECLARE_METATYPE(Location*);

class Ut_GpsController : public QObject
{
Q_OBJECT

public:

private slots:
  void init();
  void cleanup();
  void initTestCase();
  void cleanupTestCase();
  void testGetGpsWithNoGpsUpdates();
  void testGetGpsWithGpsUpdates();
  void testFakeGps();

private:
  GpsController *m_subject;
  MyGpsControllerPrivate *m_subject_p;
};
#endif // UT_GPSCONTROLLER_H
