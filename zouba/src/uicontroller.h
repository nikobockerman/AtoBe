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
  //void updateLocationSelectors();
  void changeFrom();
  void changeTo();
  void gpsBecameValid();

Q_SIGNALS:
  void routeSearchRequested();
  void fromChanged(Location *newFromLocation);
  void toChanged(Location *newToLocation);

private Q_SLOTS:
  void changeRoute( int id );
  void displayRouteDetail( int id );
  void findRoute();

private:
  QList<RouteData> m_routeData;
  Ui *m_ui;
  int m_currentRoute;
};
#endif // UICONTROLLER_H

