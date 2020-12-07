#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "banker.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setDataStructureTabelWidget(QTableWidget *tableWidget);
    void updateDataStructureTabelWidgets();
    ~MainWindow();

private:
    Banker *banker = new Banker;
    QTableWidget *tableWidget_log = new QTableWidget();
    Ui::MainWindow *ui;

protected:

private slots:
    void on_pushButton_request_clicked();
    void on_pushButton_clicked();
    void on_pushButton_log_clicked();
};
#endif // MAINWINDOW_H
