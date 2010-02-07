#include "httpclient.h"
#include "ui_zouba.h"

#include <QDebug>

int main(int argc, char *argv[] )
{
  QApplication app(argc, argv);
  QMainWindow *widget = new QMainWindow;
  Ui::MainWindow ui;
  ui.setupUi(widget);

  HttpClient httpClient( &ui );

  httpClient.get();

  ui.TimeDisplay->setText( "HELLO" );

  widget->show();
  return app.exec();
}
