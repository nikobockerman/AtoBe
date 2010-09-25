#ifndef LOCATIONSDISPLAY_H
#define LOCATIONSDISPLAY_H

#include <QMainWindow>
#include <QMaemo5EditBar>

class QVBoxLayout;
class QWidget;
class QListView;
class QListWidget;
class QPoint;
class QListWidgetItem;
class QPushButton;
class LocationsEditBar;


/* TODO: Redesign locations list:
 * - Add button to top
 * - List all locations below that
 * - Short press selects to edit
 * - Long press shows options:
 *   - Delete
 *   - Move up
 *   - Move down
 */
class LocationsDisplay : public QMainWindow
{
    Q_OBJECT
public:
    explicit LocationsDisplay(QWidget *parent = 0);

signals:

public slots:
    void populateLocations();

private slots:
    void addAddress();
    void editLocation(QListWidgetItem*);
    void contextMenu(const QPoint&);
    void remove();
    void showEditOptions();
    void closeEditOptions();

private:
    QPushButton *m_addButton;
    QListWidget *m_list;
    QPoint m_point;
    QWidget *m_centralWidget;
    QWidget *m_topWidget;
    QWidget *m_bottomWidget;
};

#endif // LOCATIONSDISPLAY_H
