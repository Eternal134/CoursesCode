#include "storer.h"
#include <QString>

Storer::Storer(QObject *parent) : QObject(parent) {
    free->setLength(sumLength);
    firstFitAllocate("操作系统", osOccupy);
    nextFitPtr = free;
}

bool Storer::firstFitAllocate(QString my_name, int len) {
    // 首次适应算法
    if(my_name.isEmpty()) {
        emit nullName();
        return false;
    }
    Partition *allocation = new Partition();
    Partition *p = free;
    while(p) {
        if((p->length() - len >= size) && (p->status() == 0)) {
            // 找到满足要求的空闲区块时, p指向当前满足要求的空闲区块, allocation指向要分配出去的空闲区块
            allocation->setLength(len);
            allocation->setStart(p->start());
            allocation->setName(my_name);
            allocation->setStatus(1);
            allocation->setNext(p);
            p->setLength(p->length() - len);
            p->setStart(p->start() + len);
            if(p->front()) {
                p->front()->setNext(allocation);
                allocation->setFront(p->front());
            }
            else {
                free = allocation;
            }
            p->setFront(allocation);
            emit allocateSucceed();
            return true;
        }
        p = p->next();
    }
    emit allocateFailed_noFit();
    return false;
}

bool Storer::bestFitAllocate(QString name, int len) {
    // 最佳适应算法
    if(name.isEmpty()) {
        emit nullName();
        return false;
    }
    Partition *allocation = new Partition();
    Partition *minPart = nullptr;
    Partition *p = free;
    while(p) {
        if((p->length() - len >= size) && (p->status() == 0)) {
            // 找到满足要求的最小空闲区块
            if(!minPart || p->length() < minPart->length()) {
                minPart = p;
            }
        }
        p = p->next();
    }
    if(!minPart) {
        // 如果没找到，发射分配失败信号
        emit allocateFailed_noFit();
        return false;
    }
    allocation->setLength(len);
    allocation->setName(name);
    allocation->setStatus(1);
    allocation->setStart(minPart->start());
    allocation->setFront(minPart->front());
    allocation->setNext(minPart);
    minPart->front()->setNext(allocation);
    minPart->setFront(allocation);
    minPart->setLength(minPart->length() - len);
    minPart->setStart(minPart->start() + len);

    emit allocateSucceed();
    return true;
}

bool Storer::nextFitAllocate(QString name, int len) {
    // 循环首次适应算法
    if(name.isEmpty()) {
        emit nullName();
        return false;
    }
    Partition *p = nextFitPtr->next();
    Partition *allocation = new Partition;
    int i = 1;
    while(i) {
        if(!p) {
            p = free;
        }
        if(p == nextFitPtr) {
            // 再执行最后一次循环
            i = 0;
        }
        if((p->length() - len >= size) && (p->status() == 0)) {
            allocation->setLength(len);
            allocation->setStart(p->start());
            allocation->setName(name);
            allocation->setStatus(1);
            allocation->setNext(p);
            allocation->setFront(p->front());
            p->setLength(p->length() - len);
            p->setStart(p->start() + len);
            p->front()->setNext(allocation);
            p->setFront(allocation);
            emit allocateSucceed();
            nextFitPtr = p;
            return true;
        }
        p = p->next();
    }
    emit allocateFailed_noFit();
    return false;
}

bool Storer::release(QString name) {
    // 内存释放算法
    if(name.isEmpty()) {
        // name为空时释放失败
        emit nullName();
        return false;
    }
    if(name == "操作系统") {
        // 试图释放操作系统时释放失败
        emit releaseFailed_OS();
        return false;
    }
    Partition *p = free, *deleteNode = nullptr;
    bool releaseSuccess = false;
    while(p) {
        if(p->name() == name) {
            deleteNode = p;
            if(p->front() && p->front()->status() == 0) {
                // 与前相连的空闲区合并
                p->front()->setLength(p->length() + p->front()->length());
                if(p->next()) {
                    p->front()->setNext(p->next());
                    p->next()->setFront(p->front());
                }
                else {
                    p->front()->setNext(nullptr);
                }
                p = p->front();
            }
            if(p->next() && p->next()->status() == 0) {
                // 与后相连的空闲区合并
                p->next()->setLength(p->length() + p->next()->length());
                p->next()->setStart(p->start());
                if(p->front()) {
                    p->front()->setNext(p->next());
                    p->next()->setFront(p->front());
                }
                else {
                    p->next()->setFront(nullptr);
                }
            }
            if(p->front() && p->next() && p->front()->status() && p->next()->status()) {
                // 如果前后都不相连，不需要合并操作
                p->setStatus(0);
                p->setName("空闲");
            }
            releaseSuccess = true;
            break;
        }
        p = p->next();
        delete deleteNode;
    }
    if(releaseSuccess) {
        // 如果释放成功
        emit releaseSucceed();
        return true;
    }
    else {
        emit releaseFailed_noSuchProcess();
        return false;
    }
}
