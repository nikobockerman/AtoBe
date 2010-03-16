#include "routedata.h"
#include "route.h"
#include "ui.h"
#include "uicontroller.h"
#include "location.h"
#include "gpscontroller.h"

#include "ytv.h"

#include <QDebug>
#include <QObject>
#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[] )
{
  QApplication app(argc, argv);
  QMainWindow *mainWindow = new QMainWindow;
  Ui ui;
  ui.setupUi(mainWindow);

  UiController  *uiController  = new UiController( &ui );
  Route         *route         = new Route();
  GpsController *gpsController = new GpsController();
  Location      *to            = new Location();

  QObject::connect(
      route, SIGNAL( routeReady( RouteData ) ),
      uiController, SLOT( displayRoute( RouteData ) )
      );

  QObject::connect(
      gpsController, SIGNAL( locationChanged( Location ) ),
      route, SLOT( setFromLocation( Location ) )
      );

  QObject::connect(
      to, SIGNAL( becomeValid() ),
      route, SLOT( setToLocation() )
      );

  QObject::connect(
      uiController, SIGNAL( homePressed() ),
      gpsController, SLOT( startGps() )
    );

  mainWindow->show();

  to->resolveAddress( work );

  return app.exec();
}
