#ifndef GPSCONTROLLER_H
#define GPSCONTROLLER_H

#include "location.h"

#include <QObject>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>

QTM_USE_NAMESPACE

class GpsController : public QObject
{
  Q_OBJECT

public:
  GpsController();

  ~GpsController();

  void stopGps();

public Q_SLOTS:
  void updateLocation( QGeoPositionInfo positionInfo );
  void startGps();

Q_SIGNALS:
  void locationChanged( const Location &newLocation );

private:
  QGeoPositionInfoSource *m_location;
};

#endif // GPSCONTROLLER_H
