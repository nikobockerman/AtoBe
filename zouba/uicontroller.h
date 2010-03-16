#ifndef UICONTROLLER_H
#define UICONTROLLER_H

#include "routedata.h"

#include <QObject>

class Ui;

class UiController : public QObject
{
  Q_OBJECT

public:
  UiController( Ui *ui );
  ~UiController();

public Q_SLOTS:
  void displayRoute( const RouteData &routeData );

Q_SIGNALS:
  void homePressed();

private:
  Ui *ui;
};
#endif // UICONTROLLER_H

