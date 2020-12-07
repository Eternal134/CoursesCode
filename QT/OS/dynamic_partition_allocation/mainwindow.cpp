#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsRectItem>
#include <QDebug>
#include <QAction>
#include <QIcon>
#include <QMenu>
#include <QWidget>
#include <QCursor>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("动态分区分配算法");
    ui->centralwidget->resize(this->window()->size());
    ui->labBackground->resize(this->window()->size());
    ui->tableWidget->setColumnCount(5);
    QStringList headers = QStringList() << "进程名" << "状态" << "大小" << "起始地址" << "结束地址";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color: rgba(255, 255, 255, 100);}");
    ui->tableWidget->verticalHeader()->setStyleSheet("QHeaderView::section{background-color: rgba(255, 255, 255, 100);}");
    updateFreeListWidget();
    connect(storer, &Storer::allocateSucceed, this, [=](){
        QMessageBox::information(this, "分配内存成功", "分配成功");
    });
    connect(storer, &Storer::allocateFailed_noFit, this, [=](){
        QMessageBox::information(this, "分配内存失败", "没有找到合适的空闲块，分配失败");
    });
    connect(storer, &Storer::nullName, this, [=](){
        QMessageBox::information(this, "失败", "进程名不能为空");
    });
    connect(storer, &Storer::releaseFailed_OS, this, [=](){
        QMessageBox::information(this, "释放内存失败", "无法释放操作系统的内存空间");
    });
    connect(ui->btnApply, &btn_apply::toChoose, this, [=](){
        // 准备选择算法时
        name = ui->lineEditName->text();
        len = ui->spinBoxLen->value();
    });
    connect(ui->btnApply, &btn_apply::choseFirstFit, this, [=](){
        // 选择首次适应算法
        storer->firstFitAllocate(name, len);
    });
    connect(ui->btnApply, &btn_apply::choseBestFit, this, [=](){
        // 选择最佳适应算法
        storer->bestFitAllocate(name, len);
    });
    connect(ui->btnApply, &btn_apply::choseNextFit, this, [=](){
        // 选择循环适应算法
        storer->nextFitAllocate(name, len);
    });
    connect(ui->btnApply, &btn_apply::chosen, this, [=](){
        // 选择算法完后
        ui->lineEditName->clear();
        ui->spinBoxLen->setValue(0);
        updateFreeListWidget();
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateFreeListWidget() {
    Partition *p = storer->Free();
    for(int i = ui->tableWidget->rowCount(); i >=0; i --) {
        ui->tableWidget->removeRow(i);
    }
    int row = 0;
    while(p) {
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(p->name()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(p->status())));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(p->length())));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(p->start())));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(p->start() + p->length())));
        row ++;
        p = p->next();
    }
}

void MainWindow::on_pushButtonRelease_clicked() {
    QString name = ui->lineEditName->text();
    if(name.isEmpty()) {
        QMessageBox::information(this, "提示", "进程名不能为空");
        return ;
    }
    if(ui->spinBoxLen->value()) {
        QMessageBox::information(this, "提示", "释放内存时不需要指定大小");
    }
    if(storer->release(name)) {
        QMessageBox::information(this, "释放内存成功", "释放内存成功");
    }
    else {
        QMessageBox::information(this, "释放内存失败", "没有此进程，释放内存失败");
    }
    updateFreeListWidget();
}

void MainWindow::on_pushButton_clicked() {
    window()->close();
}

void MainWindow::on_btnApply_clicked() {

}
