#include "nonrestoringdivisionthread.h"
#include <math.h>

NonRestoringDivisionThread::NonRestoringDivisionThread(QList<int> par1, QList<int> par2, QList<int> par3, QObject *parent)
    : QObject(parent), inputABin(par1), inputBBin(par2), outputCBin(par3){
    wait = 4000;
}


void NonRestoringDivisionThread::calculate(){
    emit updateList(outputCBin, inputABin, "(0) Initial Values", 0);
    QThread::msleep(wait);
    int decBInput = binToDec(inputBBin);

    int count;
    for(count = 0; count < inputABin.length(); count++){
        outputCBin.removeLast();
        outputCBin.prepend(inputABin.last());
        inputABin.removeLast();

        emit updateList(outputCBin, inputABin, "(" + QString::number(count + 1) + ") Left Shift A + Q", 1, true, true);
        QThread::msleep(wait);

        if(outputCBin.last() == 1){
            outputCBin = decToBin(binToDec(outputCBin) + decBInput, inputABin.length() + 1);
            emit updateList(outputCBin, inputABin, "A ⃪ A + M", 2, true);
            QThread::msleep(wait);
        }
        else{
            outputCBin = decToBin(binToDec(outputCBin) - decBInput, inputABin.length() + 1);
            emit updateList(outputCBin, inputABin, "A ⃪ A - M", 3, true);
            QThread::msleep(wait);
        }

        inputABin.prepend(!outputCBin.last());
        emit updateList(outputCBin, inputABin, "A₀ ⃪ !Qₙ₋₁", 4);
        QThread::msleep(wait);
    }

    if(outputCBin.last() == 1){
        int negativeRes = binToDec(outputCBin);
        negativeRes += decBInput;
        outputCBin = decToBin(negativeRes, outputCBin.length());
        emit updateList(outputCBin, inputABin, "(" + QString::number(count++) + ") For negative output", 5, false, true);
    }

    emit updateList(outputCBin, inputABin, "(" + QString::number(count) + ") Final Output", 6, false, true);

}

int NonRestoringDivisionThread::binToDec(QList<int> bin){
    int output = 0;
    for (int i = 0; bin.length() > 0; i++) {
        output += bin.first()*pow(2, i);
        bin.removeFirst();
    }
    return output;
}

QList<int> NonRestoringDivisionThread::decToBin(int dec, int bits){
    QList<int> bin;
    if(bits > 0){
        while(bits > 0){
            bin.append(dec & 0x1);
            dec = dec >> 1;
            bits--;
        }
    }
    else{
        while (dec > 0) {
            bin.append(dec % 2);
            dec /= 2;
        }
    }

    return  bin;
}
