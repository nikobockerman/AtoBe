#ifndef ROUTE_H
#define ROUTE_H

#include "ui_zouba.h"

#include "location.h"

#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class RoutePrivate;

class Route: public QObject
{
  Q_OBJECT

public:
  Route( Ui::MainWindow *ui );
  ~Route();

  Q_PROPERTY(Location fromLocation READ fromLocation WRITE setFromLocation);
  Q_PROPERTY(Location toLocation READ toLocation WRITE setFromLocation);

  /*!
    * \brief Gets the route data from the server
    */
  void get();

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

public Q_SLOTS:
  void replyFinished(QNetworkReply*);

private:
  QString parseJOREcode( const QString &joreCode ) const;

  RoutePrivate *q;
  QNetworkAccessManager *manager;
  Ui::MainWindow *ui;
};
#endif // ROUTE_H
