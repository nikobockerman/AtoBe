#ifndef GPSCONTROLLER_H
#define GPSCONTROLLER_H

#include "location.h"

#include "gpscontroller_p.h"

#include <QObject>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>

QTM_USE_NAMESPACE

class GpsController : public QObject
{
  Q_OBJECT

public:
  GpsController();
  GpsController( GpsControllerPrivate *gpsControllerPrivate );

  ~GpsController();

public Q_SLOTS:
  void getGps();
  void useFakeGps( const QString &fakeLocationLabel );
  void useLiveGps();

Q_SIGNALS:
  void locationChanged( Location *newLocation );

private:
    GpsControllerPrivate *q;
};

#endif // GPSCONTROLLER_H
