#include "ui.h"

#include "messagetable.h"
#include "locations.h"
#include "ytv.h"

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
#include <QGridLayout>
#include <QSizePolicy>
#include <QInputDialog>
#include <QDebug>

MessageTable *Ui::messageTable = 0;

Ui::Ui() :
  centralWidget(0),
  destinationButtons(0),
  routeStack(0),
  usingFakeGps( false ),
  messagesShown( false ),
  fakeLocationLabel( "work" )
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
  toggleMessagesAction = new QAction("Show messages", this);
  toggleFakeGpsAction  = new QAction("Use fake GPS", this);
  menu->addAction(setHomeAddressAction);
  menu->addAction(setWorkAddressAction);
  menu->addAction(toggleMessagesAction);
  menu->addAction(toggleFakeGpsAction);

  connect(
      setHomeAddressAction, SIGNAL(triggered()),
      this, SLOT(setHomeAddress())
      );
  connect(
      setWorkAddressAction, SIGNAL(triggered()),
      this, SLOT(setWorkAddress())
      );
  connect(
      toggleMessagesAction, SIGNAL(triggered()),
      this, SLOT(toggleMessages())
      );
  connect(
      toggleFakeGpsAction, SIGNAL(triggered()),
      this, SLOT(toggleFakeGps())
      );

  centralWidget = new QWidget( mainWindow );
  mainWindow->setCentralWidget(centralWidget);

  QRadioButton *homeButton = new QRadioButton();
  homeButton->setObjectName( QString::fromUtf8("homeButton") );
  homeButton->setText( "GPS->HOME" );
  homeButton->setEnabled(false);

  QRadioButton *workButton = new QRadioButton();
  workButton->setObjectName( QString::fromUtf8("workButton") );
  workButton->setText( "GPS->WORK" );
  workButton->setEnabled(false);

  destinationButtons = new QButtonGroup();
  destinationButtons->addButton( homeButton, HomeButtonId );
  destinationButtons->addButton( workButton, WorkButtonId );
  destinationButtons->setExclusive( true );

  routeStack = new QVBoxLayout();
  for ( int i=0; i<Ytv::ShowFiveResults; ++i ) {
    QRadioButton *button = new QRadioButton();
    button->setObjectName( "routeButton"+i );
    button->setEnabled( false );

    routeStack->addWidget( button, i );
  }
  routeStack->addStretch();

  QHBoxLayout *topLayout = new QHBoxLayout();
  topLayout->addLayout( routeStack );
  topLayout->addStretch();

  buttonLayout = new QGridLayout();
  buttonLayout->addWidget( homeButton, 0, 0 );
  buttonLayout->addWidget( workButton, 0, 1 );

  messageTable = new MessageTable();
  messageTable->setObjectName( QString::fromUtf8("messageTable") );
  messageTable->hide();

  QVBoxLayout *mainLayout = new QVBoxLayout();
  mainLayout->addLayout( topLayout );
  mainLayout->addWidget( messageTable );
  mainLayout->addLayout( buttonLayout );

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

void Ui::toggleMessages()
{
  messagesShown = !messagesShown;

  if ( messagesShown ) {
    showMessages();
  } else {
    hideMessages();
  }
}

void Ui::hideMessages()
{
  messageTable->hide();
  toggleMessagesAction->setText( "Show messages" );
}

void Ui::showMessages()
{
  messageTable->show();
  toggleMessagesAction->setText( "Hide messages" );
}

void Ui::toggleFakeGps()
{
  usingFakeGps = !usingFakeGps;

  if ( usingFakeGps ) {
    useFakeGps();
  } else {
    useLiveGps();
  }
}

void Ui::useFakeGps()
{
  emit fakeGpsPressed( fakeLocationLabel );
  toggleFakeGpsAction->setText( "Use Live GPS" );
}

void Ui::useLiveGps()
{
  emit liveGpsPressed();
  toggleFakeGpsAction->setText( "Use Fake GPS" );
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
