#include "pagetable.h"

PageTable::PageTable(QObject *parent) : QObject(parent)
{

}

int PageTable::reset(int logical) {
    int pagenum = logical / pagesize;
    int w = logical % pagesize;
    if(pagenum >= tableLength) {
        emit outOfRange(pagenum);
        return -1;
    }
    int blockNum = table[pagenum];
    emit calComplete(pagenum, w, blockNum);
    return blockNum * pagesize + w;
}
