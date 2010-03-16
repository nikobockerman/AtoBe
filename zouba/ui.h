#ifndef UI_H
#define UI_H

class QMainWindow;
class QWidget;
class QPushButton;
class QTableWidget;

class Ui
{
public:
  Ui();
  ~Ui();
  void setupUi( QMainWindow *mainWindow );

  QWidget *centralWidget;
  QPushButton *trigger;
  QTableWidget *table;
};
#endif //UI_H
