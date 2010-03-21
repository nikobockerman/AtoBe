#include "messagetable.h"

#include <QHeaderView>
#include <QString>
#include <QStringList>
#include <QDebug>

MessageTable::MessageTable( QWidget *parent ) :
  QTableWidget( NumberOfRows, OneColumn, parent )
{
  setHorizontalHeaderLabels( QStringList() << "Messages" );
  verticalHeader()->hide();
  //setMinimumSize( 800,0 );
  //setMaximumSize( 800,480 );
  //setSizePolicy(
      //QSizePolicy::Fixed, 
      //QSizePolicy::Expanding
      //);

  for ( int row=0; row<NumberOfRows; ++row ) {
    QTableWidgetItem *newRow = new QTableWidgetItem();
    setItem( row,0, newRow );
  }

  horizontalHeader()->setStretchLastSection(true);
}

/*
QSize MessageTable::minimumSizeHint() const
{
	QSize size( QTableWidget::sizeHint() );

	size.setWidth( 800 );
	return size;
}

QSize MessageTable::sizeHint() const
{
	return minimumSizeHint();
}
*/

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
