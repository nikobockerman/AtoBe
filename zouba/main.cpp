#include "routedata.h"
#include "route.h"
#include "ui_zouba.h"
#include "uicontroller.h"
#include "location.h"

#include <QDebug>
#include <QObject>

namespace {
  Location home( "2549183", "6672570" );
  Location work( "2551042", "6672829" );
  QString homeKey( "taivaanvuohentie%207%2Chelsinki" );
  QString workKey( "it%E4merenkatu%2011%2Chelsinki" );
}

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

  from->resolveAddress( homeKey );
  to->resolveAddress( workKey );

  widget->show();
  return app.exec();
}
