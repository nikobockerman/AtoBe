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
#include <QMenu>
#include <QPushButton>
#include <QMaemo5ValueButton>
#include <QMaemo5ListPickSelector>
#include <QStandardItemModel>

Ui::Ui() :
        m_centralWidget(NULL),
        m_routeStack(NULL),
        m_locDisp(NULL)
{
}

Ui::~Ui()
{
    delete m_locDisp;
}

void Ui::setupUi( QMainWindow *mainWindow )
{
    m_mainWindow = mainWindow;
    m_mainWindow->setAttribute(Qt::WA_Maemo5StackedWindow);
    //m_mainWindow->resize(800,480);

    m_locDisp = new LocationsDisplay(mainWindow);

    m_menu = mainWindow->menuBar();

    /*QAction *setHomeAddressAction = new QAction("Set home address", this);
    QAction *setWorkAddressAction = new QAction("Set work address", this);*/
    QAction *modifyLocationsAction = new QAction("Modify locations", this);
    m_UseGpsAction  = new QAction("Use GPS", this);
    m_UseGpsAction->setCheckable(true);
    m_UseGpsAction->setChecked(true);
    /*m_menu->addAction(setHomeAddressAction);
    m_menu->addAction(setWorkAddressAction);*/
    m_menu->addAction(m_UseGpsAction);
    m_menu->addAction(modifyLocationsAction);

    /*connect(
            setHomeAddressAction, SIGNAL(triggered()),
            this, SLOT(setHomeAddress())
            );
    connect(
            setWorkAddressAction, SIGNAL(triggered()),
            this, SLOT(setWorkAddress())
            );*/

    connect(modifyLocationsAction, SIGNAL(triggered()), m_locDisp, SLOT(show()));

    Locations* locations = Locations::GetInstance();
    connect(locations, SIGNAL(locationsChanged()), this, SLOT(setLocations()));

    m_centralWidget = new QWidget( m_mainWindow );
    m_mainWindow->setCentralWidget( m_centralWidget);

    m_locationsModel = new QStandardItemModel(0,1);
    this->setLocations();

    m_fromButton = new QMaemo5ValueButton(QString::fromUtf8("From"));
    m_fromButton->setValueLayout(QMaemo5ValueButton::ValueBesideText);
    QMaemo5ListPickSelector *fromSelector = new QMaemo5ListPickSelector();
    fromSelector->setModel(m_locationsModel);
    m_fromButton->setPickSelector(fromSelector);

    m_toButton = new QMaemo5ValueButton(QString::fromUtf8("To"));
    m_toButton->setValueLayout(QMaemo5ValueButton::ValueBesideText);
    QMaemo5ListPickSelector *toSelector = new QMaemo5ListPickSelector();
    toSelector->setModel(m_locationsModel);
    m_toButton->setPickSelector(toSelector);

    m_routeButton = new QPushButton("Route");

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
    m_buttonLayout->addWidget(m_fromButton, 0, 0);
    m_buttonLayout->addWidget(m_toButton, 0, 1);
    m_buttonLayout->addWidget(m_routeButton, 0, 2);

    m_mainLayout = new QVBoxLayout();
    m_mainLayout->addLayout( topLayout );
    m_mainLayout->addLayout( m_buttonLayout );

    m_centralWidget->setLayout( m_mainLayout );
}

void Ui::setLocations()
{
    qDebug() << "Setting locations for main menu selectors.";
    Locations *locations = Locations::GetInstance();

    m_locationsModel->clear();
    QStandardItem *item = new QStandardItem(QString("GPS"));
    item->setTextAlignment(Qt::AlignCenter);
    item->setEditable(false);
    m_locationsModel->appendRow(item);

    for (int index = 1; index <= locations->size(); ++index)
    {
        item = new QStandardItem(locations->getLocation(index)->label());
        item->setTextAlignment(Qt::AlignCenter);
        item->setEditable(false);
        m_locationsModel->appendRow(item);
    }
}

void Ui::setHomeAddress()
{
    setAddress( "home" );
}

void Ui::setWorkAddress()
{
    setAddress( "work" );
}

void Ui::setAddress( const QString &label )
{
    /*Locations locations;
    Location *location=locations.location( label );

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
        Locations locations;
        Location  *location  = locations.location( label );
        qDebug() << "location" << location;
        if ( location ) {
            //location->resolveAddress( address );
        }
    }*/
}

/*void Ui::modifyLocations()
{
    LocationsDisplay
}*/

void Ui::setBusy( bool busy )
{
    m_mainWindow->setAttribute(Qt::WA_Maemo5ShowProgressIndicator, busy);
}
