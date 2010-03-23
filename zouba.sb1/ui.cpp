#include "ui.h"

#include "messagetable.h"
#include "locations.h"

#include <QMainWindow>
#include <QRadioButton>
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
#include <QInputDialog>
#include <QDebug>

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
  menu = mainWindow->menuBar()->addMenu("Settings");

  QAction *setHomeAddressAction = new QAction("Set home address", this);
  QAction *setWorkAddressAction = new QAction("Set work address", this);
  hideMessagesAction   = new QAction("Hide messages", this);
  showMessagesAction   = new QAction("Show messages", this);
  menu->addAction(setHomeAddressAction);
  menu->addAction(setWorkAddressAction);
  menu->addAction(showMessagesAction);

  connect(
      setHomeAddressAction, SIGNAL(triggered()),
      this, SLOT(setHomeAddress())
      );
  connect(
      setWorkAddressAction, SIGNAL(triggered()),
      this, SLOT(setWorkAddress())
      );
  connect(
      hideMessagesAction, SIGNAL(triggered()),
      this, SLOT(hideMessages())
      );
  connect(
      showMessagesAction, SIGNAL(triggered()),
      this, SLOT(showMessages())
      );

  centralWidget = new QWidget( mainWindow );
  mainWindow->setCentralWidget(centralWidget);

  QRadioButton *homeButton = new QRadioButton();
  homeButton->setObjectName( QString::fromUtf8("homeButton") );
  homeButton->setText( "GPS->HOME" );
  homeButton->setEnabled(false);
  homeButton->setFixedSize( QSize( ButtonWidth, ButtonHeight ) );

  QRadioButton *workButton = new QRadioButton();
  workButton->setObjectName( QString::fromUtf8("workButton") );
  workButton->setText( "GPS->WORK" );
  workButton->setEnabled(false);

  destinationButtons = new QButtonGroup();
  destinationButtons->addButton( homeButton, HomeButtonId );
  destinationButtons->addButton( workButton, WorkButtonId );
  destinationButtons->setExclusive( true );

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
  messageTable->hide();

  QVBoxLayout *mainLayout = new QVBoxLayout();
  mainLayout->addLayout( topLayout );
  mainLayout->addWidget( messageTable );

  centralWidget->setLayout( mainLayout );
}

void Ui::setHomeAddress()
{
  setAddress( "home" );
}

void Ui::setWorkAddress()
{
  setAddress( "work" );
}

void Ui::hideMessages()
{
  messageTable->hide();
  menu->removeAction( hideMessagesAction );
  menu->addAction( showMessagesAction );
}

void Ui::showMessages()
{
  messageTable->show();
  menu->removeAction( showMessagesAction );
  menu->addAction( hideMessagesAction );
}

void Ui::setAddress( const QString &label )
{
  Locations *locations=Locations::instance();
  Location *location=locations->location( label );

  bool ok;
  QString address = QInputDialog::getText(
     centralWidget,
     tr("Enter address for \""+QString(label).toLatin1()+"\""),
     tr("Address"),
     QLineEdit::Normal,
     location->address(),
     &ok
     );

  qDebug() << "ok=" << ok;

  if ( ok ) {
    qDebug() << "new address" << address;
    Locations *locations = Locations::instance();
    Location  *location  = locations->location( label );
    qDebug() << "location" << location;
    if ( location ) {
      location->resolveAddress( address );
    }
  }
}
