#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QSpinBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){
        int result = pageTable.reset(value);
        ui->line_phyics->setText(QString::number(result));
    });
    connect(&pageTable, &PageTable::outOfRange, this, [=](int pageNum){
        QMessageBox::information(this, "提示", "访问越界，页面号:" + QString::number(pageTable.getTable()[pageNum]));
        ui->spinBox->clear();
    });
    connect(&pageTable, &PageTable::calComplete, this, [=](int pageNum, int w, int blockNum){
        ui->tableWidget->setCurrentItem(NULL);
        ui->tableWidget->item(pageNum / 8, pageNum % 8)->setSelected(true);
        ui->line_w->setText(QString::number(w));
        ui->line_pageNum->setText(QString::number(pageNum));
        ui->line_blockNum->setText(QString::number(blockNum));
    });
    for(int i = 0; i < 8; i ++) {
        for(int j = 0; j < 8; j ++) {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(QString::number(pageTable.getTable()[i*8+j])));
            ui->tableWidget->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }
    ui->spinBox->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

