#ifndef LOCATIONSDISPLAYWINDOW_H
#define LOCATIONSDISPLAYWINDOW_H

#include <QMainWindow>

class QListWidgetItem;

namespace Ui {
    class LocationsDisplayWindow;
}

class LocationsDisplayWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LocationsDisplayWindow(QWidget *parent = 0);
    ~LocationsDisplayWindow();

public slots:
    void populateLocations();

private slots:
    void showEditOptions();
    void editLocation(QListWidgetItem*);
    void closeEditOptions();
    void remove();
    void moveUp();
    void moveDown();
    void addAddress();

private:
    Ui::LocationsDisplayWindow *ui;
};

#endif // LOCATIONSDISPLAYWINDOW_H
