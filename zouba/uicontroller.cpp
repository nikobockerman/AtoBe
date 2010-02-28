#include "uicontroller.h"
#include "route.h"
#include "ui_zouba.h"

UiController::UiController( Ui::MainWindow *ui ) :
  ui(ui)
{
}

UiController::~UiController()
{
}

void UiController::displayRoute( const RouteData &routeData )
{
  ui->BusNoDisplay->setText( routeData.lineCode );
  ui->TimeDisplay->setText( routeData.arrivalTime );
}
