#ifndef INTDATA_H
#define INTDATA_H

#include<QObject>

class IntData: public QObject{
    Q_OBJECT
    Q_PROPERTY(int Data READ Data NOTIFY DataChanged)

public:
    IntData(int Data, QObject *parent = nullptr)
        :QObject(parent){
        data = Data;
        emit DataChanged();
    }

    int Data() const{ return data;}

signals:
    void DataChanged();

private:
    int data;
};

#endif // INTDATA_H
