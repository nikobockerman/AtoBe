#include "routedata.h"
#include "route.h"
#include "ui_zouba.h"
#include "uicontroller.h"
#include "location.h"

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

  Location *from = new Location();
  Location *to   = new Location();

  QObject::connect(
      from, SIGNAL( becomeValid() ),
      route, SLOT( setFromLocation() )
      );
  QObject::connect(
      to, SIGNAL( becomeValid() ),
      route, SLOT( setToLocation() )
      );

  ui.homeaddress->setText( home );
  ui.workaddress->setText( work );

  from->resolveAddress( home );
  to->resolveAddress( work );

  QObject::connect(
      uiController, SIGNAL( homeAddressChanged( QString ) ),
      from, SLOT( resolveAddress( QString ) )
    );

  QObject::connect(
      uiController, SIGNAL( workAddressChanged( QString ) ),
      to, SLOT( resolveAddress( QString ) )
    );

  /* toggle doesn't work yet because 'from' is connected to 'homeAddressChanged'
  QObject::connect(
      uiController, SIGNAL( directionChanged() ),
      route, SLOT( toggleDirection() )
    );
    */

  widget->show();
  return app.exec();
}
