#ifndef PAGE_H
#define PAGE_H

#include <QObject>

class Page : public QObject
{
    Q_OBJECT
public:
    explicit Page(QObject *parent = nullptr);

signals:

};

#endif // PAGE_H
