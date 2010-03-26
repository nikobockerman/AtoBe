#include "messagetable.h"

#include <QHeaderView>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QResizeEvent>

MessageTable::MessageTable( QWidget *parent ) :
  QTableWidget( NumberOfRows, OneColumn, parent )
{
  setHorizontalHeaderLabels( QStringList() << "Messages" );
  verticalHeader()->hide();

  for ( int row=0; row<NumberOfRows; ++row ) {
    QTableWidgetItem *newRow = new QTableWidgetItem();
    setItem( row,0, newRow );
  }
}

MessageTable::~MessageTable()
{
}

void MessageTable::displayMessage( const QString &message )
{
  // scroll items down from bottom to top
  for ( int row=NumberOfRows-1; row>0; --row ) {
    QTableWidgetItem *fromItem = item(0,row-1);
    QTableWidgetItem *toItem = item(0,row);
    QString text=fromItem->text();
    toItem->setText( text );
  }

  itemAt(0,0)->setText( message );
}

void MessageTable::resizeEvent( QResizeEvent *event )
{
  int width = event->size().width() / columnCount();
  for ( int i = 0; i < columnCount(); ++i ) {
    setColumnWidth( i, width );
  }
}
