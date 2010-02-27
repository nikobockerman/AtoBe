#include "route.h"
#include "ui_zouba.h"

#include "location.h"

#include <QDebug>

namespace {
  Location home( "2549183", "6672570" );
  Location work( "2551042", "6672829" );
}

int main(int argc, char *argv[] )
{
  QApplication app(argc, argv);
  QMainWindow *widget = new QMainWindow;
  Ui::MainWindow ui;
  ui.setupUi(widget);

  Route route( &ui );

  route.setFromLocation( work );
  route.setToLocation( home );

  route.get();

  ui.TimeDisplay->setText( "HELLO" );

  widget->show();
  return app.exec();
}
