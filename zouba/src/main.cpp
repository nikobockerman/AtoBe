#include "routedata.h"
#include "route.h"
#include "ui.h"
#include "uicontroller.h"
#include "logic/location.h"
#include "gpscontroller.h"
#include "logic/ytv.h"
#include "logic/locations.h"

#include "gui/searchdisplay.h"

#include <QDebug>
#include <QObject>
#include <QApplication>
#include <QMainWindow>
#include <QLabel>

//#define BUILD_TWO_GUIS 1

int main(int argc, char *argv[] )
{
    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName("ZouBa");
    QCoreApplication::setOrganizationDomain("zouba.yi.org");
    QCoreApplication::setApplicationName("ZouBa");

    Locations* locations = Locations::GetInstance();
    Locations *other_locations = Locations::GetInstance();
    if (locations->size() == 0)
    {
        locations->addEditLocation(new Location("2558542", "6676458", "Home"));
        locations->addEditLocation(new Location("2540835", "6672773", "Work"));
    }

#ifdef Q_WS_MAEMO_5
    SearchDisplay *mainWindow = new SearchDisplay();
    //layout->addWidget(win);
#else
    //DesktopWindow* mainWindow = new DesktopWindow();
    SearchDisplay *mainWindow = new SearchDisplay();
#endif
    mainWindow->show();

    if (locations == other_locations)
        qDebug() << "Same instance";
    else
        qDebug() << "!!NOT SAME INSTANCE!!";

#ifdef BUILD_TWO_GUIS
#ifdef Q_WS_MAEMO_5
    QMainWindow *oldMainWindow = new QMainWindow;
    UiClass *ui = new UiClass;;
    ui->setupUi(oldMainWindow);

    UiController  *uiController  = new UiController( ui );
    Route         *route         = new Route();
//#ifdef Q_WS_MAEMO_5
    GpsController *gpsController = new GpsController();
//#endif

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

//#ifdef Q_WS_MAEMO_5
    QObject::connect(
            ui->m_UseGpsAction, SIGNAL(toggled(bool)), gpsController, SLOT(useGPS(bool)));
//#endif

    oldMainWindow->show();
#endif // Q_WS_MAEMO_5
#endif // BUILD_TWO_GUIS
    //Locations::destroyLocations();

    return app.exec();
}
