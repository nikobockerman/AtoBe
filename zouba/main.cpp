#include "routedata.h"
#include "route.h"
#include "ui_zouba.h"
#include "uicontroller.h"
#include "location.h"
#include "gpscontroller.h"

#include "ytv.h"

#include <QDebug>
#include <QObject>

int main(int argc, char *argv[] )
{
  QApplication app(argc, argv);
  QMainWindow *widget = new QMainWindow;
  Ui::MainWindow ui;
  ui.setupUi(widget);

  UiController *uiController = new UiController( &ui );

  Route *route = new Route();

  QObject::connect(
      route, SIGNAL( routeReady( RouteData ) ),
      uiController, SLOT( displayRoute( RouteData ) )
      );

  GpsController *gpsController = new GpsController();
  Location *to   = new Location();

  QObject::connect(
      gpsController, SIGNAL( locationChanged( Location ) ),
      route, SLOT( setFromLocation( Location ) )
      );
  QObject::connect(
      to, SIGNAL( becomeValid() ),
      route, SLOT( setToLocation() )
      );

  ui.homeaddress->setText( "GPS" );
  ui.workaddress->setText( work );

  gpsController->startGps();
  to->resolveAddress( work );

  QObject::connect(
      uiController, SIGNAL( workAddressChanged( QString ) ),
      to, SLOT( resolveAddress( QString ) )
    );

  widget->show();
  return app.exec();
}
