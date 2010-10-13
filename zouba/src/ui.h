#ifndef UI_H
#define UI_H

#include <QObject>
#include <QStandardItemModel>
#include <QPushButton>
#include <QMenuBar>
#include <QMainWindow>
#include <QWidget>
#include <QTableWidget>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QAction>
#ifdef Q_WS_MAEMO_5
#include <QMaemo5ValueButton>
#endif

#include "location.h"
#include "locationsdisplaywindow.h"

/*class QMainWindow;
class QWidget;
class QTableWidget;
class QButtonGroup;
class QHBoxLayout;
class QVBoxLayout;
class QGridLayout;
class QMenu;
class QAction;
class Location;*/

class UiClass : public QObject
{
  Q_OBJECT

public:
  UiClass();
  ~UiClass();
  void setupUi( QMainWindow *mainWindow );

  enum {
    FromButtonId=0,
    ToButtonId=1,
    RouteButtonId=2
  };

  enum {
    ScreenWidth=800,
    ScreenHeight=480
  };

  QMainWindow *m_mainWindow;
  QWidget *m_centralWidget;
#ifdef Q_WS_MAEMO_5
  QMaemo5ValueButton *m_fromButton;
  QMaemo5ValueButton *m_toButton;
#endif
  QButtonGroup *m_routeButtons;
  QVBoxLayout *m_routeStack;
  QTableWidget *m_routeDetailTable;
  QVBoxLayout *m_mainLayout;
  QGridLayout *m_buttonLayout;
  QMenuBar       *m_menu;
  QAction     *m_UseGpsAction;
  QStandardItemModel *m_locationsModel;
  QPushButton *m_routeButton;
  LocationsDisplayWindow *m_locDisp;

public slots:
  void setLocations();

Q_SIGNALS:
  void homeAddressChanged( QString address );
  void workAddressChanged( QString address );

private Q_SLOTS:
  void setHomeAddress();
  void setWorkAddress();
  void setBusy( bool busy );
  //void modifyLocations();


private:
  void setAddress( const QString &label );
};
#endif //UI_H
