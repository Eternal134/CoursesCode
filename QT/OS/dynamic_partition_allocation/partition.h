#ifndef PARTITION_H
#define PARTITION_H

#include <QObject>

class Partition : public QObject
{
    Q_OBJECT
public:
    explicit Partition(QObject *parent = nullptr);
    Partition *front() { return Front; }
    Partition *next() { return Next; }
    int length() { return Length; }
    void setLength(int l) { Length = l; }
    int status() { return Status; }
    void setStatus(int my_status) { Status = my_status; }
    int start() { return Start; }
    void setStart(int my_start) { Start = my_start; }
    QString name() { return Name; }
    void setName(QString my_name) { Name = my_name; }
    void setNext(Partition *part) { Next = part; }
    void setFront(Partition *part) { Front = part; }

signals:

private:

    Partition *Front = nullptr;
    Partition *Next = nullptr;
    int Start = 0;
    int Length = 0;
    int Status = 0;
    QString Name = QString("空闲");

};

#endif // PARTITION_H
