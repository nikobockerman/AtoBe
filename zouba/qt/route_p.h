#ifndef ROUTE_P_H
#define ROUTE_P_H

#include "routedata.h"

#include "location.h"

#include <QObject>

class RoutePrivate: public QObject
{
  Q_OBJECT

public:
  RoutePrivate( QObject *parent=0 );
  ~RoutePrivate();

  Q_PROPERTY(Location fromLocation READ fromLocation WRITE setFromLocation);
  Q_PROPERTY(Location toLocation READ toLocation WRITE setFromLocation);

  RouteData parseReply( const QByteArray &reply );

  void setFromLocation( Location fromLocation );

  Location fromLocation();

  void setToLocation( Location toLocation );

  Location toLocation();

  QString parseJOREcode( const QString &joreCode ) const;
private:
  Location m_fromLocation;
  Location m_toLocation;
};
#endif // ROUTE_P_H
