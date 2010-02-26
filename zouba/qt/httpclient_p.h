#ifndef HTTPCLIENT_P_H
#define HTTPCLIENT_P_H

#include "routedata.h"

#include "location.h"

#include <QObject>

class HttpClientPrivate: public QObject
{
  Q_OBJECT

public:
  HttpClientPrivate( QObject *parent=0 );
  ~HttpClientPrivate();

  Q_PROPERTY(Location fromLocation READ fromLocation WRITE setFromLocation);
  Q_PROPERTY(Location toLocation READ toLocation WRITE setFromLocation);

  RouteData parseReply( const QByteArray &reply );

  /*!
    * \brief Sets the from location
    * \param fromLocation The from location
    */
  void setFromLocation( Location fromLocation );

  /*!
    \brief Get the from location
    \return The from location
    */
  Location fromLocation();

  /*!
    * \brief Sets the to location
    * \param toLocation The to location
    */
  void setToLocation( Location toLocation );

  /*!
    \brief Get the to location
    \return The to location
    */
  Location toLocation();

private:
  Location m_fromLocation;
  Location m_toLocation;
};
#endif // HTTPCLIENT_P_H
