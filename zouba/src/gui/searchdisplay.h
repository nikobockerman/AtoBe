#ifndef SEARCHDISPLAY_H
#define SEARCHDISPLAY_H

#include <QMainWindow>
#include <QLineEdit>

#include "routeresultwidget.h"
#include "locationsdisplaywidget.h"
#include "favoriteselectiondialog.h"

#include "src/logic/routefinder.h"


namespace Ui {
    class SearchDisplay;
}

class SearchDisplay : public QMainWindow
{
    Q_OBJECT

public:
    explicit SearchDisplay(QWidget *parent = 0);
    ~SearchDisplay();

public slots:
    void locations_changed();

private slots:
    void on_dest_favorites_clicked();
    void on_from_favorites_clicked();
    void on_dest_combo_currentIndexChanged(QString );
    void on_from_combo_currentIndexChanged(QString );
    void on_searchButton_clicked();

    void route_finder_finished();
    void customize_requested();
    void gps_status_change_requested(bool status);

private:
    void setEditText(QLineEdit*, QString&);
    void updateLocationLists();

    Ui::SearchDisplay *ui;
    RouteFinder *route_finder;
    QMutex one_search;
    bool search_restarted;
    LocationsDisplayWidget *edit_window;

#ifdef Q_WS_MAEMO_5
private slots:
    void from_selection_selected(Location*);
    void dest_selection_selected(Location*);
private:
    Location *from_selected;
    Location *dest_selected;
#else
private slots:
    void tabclosed(int index);
private:
    QTabWidget *tabs;
#endif
};


#endif // SEARCHDISPLAY_H
