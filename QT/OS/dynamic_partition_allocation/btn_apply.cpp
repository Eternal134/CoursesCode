#include "btn_apply.h"
#include <QMenu>

btn_apply::btn_apply(QWidget *parent) : QPushButton(parent)
{

}

void btn_apply::mousePressEvent(QMouseEvent *mouseEvent) {
    emit toChoose();
    QMenu *fitMethodMenu = new QMenu(this);
    QAction *firstFitAction = new QAction("首次适应算法", fitMethodMenu);
    QAction *bestFitAction = new QAction("最佳适应算法", fitMethodMenu);
    QAction *nextFitAction = new QAction("循环首次适应", fitMethodMenu);
    fitMethodMenu->addAction(firstFitAction);
    fitMethodMenu->addAction(bestFitAction);
    fitMethodMenu->addAction(nextFitAction);
    fitMethodMenu->setStyleSheet("QMenu{color: rgba(0, 0, 0, 200);}");
    connect(firstFitAction, QAction::triggered, this, [=](){
        emit choseFirstFit();
        emit chosen();
    });
    connect(bestFitAction, QAction::triggered, this, [=](){
        emit choseBestFit();
        emit chosen();
    });
    connect(nextFitAction, QAction::triggered, this, [=](){
        emit choseNextFit();
        emit chosen();
    });
    fitMethodMenu->popup(QCursor::pos());
}
