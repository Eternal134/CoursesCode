#ifndef PAGETABLE_H
#define PAGETABLE_H

#include <QObject>

class PageTable : public QObject
{
    Q_OBJECT
public:
    explicit PageTable(QObject *parent = nullptr);
    int size() {return pagesize;}
    int length() { return tableLength; }
    int *getTable() { return table; }
    int reset(int logical);

signals:

    void outOfRange(int pagenum);
    calComplete(int pagenum, int w, int blocknum);

private:

    int pagesize = 1024;
    int tableLength = 64;
    int table[64] = {0,42,29,15,45,31,44,43, 41,28,1,30,12,24,6,32,
                     14,27,13,46,7,33,10,22, 40,2,51,11,39,23,49,50,
                     26,16,25,4,47,17,3,48, 52,36,58,35,57,34,21,63,
                     5,37,18,8,62,56,20,54, 60,19,38,9,61,55,59,53};

};

#endif // PAGETABLE_H
