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
  m_ui->m_destinationButtons->button( id )->setEnabled(true);
}

void UiController::changeDestination( int id )
{
  qDebug() << "Destination button "+QString::number(id)+" clicked";

  bool destinationHasChanged = ( m_currentDestination != id );
  qDebug() << "Destination has changed=" << destinationHasChanged;
  if ( destinationHasChanged ) {
    qDebug() << "Emitting destination changed (" << m_destination[id]->label() << ")";
    emit destinationChanged( m_destination[id] );
  }

  // always want to emit this so that the gps position is update
  // and the user gets new information
  emit buttonClicked();
}

void UiController::changeRoute( int id )
{
  qDebug() << "Route button "+QString::number(id)+" clicked";

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

      QStringList tableStrings;
      tableStrings
        << thisLegData.m_how
        << thisLegData.m_tripTime
        << thisLegData.m_tripDistance
        << thisLegData.m_departureTime
        << thisLegData.m_arrivalTime
        << thisLegData.m_lineCode;

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

    button->setText( label );
  }

  QTableWidget *table = m_ui->m_routeDetailTable;
  table->setRowCount( 0 );
  table->resizeColumnsToContents();
}
