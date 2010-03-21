#include "ui.h"

#include "messagetable.h"

#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include <QString>
#include <QRect>
#include <QButtonGroup>
#include <QHeaderView>
#include <QObject>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSizePolicy>

MessageTable *Ui::messageTable = 0;

Ui::Ui() :
  centralWidget(0),
  destinationButtons(0),
  routeTable(0)
{
}

Ui::~Ui()
{
}

void Ui::setupUi( QMainWindow *mainWindow )
{
  mainWindow->resize(800,480);
  QMenu *menu = mainWindow->menuBar()->addMenu("Settings");

  QAction *setHomeAddressAction = new QAction("Set home address", this);
  QAction *setWorkAddressAction = new QAction("Set work address", this);
  menu->addAction(setHomeAddressAction);
  menu->addAction(setWorkAddressAction);

  connect(
      setHomeAddressAction, SIGNAL(triggered()),
      this, SLOT(setHomeAddress())
      );
  connect(
      setWorkAddressAction, SIGNAL(triggered()),
      this, SLOT(setWorkAddress())
      );

  centralWidget = new QWidget( mainWindow );
  mainWindow->setCentralWidget(centralWidget);

  QPushButton *homeButton = new QPushButton();
  homeButton->setObjectName( QString::fromUtf8("homeButton") );
  homeButton->setText( "HOME" );
  homeButton->setEnabled(false);
  homeButton->setFixedSize( QSize( ButtonWidth, ButtonHeight ) );

  QPushButton *workButton = new QPushButton();
  workButton->setObjectName( QString::fromUtf8("workButton") );
  workButton->setText( "WORK" );
  workButton->setEnabled(false);

  destinationButtons = new QButtonGroup();
  destinationButtons->addButton( homeButton, HomeButtonId );
  destinationButtons->addButton( workButton, WorkButtonId );

  buttonLayout = new QVBoxLayout();
  buttonLayout->addWidget( homeButton );
  buttonLayout->addWidget( workButton );
  buttonLayout->addStretch();

  routeTable = new QTableWidget( 1, 2 );
  QStringList columnHeaders;
  columnHeaders << "Time" << "Bus";
  routeTable->setHorizontalHeaderLabels( columnHeaders );
  routeTable->verticalHeader()->hide();

  QHBoxLayout *topLayout = new QHBoxLayout();
  topLayout->addLayout( buttonLayout );
  topLayout->addWidget( routeTable );

  messageTable = new MessageTable();
  messageTable->setObjectName( QString::fromUtf8("messageTable") );

  QVBoxLayout *mainLayout = new QVBoxLayout();
  mainLayout->addLayout( topLayout );
  mainLayout->addWidget( messageTable );

  centralWidget->setLayout( mainLayout );
}

void Ui::setHomeAddress()
{
}

void Ui::setWorkAddress()
{
}
