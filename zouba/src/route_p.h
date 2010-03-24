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

  QList<RouteData> parseReply( const QByteArray &reply );

  Q_PROPERTY(Location* fromLocation READ fromLocation WRITE setFromLocation);
  Q_PROPERTY(Location* toLocation READ toLocation WRITE setToLocation);

  void setFromLocation( Location *fromLocation );

  Location *fromLocation() const;

  void setToLocation( Location *toLocation );

  Location *toLocation() const;

  bool toValid();
  bool fromValid();

private:
  bool     m_fromValid;
  bool     m_toValid;
  Location *m_fromLocation;
  Location *m_toLocation;

  QString parseJORECode( const QString &joreCode ) const;
};
#endif // ROUTE_P_H
