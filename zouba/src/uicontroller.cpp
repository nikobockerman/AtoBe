#include "uicontroller.h"
#include "route.h"
#include "ui.h"
#include "ytv.h"
#include "location.h"
#include "messagetable.h"
#include "locations.h"

#include <QObject>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QDebug>
#include <QButtonGroup>

UiController::UiController( Ui *ui ) :
  ui(ui)
{
  Locations *locations = Locations::instance();
  Location *homeLocation = locations->location( "home" );
  Location *workLocation = locations->location( "work" );

  if ( homeLocation==0 ) {
    homeLocation = new Location( "home" );
    locations->addLocation( homeLocation );
  } else if ( homeLocation->isValid() ) {
    setHomeButtonValid();
  }

  if ( workLocation==0 ) {
    workLocation = new Location( "work" );
    locations->addLocation( workLocation );
  } else if ( workLocation->isValid() ) {
    setWorkButtonValid();
  }

  connect(
      homeLocation, SIGNAL( becomeValid() ),
      this, SLOT( setHomeButtonValid() )
  );
  connect(
      homeLocation, SIGNAL( becomeValid() ),
      locations, SLOT( saveLocation() )
      );

  connect(
      workLocation, SIGNAL( becomeValid() ),
      this, SLOT( setWorkButtonValid() )
  );
  connect(
      workLocation, SIGNAL( becomeValid() ),
      locations, SLOT( saveLocation() )
      );

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
  qDebug() << "setting home button valid";
  setButtonValid( Ui::HomeButtonId );
}

void UiController::setWorkButtonValid()
{
  qDebug() << "setting work button valid";
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
    emit destinationChanged( destination[id] );
  }

  // always want to emit this so that the gps position is update
  // and the user gets new information
  emit buttonClicked();
}

void UiController::displayRoute( const QList<RouteData> &routeData )
{
  qDebug() << "displaying route";

  ui->routeTable->setRowCount( routeData.count() );

  for ( int i=0; i<routeData.count(); i++ ) {
    QTableWidgetItem *timeItem = new QTableWidgetItem( routeData.at(i).arrivalTime );
    ui->routeTable->setItem( i, 0, timeItem );

    QTableWidgetItem *lineItem = new QTableWidgetItem( routeData.at(i).lineCode );
    ui->routeTable->setItem( i, 1, lineItem );
  }
}
