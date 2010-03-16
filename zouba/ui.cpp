#include "ui.h"

#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include <QString>
#include <QRect>

Ui::Ui() :
  centralWidget(0),
  trigger(0),
  table(0)
{
}

Ui::~Ui()
{
}

void Ui::setupUi( QMainWindow *mainWindow )
{
  mainWindow->resize(800,480);

  centralWidget = new QWidget( mainWindow );
  mainWindow->setCentralWidget(centralWidget);

  trigger = new QPushButton( centralWidget );
  trigger->setObjectName( QString::fromUtf8("trigger") );
  trigger->setText( "HOME" );
  trigger->setGeometry( QRect( 0, 0, 150, 40 ) );

  table = new QTableWidget( 1, 2, centralWidget );
  table->setObjectName( QString::fromUtf8("table") );
  table->setGeometry( QRect( 151, 0, 650, 480 ) );
}
