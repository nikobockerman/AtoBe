#ifndef FAVORITESELECTIONDIALOG_H
#define FAVORITESELECTIONDIALOG_H

#include <QDialog>

class Location;
class QListWidgetItem;

namespace Ui {
    class FavoriteSelectionDialog;
}

class FavoriteSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FavoriteSelectionDialog(QWidget *parent = 0);
    ~FavoriteSelectionDialog();

signals:
    void selectedLocation(Location*);
    void customizeRequested();

private:
    Ui::FavoriteSelectionDialog *ui;
    QString m_text;

private slots:
    void on_gps_button_clicked();
    void on_modify_button_clicked();
    void on_locations_itemClicked(QListWidgetItem* item);
    void gps_updating_changed(bool isActive);
    void gps_location_retrieved();
};

#endif // FAVORITESELECTIONDIALOG_H
