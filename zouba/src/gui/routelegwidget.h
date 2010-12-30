#ifndef ROUTELEGWIDGET_H
#define ROUTELEGWIDGET_H

#include <QWidget>

#include "src/logic/routeleg.h"

namespace Ui {
    class RouteLegWidget;
}

class RouteLegWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RouteLegWidget(QWidget *parent = 0);
    ~RouteLegWidget();

    void setDisplay(RouteLeg* leg);

private:
    Ui::RouteLegWidget *ui;
};

#endif // BUSWIDGET_H
