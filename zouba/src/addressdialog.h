#ifndef ADDRESSDIALOG_H
#define ADDRESSDIALOG_H

#include <QDialog>
#include <QList>

class Location;
class QString;
class QWidget;
class QLineEdit;
class QNetworkReply;
class QListWidget;
class QListWidgetItem;

/* TODO: Layout
 * - Name and andress text input fields in a form layout on the left
 *   - Name text input field not enabled if editing an existing location
 * - Buttons on the right
 *   - Add button
 *     - Enabled if search once and no typing has been done to address
 *   - Search
 *     - Searches for the address in the address text input field
 */
class AddressDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddressDialog(QWidget *parent = 0, const Location *location = 0);

signals:
    void busy(bool busy);

public slots:
    void searchFinished();
    void locationSelected(Location* location);

private slots:
    void searchAddress();
    void addLocation();
    void typedInAddress();

private:
    QLineEdit *m_label;
    QLineEdit *m_address;
    QPushButton *m_addButton;

    QNetworkReply *m_reply;

    QList<Location*> m_places;
    QList<Location*> m_roadNames;
    QList<Location*> m_stops;
    
    Location* m_current;
};



/* TODO: Layout
 * - One list of found locations
 * - Clicking one selects the location
 * - If the clicked one is disabled, nothing happens (clicked signal might not be enabled so this needs to implemented only if selecting a heading line emits clicked signal
 * - When selected emits locationSelected(Location *location) signal with the selected locations copy.
 * - When selected calls close
 */
class AddressDialogSelection : public QDialog
{
    Q_OBJECT
public:
    explicit AddressDialogSelection(const QList<Location*> &places, const QList<Location*> &roads, const QList<Location*> &stops, QWidget *parent = 0);

signals:
    void locationSelected(Location* location);
    
private slots:
    void itemSelected(QListWidgetItem *item);

private:
  const QList<Location*>& m_places;
  const QList<Location*>& m_roads;
  const QList<Location*>& m_stops;
};

#endif // ADDRESSDIALOGNEW_H
