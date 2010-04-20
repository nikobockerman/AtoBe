#ifndef UI_H
#define UI_H

#include <QObject>

class QMainWindow;
class QWidget;
class QTableWidget;
class QButtonGroup;
class MessageTable;
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

  QWidget *centralWidget;
  QButtonGroup *destinationButtons;
  QVBoxLayout *routeStack;
  static MessageTable *messageTable;
  QHBoxLayout *mainLayout;
  QGridLayout *buttonLayout;
  QMenu       *menu;
  QAction     *toggleMessagesAction;
  QAction     *toggleFakeGpsAction;
  QAction     *useLiveGpsAction;
  bool        usingFakeGps;
  bool        messagesShown;
  QString     fakeLocationLabel;

Q_SIGNALS:
  void homeAddressChanged( QString address );
  void workAddressChanged( QString address );
  void fakeGpsPressed( const QString &fakeLocationLabel );
  void liveGpsPressed();

private Q_SLOTS:
  void setHomeAddress();
  void setWorkAddress();
  void toggleMessages();
  void toggleFakeGps();

private:
  void useFakeGps();
  void useLiveGps();
  void hideMessages();
  void showMessages();
  void setAddress( const QString &label );
};
#endif //UI_H
