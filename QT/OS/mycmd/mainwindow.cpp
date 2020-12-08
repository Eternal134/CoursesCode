#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QDebug>
#include <stdlib.h>
//#include <

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_banker_clicked()
{
    QString program = "D:\\works\\courses\\CoursesCode\\QT\\OS\\exeFile_avoidDeadlockBanker\\avoidDeadlock_banker.exe";
    QProcess *process = new QProcess(this);
    process->start(program);
}

void MainWindow::on_btn_allocate_clicked()
{
    QString program = "D:/works/courses/CoursesCode/QT/OS/"
                      "build-dynamic_partition_allocation-Desktop_Qt_5_14_2_MinGW_32_bit-Release/release/dynamic_partition_allocation.exe";
    QProcess *process = new QProcess(this);
    process->start(program);
}

void MainWindow::on_pushButton_clicked()
{
    QString program = "D:/works/courses/CoursesCode/QT/OS/"
        "build-pageReplacement-Desktop_Qt_5_14_2_MinGW_32_bit-Release/release/pageReplacement.exe";
    QProcess *process = new QProcess(this);
    process->start(program);
}

void MainWindow::on_btn_reset_clicked()
{
    QString program = " D:/works/courses/CoursesCode/QT/OS/"
        "build-reset-Desktop_Qt_5_14_2_MinGW_32_bit-Release/release/reset.exe";
    QProcess *process = new QProcess(this);
    process->start(program);
}
