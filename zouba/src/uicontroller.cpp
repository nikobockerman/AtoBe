#include "uicontroller.h"
#include "route.h"
#include "ui.h"
#include "ytv.h"
#include "location.h"
#include "locations.h"

#include <QObject>
#include <QPushButton>
#include <QDebug>
#include <QButtonGroup>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QTableWidgetItem>

UiController::UiController( Ui *ui ) :
  m_routeData(),
  m_destination(),
  m_ui(ui),
  m_currentDestination(-1),
  m_currentRoute(-1)
{
  Locations locations;
  Location *homeLocation = locations.location( "home" );
  Location *workLocation = locations.location( "work" );

  if ( homeLocation==0 ) {
    homeLocation = new Location( "home" );
    locations.addLocation( homeLocation );
  } else if ( homeLocation->isValid() ) {
    setHomeButtonValid();
  }

  if ( workLocation==0 ) {
    workLocation = new Location( "work" );
    locations.addLocation( workLocation );
  } else if ( workLocation->isValid() ) {
    setWorkButtonValid();
  }

  connect(
      homeLocation, SIGNAL( becomeValid() ),
      this, SLOT( setHomeButtonValid() )
  );
  connect(
      homeLocation, SIGNAL( becomeInValid() ),
      this, SLOT( setHomeButtonInValid() )
  );
  connect(
      homeLocation, SIGNAL( becomeValid() ),
      &locations, SLOT( saveLocation() )
      );
  connect(
      homeLocation, SIGNAL( busy( bool ) ),
      ui, SLOT( setBusy( bool ) )
      );

  connect(
      workLocation, SIGNAL( becomeValid() ),
      this, SLOT( setWorkButtonValid() )
  );
  connect(
      workLocation, SIGNAL( becomeInValid() ),
      this, SLOT( setWorkButtonInValid() )
  );
  connect(
      workLocation, SIGNAL( becomeValid() ),
      &locations, SLOT( saveLocation() )
      );
  connect(
      workLocation, SIGNAL( busy( bool ) ),
      ui, SLOT( setBusy( bool ) )
      );

  m_destination.append( homeLocation );
  m_destination.append( workLocation );

  connect(
      m_ui->m_destinationButtons, SIGNAL( buttonClicked( int ) ),
      this, SLOT( changeDestination( int ) )
  );

  connect(
      m_ui->m_routeButtons, SIGNAL( buttonClicked( int ) ),
      this, SLOT( changeRoute( int ) )
  );
}

UiController::~UiController()
{
}

void UiController::setHomeButtonInValid()
{
  qDebug() << "setting home button invalid";
  setButtonValid( Ui::HomeButtonId, false );
}

void UiController::setHomeButtonValid()
{
  qDebug() << "setting home button valid";
  setButtonValid( Ui::HomeButtonId, true );
}

void UiController::setWorkButtonInValid()
{
  qDebug() << "setting work button invalid";
  setButtonValid( Ui::WorkButtonId, false );
}

void UiController::setWorkButtonValid()
{
  qDebug() << "setting work button valid";
  setButtonValid( Ui::WorkButtonId, true );
}

void UiController::setButtonValid( int id, bool isValid )
{
  m_ui->m_destinationButtons->button( id )->setEnabled( isValid );
}

void UiController::changeDestination( int id )
{
  bool destinationHasChanged = ( m_currentDestination != id );
  qDebug() << "Destination has changed=" << destinationHasChanged;
  if ( destinationHasChanged ) {
    qDebug() << "Emitting destination changed (" << m_destination[id]->label() << ")";
    emit destinationChanged( m_destination[id] );
    m_currentDestination = id;
  }

  // always want to emit this so that the gps position is updated
  // and the user gets new information
  emit buttonClicked();
}

void UiController::changeRoute( int id )
{
  bool routeHasChanged = ( m_currentRoute != id );
  if ( routeHasChanged ) {
    displayRouteDetail( id );
  }
}

void UiController::displayRouteDetail( int id )
{
  QTableWidget *table = m_ui->m_routeDetailTable;

  if ( id < m_routeData.count() ) {
    QList<LegData> &legDataList = m_routeData[ id ].m_legData;
    table->setRowCount( legDataList.count() );

    int row=0;
    foreach( LegData thisLegData, legDataList ) {
      QString thisHow = thisLegData.m_how;

      bool thisIsLine = ( thisHow == "LINE" );
      if ( thisIsLine ) {
        thisHow = thisLegData.m_lineCode;
      }

      QStringList tableStrings;
      tableStrings
        << thisHow
        << thisLegData.m_tripTime
        << thisLegData.m_tripDistance
        << thisLegData.m_departureTime
        << thisLegData.m_arrivalTime;

      int col=0;
      foreach( QString thisString, tableStrings ) {
        QTableWidgetItem *newItem = new QTableWidgetItem();
        newItem->setText( thisString );
        table->setItem( row,col, newItem );
        ++col;
      }

      ++row;
    }
  } else {
    table->setRowCount( 0 );
  }

  table->resizeColumnsToContents();
}

void UiController::displayRoute( const QList<RouteData> &routeData )
{
  m_routeData = routeData;

  qDebug() << "displaying route";

  for ( int i=0; i<Ytv::ShowFiveResults; ++i ) {
    QString label;

    QWidget *widget = m_ui->m_routeStack->itemAt( i )->widget();
    QRadioButton *button = qobject_cast<QRadioButton *>(widget);

    if ( i<routeData.count() ) {
      RouteData thisRouteData = routeData.at(i);
      label = ( QStringList()
          << thisRouteData.m_departureTime
          << thisRouteData.m_lineCode ).join( "/" );
      button->setEnabled( true );
    } else {
      button->setEnabled( false );
    }

    if ( i==0 ) {
      button->setChecked( true );
    } else {
      button->setChecked( false );
    }

    button->setText( label );
  }

  displayRouteDetail( 0 );
}
