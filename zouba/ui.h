#ifndef UI_H
#define UI_H

class QMainWindow;
class QWidget;
class QTableWidget;
class QButtonGroup;

class Ui
{
public:
  Ui();
  ~Ui();
  void setupUi( QMainWindow *mainWindow );

  enum {
    HomeButtonId=0,
    WorkButtonId=1
  };

  QWidget *centralWidget;
  QButtonGroup *destinationButtons;
  QTableWidget *table;
};
#endif //UI_H
