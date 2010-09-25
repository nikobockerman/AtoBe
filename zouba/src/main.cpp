#include "routedata.h"
#include "route.h"
#include "ui.h"
#include "uicontroller.h"
#include "location.h"
#include "gpscontroller.h"
#include "ytv.h"
#include "locations.h"

#include <QDebug>
#include <QObject>
#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[] )
{
    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName("ZouBa");
    QCoreApplication::setOrganizationDomain("zouba.yi.org");
    QCoreApplication::setApplicationName("ZouBa");

    Locations* locations = Locations::GetInstance();
    Locations *other_locations = Locations::GetInstance();
    if (locations == other_locations)
        qDebug() << "Same instance";
    else
        qDebug() << "!!NOT SAME INSTANCE!!";

    QMainWindow *mainWindow = new QMainWindow;
    Ui *ui = new Ui;;
    ui->setupUi(mainWindow);

    UiController  *uiController  = new UiController( ui );
    Route         *route         = new Route();
    GpsController *gpsController = new GpsController();

    QObject::connect(
            route, SIGNAL( routeReady( QList<RouteData> ) ),
            uiController, SLOT( displayRoute( QList<RouteData> ) )
            );

    /*QObject::connect(
      gpsController, SIGNAL( gpsLocationChanged( Location* ) ),
      uiController, SLOT()
      );*/

    QObject::connect(
            uiController, SIGNAL(fromChanged(Location*)),
            route, SLOT(setFromLocation(Location*)));

    QObject::connect(
            uiController, SIGNAL(toChanged(Location*)),
            route, SLOT(setToLocation(Location*)));

    QObject::connect(
            uiController, SIGNAL(routeSearchRequested()),
            route, SLOT(searchRoute()));

    QObject::connect(
            route, SIGNAL(busy(bool)),
            ui, SLOT(setBusy(bool)));

    QObject::connect(
            ui->m_UseGpsAction, SIGNAL(toggled(bool)), gpsController, SLOT(useGPS(bool)));

    mainWindow->show();

    //Locations::destroyLocations();

    return app.exec();
}
