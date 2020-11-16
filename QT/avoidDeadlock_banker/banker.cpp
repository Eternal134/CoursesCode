#include "banker.h"
#include <QDebug>

Banker::Banker(QObject *parent) : QObject(parent)
{

}

bool isAllTrue(bool a[], int len) {
    // 判断一个布尔型数组的值是否全为真
    for(int i = 0; i < len; i ++) {
        if(!a[i]) { return false; }
    }
    return true;
}

bool Banker::isSafeNow() {
    // 判断系统是否安全
    int Work[resourses];
    bool Finish[resourses];
    for(int i = 0; i < resourses; i ++) {
        Work[i] = Availiable[i];
        Finish[i] = false;
    }
    while(1) {
        // 一直尝试从未完成的进程中找到一个可以执行的进程
        bool isSuccess = false;
        for(int num = 0; num < processes; num ++) {
            if(!Finish[num]) {
                bool isExceed = false;
                for(int i = 0; i < resourses; i ++) {
                    // 判断进程num所需要的资源量是否超过现有资源量
                    if(Need[num][i] > Work[i]) {
                        // 超过了
                        isExceed = true;
                        break;
                    }
                }
                if(!isExceed) {
                    for(int i = 0; i < resourses; i ++) {
                        Work[i] += Allocation[num][i];
                    }
                    Finish[num] = true;
                    isSuccess = true;
                }
            }
            if(isSuccess) { break; }
        }
        // 如果没有找到一个可以执行的进程且此时所有进程没有执行完, 代表此时系统不安全
        if(!isSuccess && !isAllTrue(Finish, resourses)) { return false; }
        if(isAllTrue(Finish, resourses)) { return true; }
    }

}

bool Banker::allocate(int num, int request[]) {

    for(int i = 0; i < resourses; i ++) {
        // 检查需求的资源量是否符合要求
        if(request[i] > Need[num][i]) {
            // 发送信号，发出弹窗，提示需求的资源量超出了声明的最大资源量
            emit requestExceedNeed();
            return false;
        }
        if(request[i] > Availiable[i]) {
            // 发送信号，发出弹窗，提示需求的资源量超出了现有资源量
            emit requestExceedAvailable();
            return false;
        }
    }
    for(int i = 0; i < resourses; i ++) {
        // 修改系统资源数据结构的值
        Availiable[i] -= request[i];
        Allocation[num][i] += request[i];
        Need[num][i] -= request[i];
    }
    if(!isSafeNow()) {
        // 如果分配资源之后系统不安全
        for(int i = 0; i < resourses; i ++) {
            // “没收”刚分配的资源
            Availiable[i] += request[i];
            Allocation[num][i] -= request[i];
            Need[num][i] += request[i];
        }
        emit allocateFailed();
        return false;
    }
    else {
        emit allocateSucceed();
        return true;
    }
}

void Banker::myDebug() {
    for(int i = 0; i < 5; i ++) {
        qDebug() << Allocation[i][0] << " " << Allocation[i][1] << " " << Allocation[i][2];
    }
}
