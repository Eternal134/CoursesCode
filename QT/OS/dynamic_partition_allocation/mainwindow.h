#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMenu>
#include <QAction>
#include "storer.h"
#include "btn_apply.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void updateFreeListWidget();

    ~MainWindow();

private slots:
    void on_pushButtonApply_clicked();

    void on_pushButtonRelease_clicked();

    void on_pushButton_clicked();

    void on_btnApply_clicked();

signals:

    void chooseFirstFitMethod();
    void chooseBestFitMethod();

private:
    Ui::MainWindow *ui;
    Storer *storer = new Storer;
    QString name;
    int len;
};
#endif // MAINWINDOW_H
