#include "routeresultwidget.h"
#include "ui_routeresultwidget.h"

#include "routelegwidget.h"
#include "routeoneitemwidget.h"

#include "src/logic/routeleg.h"

#include <QLabel>
#include <QList>
#include <QScrollArea>
#include <QScrollBar>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QTime>

RouteResultWidget::RouteResultWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RouteResultWidget),
    routes()
{

    ui->setupUi(this);
#ifdef Q_WS_MAEMO_5
    this->setAttribute(Qt::WA_Maemo5StackedWindow);
    connect(QApplication::desktop(), SIGNAL(resized(int)), SLOT(rotationEvent()));
    //this->setObjectName(this->parent()->objectName());
    //this->resize(800, 480);
#endif
    this->setWindowTitle(QCoreApplication::applicationName());
}

RouteResultWidget::~RouteResultWidget()
{
    delete ui;
}

void RouteResultWidget::addRoute(RouteNew *route)
{
    RouteOneItemWidget *item = new RouteOneItemWidget();

    QHBoxLayout *layout = new QHBoxLayout();

    item->setStartTime(route->startTime);
    item->setEndTime(route->endTime);

    RouteLeg *leg = route->route.at(0);
    if (leg->type == WALK)
    {
        if (route->route.size() > 1)
            leg = route->route.at(1);
        else
            leg = NULL;
    }
    if (leg == NULL)
    {
        QDateTime none;
        item->setStopTime(none);
    }
    else
        item->setStopTime(leg->startPoint->departure_time);

    QTime duration = QTime().addSecs(route->startTime.secsTo(route->endTime));
    qDebug() << "Duration:" << duration;
    qDebug() << "Seconds:" << route->startTime.secsTo(route->endTime);
    item->setDuration(duration);

    QList<RouteLeg*>::const_iterator iter;
    for (iter = route->route.constBegin(); iter != route->route.constEnd(); iter++)
    {
        RouteLegWidget *leg_widget = new RouteLegWidget();
        leg_widget->setDisplay(*iter);
        layout->addWidget(leg_widget);
        layout->setSpacing(0);
    }

    item->setItemsWidget(layout);

    this->routes.append(item); // Might be unnecessary

    QListWidgetItem *listItem = new QListWidgetItem("");
    item->adjustSize();

    qDebug() << "Item size:" << item->size().width();
    qDebug() << "SizeHint:" << item->sizeHint().width();
    qDebug() << "Min:" << item->minimumWidth();
    qDebug() << "Max:" << item->maximumWidth();

    listItem->setSizeHint(item->sizeHint());
    this->ui->routesArea->addItem(listItem);
    this->ui->routesArea->setItemWidget(listItem, item);

    //this->ui->routesArea->setMinimumWidth(this->ui->routesArea->sizeHint().width());
}
