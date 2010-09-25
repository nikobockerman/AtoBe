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
#include <QMaemo5ValueButton>

#include "location.h"
#include "locationsdisplay.h"

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

class Ui : public QObject
{
  Q_OBJECT

public:
  Ui();
  ~Ui();
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
  QMaemo5ValueButton *m_fromButton;
  QMaemo5ValueButton *m_toButton;
  QButtonGroup *m_routeButtons;
  QVBoxLayout *m_routeStack;
  QTableWidget *m_routeDetailTable;
  QVBoxLayout *m_mainLayout;
  QGridLayout *m_buttonLayout;
  QMenuBar       *m_menu;
  QAction     *m_UseGpsAction;
  QStandardItemModel *m_locationsModel;
  QPushButton *m_routeButton;
  LocationsDisplay *m_locDisp;

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
