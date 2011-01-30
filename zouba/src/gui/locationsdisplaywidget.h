#ifndef LOCATIONSDISPLAYWIDGET_H
#define LOCATIONSDISPLAYWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QList>

#include "../logic/location.h"

namespace Ui {
    class LocationsDisplayWidget;
}

class LocationsDisplayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LocationsDisplayWidget(QWidget *parent = 0);
    ~LocationsDisplayWidget();

public slots:
    void populateLocations();
    void showWidget();

private slots:
    void on_newLocButton_clicked();
    void on_upButton_clicked();
    void on_downButton_clicked();
    void on_deleteButton_clicked();
    void on_doneButton_clicked();
    void on_locationsWidget_itemClicked(QListWidgetItem* item);
    void on_customizeButton_clicked();

private: //Methods
    void editLocation(QListWidgetItem*);
    Location* getSelectedLocation(QList<QListWidgetItem*>);
    QString getLocName(const QListWidgetItem *item);

private: // Variables
    Ui::LocationsDisplayWidget *ui;
};

#endif // LOCATIONSDISPLAYWIDGET_H
