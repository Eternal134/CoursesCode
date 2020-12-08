#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tw_page->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tw_page->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tw_request->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tw_request->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    displayRequest();
    connect(&page, &Page::directTransfer, this, [=](int index){
        outputPage(index);
        ui->tw_page->item(nowRequest, index)->setBackgroundColor(QColor(85, 255, 255, 200));
    });
    connect(&page, &Page::pageMissing, this, [=](int index){
        outputPage(index);
        ui->tw_page->item(nowRequest, index)->setBackgroundColor(QColor(255, 85, 127, 200));
    });
    connect(&page, &Page::requestSuccess, this, [=](int index){
        outputPage(index);
        ui->tw_page->item(nowRequest, index)->setBackgroundColor(QColor(0, 255, 0, 200));
    });
}

void MainWindow::outputPage(int index) {
    for(int i = 0; i < page.table().length(); i ++) {
        ui->tw_page->setItem(nowRequest, i, new QTableWidgetItem(QString::number(page.table().value(i))));
        ui->tw_page->item(nowRequest, i)->setTextAlignment(Qt::AlignCenter);
    }
}

void MainWindow::displayRequest() {
    for(int i = 0; i < ui->tw_request->rowCount(); i ++) {
        ui->tw_request->setItem(i, 0, new QTableWidgetItem(QString::number(page.request().value(i))));
        ui->tw_request->item(i, 0)->setTextAlignment(Qt::AlignCenter);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked() {
    page.optAlgorithm(nowRequest);
    nowRequest ++;
}

void MainWindow::on_pushButton_2_clicked()
{
    window()->close();
}
