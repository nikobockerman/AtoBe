#ifndef UICONTROLLER_H
#define UICONTROLLER_H

#include "routedata.h"
#include "location.h"

#include <QObject>

class Ui;

class UiController : public QObject
{
  Q_OBJECT

public:
  UiController( Ui *ui );
  ~UiController();

public Q_SLOTS:
  void displayRoute( const QList<RouteData> &routeData );

Q_SIGNALS:
  void buttonClicked();
  void destinationChanged( Location *newDestination );

private Q_SLOTS:
  void changeDestination( int id );
  void changeRoute( int id );
  void setHomeButtonValid();
  void setWorkButtonValid();
  void displayRouteDetail( int id );

private:
  void setButtonValid( int id );

private:
  QList<RouteData> m_routeData;
  QList<Location*> m_destination;
  Ui *m_ui;
  int m_currentDestination;
  int m_currentRoute;
};
#endif // UICONTROLLER_H

