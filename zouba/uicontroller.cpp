#include "uicontroller.h"
#include "route.h"
#include "ui_zouba.h"

UiController::UiController( Ui::MainWindow *ui ) :
  ui(ui),
  route( HomeToWork )
{
  connect( ui->sethomeaddress, SIGNAL( pressed() ), this, SLOT( setHomeAddress() ) );
  connect( ui->setworkaddress, SIGNAL( pressed() ), this, SLOT( setWorkAddress() ) );
  connect( ui->route, SIGNAL( pressed() ), this, SLOT( toggleRoute() ) );
}

UiController::~UiController()
{
}

void UiController::setHomeAddress()
{
  emit homeAddressChanged( ui->homeaddress->text() );
}

void UiController::setWorkAddress()
{
  emit workAddressChanged( ui->workaddress->text() );
}

void UiController::toggleRoute()
{
  if ( route == HomeToWork ) {
    route = WorkToHome;
    ui->route->setText( "Home<-Work" );
  } else {
    route = HomeToWork;
    ui->route->setText( "Home->Work" );
  }

  ui->busnodisplay->setText( "working" );
  ui->timedisplay->setText( "working" );

  emit directionChanged();
}

void UiController::displayRoute( const RouteData &routeData )
{
  ui->busnodisplay->setText( routeData.lineCode );
  ui->timedisplay->setText( routeData.arrivalTime );
}
