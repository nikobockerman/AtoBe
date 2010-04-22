#ifndef UI_H
#define UI_H

#include <QObject>

class QMainWindow;
class QWidget;
class QTableWidget;
class QButtonGroup;
class QHBoxLayout;
class QVBoxLayout;
class QGridLayout;
class QMenu;
class QAction;
class Location;

class Ui : public QObject
{
  Q_OBJECT

public:
  Ui();
  ~Ui();
  void setupUi( QMainWindow *mainWindow );

  enum {
    HomeButtonId=0,
    WorkButtonId=1
  };

  enum {
    ScreenWidth=800,
    ScreenHeight=480
  };

  QMainWindow *m_mainWindow;
  QWidget *m_centralWidget;
  QButtonGroup *m_destinationButtons;
  QButtonGroup *m_routeButtons;
  QVBoxLayout *m_routeStack;
  QTableWidget *m_routeDetailTable;
  QVBoxLayout *m_mainLayout;
  QGridLayout *m_buttonLayout;
  QMenu       *m_menu;
  QAction     *m_toggleFakeGpsAction;
  QAction     *m_useLiveGpsAction;
  bool        m_usingFakeGps;
  QString     m_fakeLocationLabel;

Q_SIGNALS:
  void homeAddressChanged( QString address );
  void workAddressChanged( QString address );
  void fakeGpsPressed( const QString &fakeLocationLabel );
  void liveGpsPressed();

private Q_SLOTS:
  void setHomeAddress();
  void setWorkAddress();
  void toggleFakeGps();
  void setBusy( bool busy );

private:
  void useFakeGps();
  void useLiveGps();
  void setAddress( const QString &label );
};
#endif //UI_H
