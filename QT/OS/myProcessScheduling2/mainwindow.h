#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QDialog>
#include <QTextEdit>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum States {W, R, F};

typedef struct PCB {
    PCB* next = nullptr;
    QString name;
    int super = 0;
    int arrive_time;
    int need_time;
    int costed_time = 0;
    States state;
}PCB, *RQueen;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void updateTableWidget();
    ~MainWindow();

    void enter_key(QKeyEvent *k);


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;

    RQueen rqueen = new PCB;
    QDialog *dia = new QDialog(this);
    QTableWidget *wid = new QTableWidget(dia);
    QTableWidget *wid_completed_process = new QTableWidget(dia);
    QTextEdit *wid_title1 = new QTextEdit(dia);
    QTextEdit *wid_title2 = new QTextEdit(dia);
};
#endif // MAINWINDOW_H
