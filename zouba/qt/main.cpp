#include "httpclient.h"
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

  HttpClient httpClient( &ui );

  httpClient.setFromLocation( work );
  httpClient.setToLocation( home );

  httpClient.get();

  ui.TimeDisplay->setText( "HELLO" );

  widget->show();
  return app.exec();
}
