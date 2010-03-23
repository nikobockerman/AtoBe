#ifndef ROUTE_H
#define ROUTE_H

#include "routedata.h"
#include "location.h"

#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class RoutePrivate;

class Route: public QObject
{
  Q_OBJECT

public:
  Route();
  ~Route();

  /*!
    * \brief Gets the route data from the server
    */
  void getRoute();

  /*!
    \brief Get the from location
    \return The from location
    */
  Location *fromLocation() const;

  /*!
    \brief Get the to location
    \return The to location
    */
  Location *toLocation() const;

public Q_SLOTS:

  /*!
    * \brief Sets the from location
    * \param fromLocation The from location
    */
  void setFromLocation( Location *location=0 );

  /*!
    * \brief Sets the to location
    * \param toLocation The to location
    */
  void setToLocation( Location *location=0 );

Q_SIGNALS:
  void routeReady( QList<RouteData> );

private Q_SLOTS:
  void replyFinished( QNetworkReply* );

private:
  RoutePrivate *q;
  QNetworkAccessManager *manager;
};
#endif // ROUTE_H
