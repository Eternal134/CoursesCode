#ifndef STORER_H
#define STORER_H

#include <QObject>
#include "partition.h"

class Storer : public QObject
{
    Q_OBJECT
public:
    explicit Storer(QObject *parent = nullptr);
    bool firstFitAllocate(QString my_name, int len);
    bool bestFitAllocate(QString name, int len);
    bool nextFitAllocate(QString name, int len);
    bool release(QString name);
    Partition *Free() { return free; }

signals:

    void releaseSucceed();
    void releaseFailed_noSuchProcess();
    void releaseFailed_OS();
    void allocateSucceed();
    void nullName();
    void allocateFailed_noFit();

private:

    int sumLength = 512;            // 存储区总长度
    int osOccupy = 20;              // 操作系统占用长度
    int size = 5;                   // 空闲区块的最小不可分割长度
    Partition *free = new Partition();      // 指向空闲区链
    Partition *nextFitPtr = nullptr;        // 循环适应算法的循环指针
};

#endif // STORER_H
