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

private:
  Ui::MainWindow *ui;
};
#endif // UICONTROLLER_H

