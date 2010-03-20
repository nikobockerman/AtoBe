#include "uicontroller.h"
#include "route.h"
#include "ui.h"
#include "ytv.h"
#include "location.h"
#include "messagetable.h"

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

  homeLocation->resolveAddress( Ytv::Home );
  workLocation->resolveAddress( Ytv::Work );

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
  qDebug() << "Button "+QString::number(id)+" clicked";

  bool destinationHasChanged = ( currentDestination != id );
  if ( destinationHasChanged ) {
    emit destinationChanged( *(destination[id]) );
  }

  // always want to emit this so that the gps position is update
  // and the user gets new information
  emit buttonClicked();
}

void UiController::displayRoute( const QList<RouteData> &routeData )
{
  qDebug() << "displaying route";

  ui->table->setRowCount( routeData.count() );

  for ( int i=0; i<routeData.count(); i++ ) {
    QTableWidgetItem *timeItem = new QTableWidgetItem( routeData.at(i).arrivalTime );
    ui->table->setItem( i, 0, timeItem );

    QTableWidgetItem *lineItem = new QTableWidgetItem( routeData.at(i).lineCode );
    ui->table->setItem( i, 1, lineItem );
  }

  ui->table->resizeColumnsToContents();
}
