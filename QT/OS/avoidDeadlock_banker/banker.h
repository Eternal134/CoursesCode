#ifndef BANKER_H
#define BANKER_H

#include <QObject>

class MainWindow;

class Banker : public QObject
{
    Q_OBJECT
public:
    explicit Banker(QObject *parent = nullptr);
    bool allocate(int num, int request[]);
    bool isSafeNow();
    int getResourses() { return resourses; }
    int getProcesses() { return processes; }
    void myDebug();

signals:
    void requestExceedNeed();
    void requestExceedAvailable();
    void allocateSucceed();
    void allocateFailed();

private:
    int resourses = 3, processes = 5;

public:
    int Availiable[3] = {3, 3, 2};                                              // 可利用资源向量
    int Max[5][3] = {{7,5,3}, {3,2,2}, {9,0,2}, {2,2,2}, {4,3,3}};              // 最大需求矩阵
    int Allocation[5][3] = {{0,1,0}, {2,0,0}, {3,0,2}, {2,1,1}, {0,0,2}};       // 分配矩阵
    int Need[5][3] = {{7,4,3}, {1,2,2}, {6,0,0}, {0,1,1}, {4,3,1}};             // 需求矩阵
    int over[5] = {0,0,0,0,0};

};

#endif // BANKER_H
