#ifndef PAGE_H
#define PAGE_H

#include <QObject>
#include <QList>

class Page : public QObject
{
    Q_OBJECT
public:
    explicit Page(QObject *parent = nullptr);
    void init();
    void optAlgorithm(int requestIndex);
    int lenth() { return pageTableLen; }
    int num() { return requestNum; }
    QList<int> table() { return pageTable; }
    QList<int> request() { return requestStream; }


signals:

    void pageMissing(int index);
    void directTransfer(int index);
    void requestSuccess(int index);

private:
    int pageTableLen= 4;
    QList<int> pageTable;
    int requestNum = 15;
    QList<int> requestStream;
};

#endif // PAGE_H
