#ifndef ROUTEONEITEMWIDGET_H
#define ROUTEONEITEMWIDGET_H

#include <QWidget>
#include <QDateTime>

namespace Ui {
    class RouteOneItemWIdget;
}

class RouteOneItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RouteOneItemWidget(QWidget *parent = 0);
    ~RouteOneItemWidget();

    void setStartTime(QDateTime& time);
    void setEndTime(QDateTime& time);
    void setStopTime(QDateTime& time);
    void setDuration(QTime& time);
    void setItemsWidget(QLayout *widget);

private:
    Ui::RouteOneItemWIdget *ui;
};

#endif // ROUTEONEITEMWIDGET_H
