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
  enum {
   ButtonWidth=300,
   ButtonHeight=70
  };


  QWidget *centralWidget;
  QButtonGroup *destinationButtons;
  QTableWidget *table;
  static MessageTable *messageTable;
  QHBoxLayout *mainLayout;
  QVBoxLayout *buttonLayout;

Q_SIGNALS:
  void homeAddressChanged( QString address );
  void workAddressChanged( QString address );

private Q_SLOTS:
  void setHomeAddress();
  void setWorkAddress();
};
#endif //UI_H
