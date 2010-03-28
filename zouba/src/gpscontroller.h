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

public Q_SLOTS:
  void updateLocation( QGeoPositionInfo positionInfo );
  void getGps();
  void useFakeGps( Location *fakeLocation );
  void useLiveGps();

Q_SIGNALS:
  void locationChanged( Location *newLocation );

private:
  QGeoPositionInfoSource *m_location;
  Location               *m_currentLocation;
  bool                    m_useFakeLocation;
};

#endif // GPSCONTROLLER_H
