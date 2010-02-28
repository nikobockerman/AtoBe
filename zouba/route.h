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

  Q_PROPERTY(Location fromLocation READ fromLocation WRITE setFromLocation);
  Q_PROPERTY(Location toLocation READ toLocation WRITE setToLocation);

  /*!
    * \brief Gets the route data from the server
    */
  void getRoute();

  /*!
    \brief Get the from location
    \return The from location
    */
  const Location &fromLocation();

  /*!
    \brief Get the to location
    \return The to location
    */
  const Location &toLocation();

public Q_SLOTS:

  /*!
    * \brief Sets the from location
    * \param fromLocation The from location
    */
  void setFromLocation( const Location &location=Location() );

  /*!
    * \brief Sets the to location
    * \param toLocation The to location
    */
  void setToLocation( const Location &location=Location() );

  /*!
    * \brief Toggles the route direction.
    */
  void toggleDirection();

Q_SIGNALS:
  void routeReady( RouteData );

private Q_SLOTS:
  void replyFinished( QNetworkReply* );

private:
  RoutePrivate *q;
  QNetworkAccessManager *manager;
};
#endif // ROUTE_H
