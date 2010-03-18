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
  void destinationChanged( Location newDestination );

private Q_SLOTS:
  void changeDestination( int id );
  void setHomeButtonValid();
  void setWorkButtonValid();

private:
  void setButtonValid( int id );

private:
  QList<Location*> destination;
  Ui *ui;
  int currentDestination;
};
#endif // UICONTROLLER_H

