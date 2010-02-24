#ifndef HTTPCLIENT_P_H
#define HTTPCLIENT_P_H

#include "routedata.h"

#include <QObject>

class HttpClientPrivate: public QObject
{
  Q_OBJECT

public:
  HttpClientPrivate( QObject *parent=0 );
  ~HttpClientPrivate();

  RouteData parseReply( const QByteArray &reply );
};
#endif // HTTPCLIENT_P_H
