#ifndef ROUTERESULTWIDGET_H
#define ROUTERESULTWIDGET_H

#include <QMainWindow>

#include "routeoneitemwidget.h"

#include "src/logic/routenew.h"

namespace Ui {
    class RouteResultWidget;
}

class RouteResultWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit RouteResultWidget(QWidget *parent = 0);
    ~RouteResultWidget();

    void addRoute(RouteNew *route);

private slots:

private:    
    Ui::RouteResultWidget *ui;

    QList<RouteOneItemWidget*> routes; // May be unnecessary
};

#endif // ROUTERESULTWIDGET_H
