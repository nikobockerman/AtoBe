#include "uicontroller.h"
#include "route.h"
#include "ui.h"
#include "ytv.h"
#include "location.h"
#include "locations.h"

#include <QObject>
#include <QPushButton>
#include <QDebug>
#include <QButtonGroup>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QTableWidgetItem>
#include <QString>
#include <QMaemo5AbstractPickSelector>
#include <QMaemo5InformationBox>

UiController::UiController( Ui *ui ) :
        m_routeData(),
        m_ui(ui),
        m_currentRoute(-1)
{
    Locations *locations = Locations::GetInstance();
    if (locations->size() == 0)
    {
        locations->addEditLocation(new Location("Home"));
        locations->addEditLocation(new Location("Work"));
    }

    QObject::connect(m_ui->m_routeButton, SIGNAL(clicked()), this, SLOT(findRoute()));
    QObject::connect(this->m_ui->m_fromButton->pickSelector(), SIGNAL(selected(const QString &)), this, SLOT(changeFrom()));
    connect(m_ui->m_toButton->pickSelector(), SIGNAL(selected(const QString &)), this, SLOT(changeTo()));
    connect(m_ui->m_routeButtons, SIGNAL(buttonClicked(int)), this, SLOT(displayRouteDetail(int)));
}

UiController::~UiController()
{
}

void UiController::changeRoute( int id )
{
    bool routeHasChanged = ( m_currentRoute != id );
    if ( routeHasChanged ) {
        displayRouteDetail( id );
    }
}

void UiController::displayRouteDetail( int id )
{
    QTableWidget *table = m_ui->m_routeDetailTable;

    if ( id < m_routeData.count() ) {
        QList<LegData> &legDataList = m_routeData[ id ].m_legData;
        table->setRowCount( legDataList.count() );

        int row=0;
        foreach( LegData thisLegData, legDataList ) {
            QString thisHow = thisLegData.m_how;

            bool thisIsLine = ( thisHow == "LINE" );
            if ( thisIsLine ) {
                thisHow = thisLegData.m_lineCode;
            }

            QStringList tableStrings;
            tableStrings
                    << thisHow
                    << thisLegData.m_tripTime
                    << thisLegData.m_tripDistance
                    << thisLegData.m_departureTime
                    << thisLegData.m_arrivalTime;

            int col=0;
            foreach( QString thisString, tableStrings ) {
                QTableWidgetItem *newItem = new QTableWidgetItem();
                newItem->setText( thisString );
                table->setItem( row,col, newItem );
                ++col;
            }

            ++row;
        }
    } else {
        table->setRowCount( 0 );
    }

    table->resizeColumnsToContents();
}

void UiController::displayRoute( const QList<RouteData> &routeData )
{
    m_routeData = routeData;

    qDebug() << "displaying route";

    for ( int i=0; i<Ytv::ShowFiveResults; ++i ) {
        QString label;

        QWidget *widget = m_ui->m_routeStack->itemAt( i )->widget();
        QRadioButton *button = qobject_cast<QRadioButton *>(widget);

        if ( i<routeData.count() ) {
            RouteData thisRouteData = routeData.at(i);
            label = ( QStringList()
                      << thisRouteData.m_departureTime
                      << thisRouteData.m_lineCode ).join( "/" );
            button->setEnabled( true );
        } else {
            button->setEnabled( false );
        }

        if ( i==0 ) {
            button->setChecked( true );
        } else {
            button->setChecked( false );
        }

        button->setText( label );
    }

    displayRouteDetail( 0 );
}

void UiController::findRoute()
{
    qDebug() << "Route search button clicked";
    emit(routeSearchRequested());
}

/*void UiController::updateLocationSelectors()
{
    m_ui->setLocations();
}*/

void UiController::changeFrom()
{
    qDebug() << "From selection changed";
    Locations *locations = Locations::GetInstance();
    Location *from;

    const QString newValue = m_ui->m_fromButton->valueText();
    if (newValue == "GPS")
    {
        from = locations->getGpsLocation();
        if (!from->isValid())
        {
            qDebug() << "GPS location is not valid.";
            QMaemo5InformationBox::information(this->m_ui->m_mainWindow, "GPS location has not been received yet. Wait a moment.");
            connect(from, SIGNAL(becomeValid()), this, SLOT(gpsBecameValid()));
            return;
        }
    }
    else
        from = locations->getLocation(newValue);

    qDebug() << "Emitting signal of new from selection";
    emit(fromChanged(from));
}

void UiController::gpsBecameValid()
{
    QMaemo5InformationBox::information(this->m_ui->m_mainWindow, "GPS location received.");
    Location *gps = Locations::GetInstance()->getGpsLocation();
    disconnect(gps, SIGNAL(becomeValid()), this, SLOT(gpsBecameValid()));
    this->changeFrom();
    this->changeTo();
}

void UiController::changeTo()
{
    qDebug() << "To selection changed";
    Locations *locations = Locations::GetInstance();
    Location *to;

    const QString newValue = m_ui->m_toButton->valueText();
    if (newValue == "GPS")
    {
        to = locations->getGpsLocation();
        if (!to->isValid())
        {
            qDebug() << "GPS location is not valid.";
            QMaemo5InformationBox::information(this->m_ui->m_mainWindow, "GPS location has not been received yet. Wait a moment.");
            connect(to, SIGNAL(becomeValid()), this, SLOT(gpsBecameValid()));
            return;
        }
    }
    else
        to = locations->getLocation(newValue);

    qDebug() << "Emitting signal of new to selection";
    emit(toChanged(to));
}
