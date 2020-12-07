#ifndef BANK_H
#define BANK_H

#include <QMainWindow>

class Bank : public QMainWindow
{
    Q_OBJECT
public:
    explicit Bank(QWidget *parent = nullptr);
    bool allocate(int num, int request[]);

signals:

private:
    int resourses = 3;
    int Availiable[3] = {3, 3, 2};                                              // 可利用资源向量
    int Max[5][3] = {{7,5,3}, {3,2,2}, {9,0,2}, {2,2,2}, {4,3,3}};              // 最大需求矩阵
    int Allocation[5][3] = {{0,1,0}, {2,0,0}, {3,0,2}, {2,1,1}, {0,0,2}};       // 分配矩阵
    int Need[5][3] = {{7,4,3}, {1,2,2}, {6,0,0}, {0,1,1}, {4,3,1}};             // 需求矩阵
    int over[5] = {0,0,0,0,0};

};

#endif // BANK_H
