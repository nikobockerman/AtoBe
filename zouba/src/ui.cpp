#include "ui.h"

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

Ui::Ui() :
  m_centralWidget(0),
  m_destinationButtons(0),
  m_routeStack(0),
  m_usingFakeGps( false ),
  m_fakeLocationLabel( "work" )
{
}

Ui::~Ui()
{
}

void Ui::setupUi( QMainWindow *mainWindow )
{
  m_mainWindow = mainWindow;
  m_mainWindow->resize(800,480);

  m_menu = mainWindow->menuBar()->addMenu("Settings");

  QAction *setHomeAddressAction = new QAction("Set home address", this);
  QAction *setWorkAddressAction = new QAction("Set work address", this);
  m_toggleFakeGpsAction  = new QAction("Use fake GPS", this);
  m_menu->addAction(setHomeAddressAction);
  m_menu->addAction(setWorkAddressAction);
  m_menu->addAction(m_toggleFakeGpsAction);

  connect(
      setHomeAddressAction, SIGNAL(triggered()),
      this, SLOT(setHomeAddress())
      );
  connect(
      setWorkAddressAction, SIGNAL(triggered()),
      this, SLOT(setWorkAddress())
      );
  connect(
      m_toggleFakeGpsAction, SIGNAL(triggered()),
      this, SLOT(toggleFakeGps())
      );

  m_centralWidget = new QWidget( m_mainWindow );
  m_mainWindow->setCentralWidget( m_centralWidget);

  QRadioButton *homeButton = new QRadioButton();
  homeButton->setObjectName( QString::fromUtf8("homeButton") );
  homeButton->setText( "GPS->HOME" );
  homeButton->setEnabled(false);

  QRadioButton *workButton = new QRadioButton();
  workButton->setObjectName( QString::fromUtf8("workButton") );
  workButton->setText( "GPS->WORK" );
  workButton->setEnabled(false);

  m_destinationButtons = new QButtonGroup();
  m_destinationButtons->addButton( homeButton, HomeButtonId );
  m_destinationButtons->addButton( workButton, WorkButtonId );
  m_destinationButtons->setExclusive( true );

  m_routeButtons = new QButtonGroup();
  m_routeButtons->setExclusive( true );
  m_routeStack = new QVBoxLayout();
  for ( int i=0; i<Ytv::ShowFiveResults; ++i ) {
    QRadioButton *button = new QRadioButton();
    button->setObjectName( "routeButton"+i );
    button->setEnabled( false );

    m_routeStack->addWidget( button, i );
    m_routeButtons->addButton( button, i );
  }
  m_routeStack->addStretch();

  QStringList headers( QStringList() << "How" << "Time" << "Dist" << "Dep" << "Arr" );
  m_routeDetailTable = new QTableWidget();
  m_routeDetailTable->setColumnCount( headers.count() );
  m_routeDetailTable->setHorizontalHeaderLabels( headers );
  m_routeDetailTable->resizeColumnsToContents();
  m_routeDetailTable->setSelectionMode( QAbstractItemView::NoSelection );

  QHBoxLayout *topLayout = new QHBoxLayout();
  topLayout->addLayout( m_routeStack );
  topLayout->addWidget( m_routeDetailTable );

  m_buttonLayout = new QGridLayout();
  m_buttonLayout->addWidget( homeButton, 0, 0 );
  m_buttonLayout->addWidget( workButton, 0, 1 );

  m_mainLayout = new QVBoxLayout();
  m_mainLayout->addLayout( topLayout );
  m_mainLayout->addLayout( m_buttonLayout );

  m_centralWidget->setLayout( m_mainLayout );
}

void Ui::setHomeAddress()
{
  setAddress( "home" );
}

void Ui::setWorkAddress()
{
  setAddress( "work" );
}

void Ui::toggleFakeGps()
{
  m_usingFakeGps = !m_usingFakeGps;

  if ( m_usingFakeGps ) {
    useFakeGps();
  } else {
    useLiveGps();
  }
}

void Ui::useFakeGps()
{
  emit fakeGpsPressed( m_fakeLocationLabel );
  m_toggleFakeGpsAction->setText( "Use Live GPS" );
}

void Ui::useLiveGps()
{
  emit liveGpsPressed();
  m_toggleFakeGpsAction->setText( "Use Fake GPS" );
}

void Ui::setAddress( const QString &label )
{
  Locations *locations=Locations::instance();
  Location *location=locations->location( label );

  bool ok;
  QString address = QInputDialog::getText(
     m_centralWidget,
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

void Ui::setBusy( bool busy )
{
  m_mainWindow->setAttribute(Qt::WA_Maemo5ShowProgressIndicator, busy);
}
