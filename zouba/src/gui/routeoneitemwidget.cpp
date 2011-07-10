#include "routeoneitemwidget.h"
#include "ui_routeoneitemwidget.h"

RouteOneItemWidget::RouteOneItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RouteOneItemWIdget)
{
    ui->setupUi(this);
}

RouteOneItemWidget::~RouteOneItemWidget()
{
    delete ui;
}

void RouteOneItemWidget::setDuration(QTime &time)
{
    QString disp;
    int hours = time.hour();
    if (hours > 0)
        disp.append(QString::number(hours) + " h ");
    disp.append(QString::number(time.minute()) + " min");
    this->ui->duration->setText(disp);
    this->ui->duration->adjustSize();
}

void RouteOneItemWidget::setEndTime(QDateTime &time)
{
    this->ui->endTime->setText(time.toString("hh:mm"));
    this->ui->endTime->adjustSize();
}

void RouteOneItemWidget::setStartTime(QDateTime &time)
{
    this->ui->startTime->setText(time.toString("hh:mm"));
    this->ui->startTime->adjustSize();
}

void RouteOneItemWidget::setStopTime(QDateTime &time)
{
    if (time == QDateTime())
    {
        /*QLabel *duration = this->ui->duration;
        this->ui->gridLayout->removeWidget(duration);
        this->ui->gridLayout->addWidget(duration, 0, 2, 1, 2);*/
        this->ui->stopTime->hide();
    }
    else
    {
        this->ui->stopTime->setText(time.toString("<b>hh:mm</b>"));
        this->ui->stopTime->adjustSize();
    }
}

void RouteOneItemWidget::setItemsWidget(QLayout *layout)
{
    this->ui->routeItems->setLayout(layout);
    this->ui->routeItems->adjustSize();
}
