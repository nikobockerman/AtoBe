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

  QObject::connect(
      route, SIGNAL( routeReady( QList<RouteData> ) ),
      uiController, SLOT( displayRoute( QList<RouteData> ) )
      );

  QObject::connect(
      gpsController, SIGNAL( locationChanged( Location ) ),
      route, SLOT( setFromLocation( Location ) )
      );

  QObject::connect(
      uiController, SIGNAL( destinationChanged( Location ) ),
      route, SLOT( setToLocation( Location ) )
    );

  QObject::connect(
      uiController, SIGNAL( buttonClicked() ),
      gpsController, SLOT( startGps() )
    );

  mainWindow->show();

  return app.exec();
}
