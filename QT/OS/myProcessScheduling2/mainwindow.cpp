#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setButtonStyle.h"
#include <QDebug>
#include <QMessageBox>
#include <windows.h>

void OrderInsert(RQueen rqueen, PCB* pcb) {
    // 按优先级将pcb插入到就绪队列rqueen中
    if(!rqueen->next) {
        rqueen->next = pcb;
    }
    else {
        PCB* p1 = rqueen, * p2 = p1->next;
        if(!p2) {
            p1->next = pcb;
        }
        else {
            while(p2) {
                if(p2->super > pcb->super) {
                    p1 = p2;
                    p2 = p1->next;
                }
                else {
                    p1->next = pcb;
                    pcb->next = p2;
                    return;
                }
            }
            p1->next = pcb;
        }
    }
}

void deleteFirstPCB(RQueen rqueen) {

    PCB *first_pcb = rqueen->next;
    if(first_pcb != nullptr) {
        rqueen->next = first_pcb->next;
        delete first_pcb;
    }
}

void run(RQueen rqueen) {
    // 执行队首的进程
    if(rqueen->next == nullptr) return;
    PCB *first = rqueen->next;

    if(first == nullptr) {
        return ;
    }
    first->costed_time ++;
    first->super --;

    if(first->costed_time == first->need_time) {
        deleteFirstPCB(rqueen);
    }
    else {
        rqueen->next = first->next;
        first->next = nullptr;
        OrderInsert(rqueen, first);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "进程名" << "优先级" << "需要的CPU时间" <<
                                               "已获得的CPU时间");
    // 隐藏垂直表头
    ui->tableWidget->verticalHeader()->hide();
    // 设置表头颜色
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgba(248,191,154,0.5);}");
    // 表头填充
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // 相邻行交替颜色
    ui->tableWidget->setAlternatingRowColors(true);
    // 禁止编辑
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 日志对话框大小
    int width = 900, hight = 600;
    dia->setFixedSize(width, hight);
    dia->setWindowTitle("日志");
    // 设置日志对话框中的第一个表格
    wid->setFixedSize(width, hight * 0.6);
    wid->move(0, hight * 0.05);
    wid->setColumnCount(2);
    wid->setHorizontalHeaderLabels(QStringList() << "进程名" << "优先级");
    wid->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    wid->horizontalHeader()->setStyleSheet("QHeaderView::section{"
                                                               "background-color:rgba(248,191,154,0.5);}");
    wid->setEditTriggers(QAbstractItemView::NoEditTriggers);
    wid->setAlternatingRowColors(true);
    wid->verticalHeader()->hide();
    // 设置日志对话框中的第二个表格
    wid_completed_process->setFixedSize(width, hight * 0.3);
    wid_completed_process->move(0, hight * 0.7);
    wid_completed_process->setColumnCount(2);
    wid_completed_process->setHorizontalHeaderLabels(QStringList() << "进程名" << "消耗的CPU时间");
    wid_completed_process->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    wid_completed_process->horizontalHeader()->setStyleSheet("QHeaderView::section{"
                                                              "background-color:rgba(248,191,154,0.5);}");
    wid_completed_process->setEditTriggers(QAbstractItemView::NoEditTriggers);
    wid_completed_process->setAlternatingRowColors(true);
    wid_completed_process->verticalHeader()->hide();

    wid_title1->setText("执行进程记录");
    wid_title1->setAlignment(Qt::AlignCenter);
    wid_title1->setFixedSize(width, hight * 0.05);
    wid_title1->move(0, 0);
    wid_title1->setReadOnly(true);
    wid_title1->setStyleSheet("background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, "
                              "stop:0 rgba(255, 246, 183, 255), stop:1 rgba(246, 65, 108, 255))");

    wid_title2->setText("已完成的进程");
    wid_title2->setAlignment(Qt::AlignCenter);
    wid_title2->setFixedSize(width, hight * 0.05);
    wid_title2->move(0, hight * 0.65);
    wid_title2->setReadOnly(true);
    wid_title2->setStyleSheet("background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, "
                              "stop:0 rgba(255, 246, 183, 255), stop:1 rgba(246, 65, 108, 255))");

    setButtonStyleSheet(ui->pushButton);
    setButtonStyleSheet(ui->pushButton_2);
    setButtonStyleSheet(ui->pushButton_3);
    setButtonStyleSheet(ui->pushButton_4);

    ui->pushButton->setDefault(true);

    connect(ui->pushButton_4, QPushButton::clicked, [=](){
        // 显示日志按钮
        dia->show();
    });
}

MainWindow::~MainWindow() {

    delete ui;
}

void MainWindow::updateTableWidget() {
    // 更新显示就绪队列的表格
    for(int row = ui->tableWidget->rowCount() - 1; row >= 0; row --) {
        ui->tableWidget->removeRow(row);
    }
    PCB *p = rqueen->next;
    int i = 0, j;
    while(p) {
        j = 0;
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(i, j ++, new QTableWidgetItem(p->name));
        ui->tableWidget->setItem(i, j ++, new QTableWidgetItem(QString::number(p->super)));
        ui->tableWidget->setItem(i, j ++, new QTableWidgetItem(QString::number(p->need_time)));
        ui->tableWidget->setItem(i, j ++, new QTableWidgetItem(QString::number(p->costed_time)));
        p = p->next;
        i ++;
    }
}

void MainWindow::on_pushButton_clicked() {
    // 添加进程按钮
    PCB *pcb = new PCB;
    pcb->name = ui->lineEdit->text();
    pcb->super = ui->spinBox->value();
    pcb->need_time = ui->spinBox_2->value();
    if(pcb->name.isEmpty()) {
        QMessageBox::information(this, "提示", "无效的进程名");
    }
    else if(!pcb->need_time) {
        QMessageBox::information(this, "提示", "需要的CPU时间不能为0");
    }
    else {
        OrderInsert(rqueen, pcb);
        ui->lineEdit->clear();
        ui->spinBox->setValue(0);
        ui->spinBox_2->setValue(0);
    }
    updateTableWidget();
}

void MainWindow::on_pushButton_3_clicked() {
    // 关闭按钮
    this->close();
}

void MainWindow::on_pushButton_2_clicked() {
    // 执行进程按钮
    PCB *first = rqueen->next;
    if(first == nullptr) {
        QMessageBox::information(this, "提示", "没有可以执行的进程");
        return ;
    }
    if(first->costed_time + 1 == first->need_time) {
        wid_completed_process->insertRow(wid_completed_process->rowCount());
        wid_completed_process->setItem(wid_completed_process->rowCount() - 1, 0,
                                      new QTableWidgetItem(first->name));
        wid_completed_process->setItem(wid_completed_process->rowCount() - 1, 1,
                                      new QTableWidgetItem(QString::number(first->need_time)));
    }
    wid->insertRow(wid->rowCount());
    wid->setItem(wid->rowCount() - 1, 0, new QTableWidgetItem(first->name));
    wid->setItem(wid->rowCount() - 1, 1, new QTableWidgetItem(QString::number(first->super)));
    run(rqueen);
    updateTableWidget();
}
