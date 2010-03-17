#include "uicontroller.h"
#include "route.h"
#include "ui.h"
#include "ytv.h"
#include "location.h"

#include <QObject>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QDebug>
#include <QButtonGroup>

UiController::UiController( Ui *ui ) :
  ui(ui)
{
  Location *homeLocation = new Location();
  Location *workLocation = new Location();

  connect(
      homeLocation, SIGNAL( becomeValid() ),
      this, SLOT( setHomeButtonValid() )
  );
  connect(
      workLocation, SIGNAL( becomeValid() ),
      this, SLOT( setWorkButtonValid() )
  );

  homeLocation->resolveAddress( home );
  workLocation->resolveAddress( work );

  destination.append( homeLocation );
  destination.append( workLocation );

  connect(
      ui->destinationButtons, SIGNAL( buttonClicked( int ) ),
      this, SLOT( changeDestination( int ) )
  );

}

UiController::~UiController()
{
}

void UiController::setHomeButtonValid()
{
  setButtonValid( Ui::HomeButtonId );
}

void UiController::setWorkButtonValid()
{
  setButtonValid( Ui::WorkButtonId );
}

void UiController::setButtonValid( int id )
{
  ui->destinationButtons->button( id )->setEnabled(true);
}

void UiController::changeDestination( int id )
{
  bool destinationHasChanged = ( currentDestination != id );
  if ( destinationHasChanged ) {
    emit destinationChanged( *(destination[id]) );
  }

  // always want to emit this so that the gps position is update
  // and the user gets new information
  emit buttonClicked();
}

void UiController::displayRoute( const RouteData &routeData )
{
  qDebug() << __PRETTY_FUNCTION__;
  qDebug() << "routeData.arrivalTime" << routeData.arrivalTime;
  qDebug() << "routeData.lineCode" << routeData.lineCode;

  QTableWidgetItem *timeItem = new QTableWidgetItem( routeData.arrivalTime );
  ui->table->setItem( 0, 0, timeItem );

  QTableWidgetItem *lineItem = new QTableWidgetItem( routeData.lineCode );
  ui->table->setItem( 0, 1, lineItem );
}
