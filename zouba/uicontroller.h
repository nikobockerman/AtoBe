#ifndef UICONTROLLER_H
#define UICONTROLLER_H

#include "ui_zouba.h"
#include "routedata.h"

#include <QObject>

class UiController : public QObject
{
  Q_OBJECT

public:
  UiController( Ui::MainWindow *ui );
  ~UiController();

public Q_SLOTS:
  void displayRoute( const RouteData &routeData );

Q_SIGNALS:
  void homeAddressChanged( QString );
  void workAddressChanged( QString );
  void directionChanged();

private Q_SLOTS:
  void setHomeAddress();
  void setWorkAddress();
  void toggleRoute();

private:
  Ui::MainWindow *ui;
  enum Direction {
    WorkToHome,
    HomeToWork
  };

  Direction route;
};
#endif // UICONTROLLER_H

