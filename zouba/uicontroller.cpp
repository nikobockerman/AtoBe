#include "uicontroller.h"
#include "route.h"
#include "ui.h"

#include <QObject>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QDebug>

UiController::UiController( Ui *ui ) :
  ui(ui)
{
  connect( ui->trigger, SIGNAL( pressed() ), this, SIGNAL( homePressed() ) );
}

UiController::~UiController()
{
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
