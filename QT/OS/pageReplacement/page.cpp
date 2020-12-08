#include "page.h"
#include <QTime>

Page::Page(QObject *parent) : QObject(parent)
{
    init();
}

void Page::init() {
    // 初始化请求流
   qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i = 0; i < requestNum; i ++) {
        // 生成1-10的随机数作为请求页面号
        requestStream << qrand() % 10;
    }
}

void Page::optAlgorithm(int requestIndex) {
    // 最佳置换算法
    int index;
    if((index = pageTable.indexOf(requestStream.value(requestIndex))) != -1) {
        // 如果内存中已有该页面，访问成功
        emit requestSuccess(index);
    }
    else if(pageTable.length() < pageTableLen) {
        // 如果内存中没有该页面，但是内存还有空闲区，直接调入
        pageTable.append(requestStream.value(requestIndex));
        emit directTransfer(pageTable.length() - 1);
    }
    else {
        // 否则进行页面置换
        int maxIndex = -1;          // 找到内存中自该请求以后最晚出现的页面请求
        int temp;                   // 临时记录一些值
        for(int j = 0; j < pageTableLen; j ++) {
            temp = requestStream.indexOf(pageTable.value(j), requestIndex + 1);
            if(temp == -1) {        // 如果后面的请求中再也没有出现过
                index = j;          //
                break;
            }
            if(temp > maxIndex) {   // 如果该页面会在请求流中出现的更晚
                maxIndex = temp;
                index = j;
            }
        }
        // 替换页面
        pageTable.replace(index, requestStream.value(requestIndex));
        emit pageMissing(index);
    }
}
