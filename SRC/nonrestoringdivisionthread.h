#ifndef NONRESTORINGDIVISIONTHREAD_H
#define NONRESTORINGDIVISIONTHREAD_H

#include <QObject>
#include <QThread>

class NonRestoringDivisionThread : public QObject
{
    Q_OBJECT
public:
    explicit NonRestoringDivisionThread(QList<int>, QList<int>, QList<int>, QObject *parent = nullptr);

    void calculate();

signals:
    void updateList(QList<int>, QList<int>, QString, int op, bool dash = false, bool newStep = false);

private:
    int binToDec(QList<int> bin);//convert binary list to decimal
    QList<int> decToBin(int dec, int bits = 0); //convert decimal string input into binary list

    QList<int> inputABin, inputBBin, outputCBin;
    uint wait;
};

#endif // NONRESTORINGDIVISIONTHREAD_H
