#ifndef LOCATIONSDISPLAYWINDOW_H
#define LOCATIONSDISPLAYWINDOW_H

#include <QMainWindow>
#include <QModelIndex>

class QListWidgetItem;
class Location;

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
    void on_locationsWidget_itemClicked(QListWidgetItem* item);
    void on_locationsWidget_clicked(QModelIndex index); // Unneeded
    void on_doneButton_clicked();
    void on_deleteButton_clicked();
    void on_downButton_clicked();
    void on_upButton_clicked();
    void on_customizeButton_clicked();
    void on_newLocButton_clicked();

private: // Methods
    void editLocation(QListWidgetItem*);
    Location* getSelectedLocation(QList<QListWidgetItem*>);
    QString getLocName(const QListWidgetItem *item);

private: // Variables
    Ui::LocationsDisplayWindow *ui;
};

#endif // LOCATIONSDISPLAYWINDOW_H
