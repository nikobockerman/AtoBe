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

    QList<RouteNew*> routes;
};

#endif // ROUTERESULTWIDGET_H
