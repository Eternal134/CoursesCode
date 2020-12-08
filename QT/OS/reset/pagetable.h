#ifndef PAGETABLE_H
#define PAGETABLE_H

#include <QObject>

class PageTable : public QObject
{
    Q_OBJECT
public:
    explicit PageTable(QObject *parent = nullptr);

signals:

};

#endif // PAGETABLE_H
