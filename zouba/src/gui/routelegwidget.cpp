#include "routelegwidget.h"
#include "ui_routelegwidget.h"

RouteLegWidget::RouteLegWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RouteLegWidget)
{
    ui->setupUi(this);
}

RouteLegWidget::~RouteLegWidget()
{
    delete ui;
}

void RouteLegWidget::setDisplay(RouteLeg *leg)
{
#ifdef Q_WS_MAEMO_5
    int picSize = 40;
#else
    int picSize = 40;
#endif
    if (leg->type == WALK)
    {
        this->ui->image->setPixmap(QIcon(":/reittiopas/walk").pixmap(picSize));
        this->ui->image->adjustSize();
        this->ui->lineSymbol->setText("");
        this->ui->lineSymbol->adjustSize();
        return;
    }
    this->ui->lineSymbol->setText("<b>" + leg->symbol + "</b>");
    this->ui->lineSymbol->adjustSize();
    switch (leg->type)
    {
    case BUS:
        this->ui->image->setPixmap(QIcon(":/reittiopas/bus").pixmap(picSize));
        break;
    case FERRY:
        this->ui->image->setPixmap(QIcon(":/reittiopas/ferry").pixmap(picSize));
        break;
    case SUB:
        this->ui->image->setPixmap(QIcon(":/reittiopas/metro").pixmap(picSize));
        break;
    case TRAIN:
        this->ui->image->setPixmap(QIcon(":/reittiopas/train").pixmap(picSize));
        break;
    case TRAM:
        this->ui->image->setPixmap(QIcon(":/reittiopas/tram").pixmap(picSize));
        break;
    case WALK:
        break;
    }
    this->ui->image->adjustSize();
}
