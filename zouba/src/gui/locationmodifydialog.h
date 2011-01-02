#ifndef LOCATIONMODIFYDIALOG_H
#define LOCATIONMODIFYDIALOG_H

#include <QDialog>
#include <QListWidgetItem>

#include "../logic/locationfinder.h"

namespace Ui {
    class LocationModifyDialog;
}

class LocationModifyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LocationModifyDialog(QWidget *parent = 0, Location *edit = NULL);
    ~LocationModifyDialog();

private:
    Ui::LocationModifyDialog *ui;

private slots:
    void on_address_list_itemClicked(QListWidgetItem* item);
    void on_search_button_clicked();

    void location_search_finished();
    void orientationChanged();

private : // Methods
    void populateList(const QList<Location*> &list);

private: // Variables
    LocationFinder *finder;
    bool edit;
};

#endif // LOCATIONMODIFYDIALOG_H
