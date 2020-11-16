#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "banker.h"
#include <QMessageBox>
#include <QTableWidget>
#include <QDebug>

void MainWindow::setDataStructureTabelWidget(QTableWidget *tableWidget) {
    // 设置用于显示数据结构的表格的样式
    tableWidget->setColumnCount(banker->getResourses());
    tableWidget->setRowCount(banker->getProcesses());
    QStringList headers;
    for(int i = 0; i < tableWidget->colorCount(); i ++) {
        headers << QString(char(65 + i));
    }
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->resizeRowsToContents();
    tableWidget->setHorizontalHeaderLabels(headers);
    tableWidget->setAlternatingRowColors(true);
    tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgba(248,191,154,0.8);}");
}

void MainWindow::updateDataStructureTabelWidgets() {
    // 更新几个表示数据结构的表格
    ui->tableWidget_Allocation->clearContents();
    ui->tableWidget_Available->clearContents();
    ui->tableWidget_Max->clearContents();
    ui->tableWidget_Need->clearContents();
    for(int i = 0; i < ui->tableWidget_Available->columnCount(); i ++) {
        ui->tableWidget_Available->setItem(0, i, new QTableWidgetItem(
                                                    QString::number(banker->Availiable[i])));
        ui->tableWidget_Available->item(0, i)->setTextAlignment(Qt::AlignHCenter);
    }
    for(int i = 0; i < banker->getProcesses(); i ++) {
        for(int j = 0; j < banker->getResourses(); j ++) {
            ui->tableWidget_Allocation->setItem(i, j, new QTableWidgetItem(
                                                    QString::number(banker->Allocation[i][j])));
            ui->tableWidget_Allocation->item(i, j)->setTextAlignment(Qt::AlignHCenter);
            ui->tableWidget_Max->setItem(i, j, new QTableWidgetItem(
                                                    QString::number(banker->Max[i][j])));
            ui->tableWidget_Max->item(i, j)->setTextAlignment(Qt::AlignHCenter);
            ui->tableWidget_Need->setItem(i, j, new QTableWidgetItem(
                                                    QString::number(banker->Need[i][j])));
            ui->tableWidget_Need->item(i, j)->setTextAlignment(Qt::AlignHCenter);
        }
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("银行家算法模拟实验");
    connect(banker, Banker::requestExceedNeed, [=](){
        QMessageBox::information(this, "提示", "需求资源量超出声明的最大资源量");
    });
    connect(banker, Banker::requestExceedAvailable, [=](){
        QMessageBox::information(this, "提示", "需求资源量过多，进程挂起");
    });
    connect(banker, Banker::allocateFailed, [=](){
        QMessageBox::information(this, "提示", "分配后系统进入不安全状态，分配失败！");
    });
    connect(banker, Banker::allocateSucceed, [=](){
        QMessageBox::information(this, "提示", "分配资源成功！");
        updateDataStructureTabelWidgets();
    });
    setDataStructureTabelWidget(ui->tableWidget_Allocation);
    setDataStructureTabelWidget(ui->tableWidget_Available);
    ui->tableWidget_Available->setRowCount(1);
    setDataStructureTabelWidget(ui->tableWidget_Need);
    setDataStructureTabelWidget(ui->tableWidget_Max);
    updateDataStructureTabelWidgets();

    tableWidget_log->setWindowTitle("申请记录");
    tableWidget_log->setColumnCount(5);
    tableWidget_log->setHorizontalHeaderLabels(QStringList() << "进程名" << "资源量A" <<
                                               "资源量B" << "资源量C" << "是否成功");
    tableWidget_log->resize(600, 400);
    tableWidget_log->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget_log->setAlternatingRowColors(true);
    tableWidget_log->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:"
                                                   "rgba(248,191,154,0.8);}");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_request_clicked() {
   // 按下申请资源按钮时
    int process = ui->spinBox_num->value() - 1;
    if(process < 0 || process >= banker->getProcesses()) {
        QMessageBox::information(this, "提示", "没有此进程！");
        return ;
    }
    int requests[3];
    requests[0] = ui->spinBox_A->value();
    requests[1] = ui->spinBox_B->value();
    requests[2] = ui->spinBox_C->value();
    bool isSucess = banker->allocate(process, requests);
    /* 将此申请记录到tableWidget_log中 */
    tableWidget_log->insertRow(tableWidget_log->rowCount());
    tableWidget_log->setItem(tableWidget_log->rowCount() - 1, 0, new QTableWidgetItem(
                                 QString::number(process + 1)));
    tableWidget_log->setItem(tableWidget_log->rowCount() - 1, 1, new QTableWidgetItem(
                                 QString::number(requests[0])));
    tableWidget_log->setItem(tableWidget_log->rowCount() - 1, 2, new QTableWidgetItem(
                                 QString::number(requests[1])));
    tableWidget_log->setItem(tableWidget_log->rowCount() - 1, 3, new QTableWidgetItem(
                                 QString::number(requests[2])));
    if(isSucess) {
        tableWidget_log->setItem(tableWidget_log->rowCount() - 1, 4, new QTableWidgetItem("成功"));
    }
    else {
        tableWidget_log->setItem(tableWidget_log->rowCount() - 1, 4, new QTableWidgetItem("失败"));
    }
    for(int i = 0; i < tableWidget_log->rowCount(); i ++) {
        // 设置字体居中
        for(int j = 0; j < tableWidget_log->columnCount(); j ++) {
            tableWidget_log->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }
    ui->spinBox_num->setValue(0);
    ui->spinBox_A->setValue(0);
    ui->spinBox_B->setValue(0);
    ui->spinBox_C->setValue(0);
}

void MainWindow::on_pushButton_clicked() {
    // 点下关闭程序按钮
    this->close();
}

void MainWindow::on_pushButton_log_clicked() {
    // 点击查看日志按钮
    tableWidget_log->show();
}
