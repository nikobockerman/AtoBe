#include "ui.h"

#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include <QString>
#include <QRect>
#include <QButtonGroup>
#include <QHeaderView>

Ui::Ui() :
  centralWidget(0),
  destinationButtons(0),
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

  QPushButton *homeButton = new QPushButton( centralWidget );
  homeButton->setObjectName( QString::fromUtf8("homeButton") );
  homeButton->setText( "HOME" );
  homeButton->setGeometry( QRect( 0, 0, 150, 40 ) );
  homeButton->setEnabled(false);

  QPushButton *workButton = new QPushButton( centralWidget );
  workButton->setObjectName( QString::fromUtf8("workButton") );
  workButton->setText( "WORK" );
  workButton->setGeometry( QRect( 0, 40, 150, 40 ) );
  workButton->setEnabled(false);

  destinationButtons = new QButtonGroup( centralWidget );
  destinationButtons->addButton( homeButton, HomeButtonId );
  destinationButtons->addButton( workButton, WorkButtonId );

  table = new QTableWidget( 1, 2, centralWidget );
  table->setObjectName( QString::fromUtf8("table") );
  table->setGeometry( QRect( 151, 0, 650, 480 ) );
  QStringList columnHeaders;
  columnHeaders << "Time" << "Bus";
  table->setHorizontalHeaderLabels( columnHeaders );
  table->verticalHeader()->hide();
}
