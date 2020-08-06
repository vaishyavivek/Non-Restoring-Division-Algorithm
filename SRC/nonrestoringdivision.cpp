#include "nonrestoringdivision.h"
#include <math.h>
#include "outputtemplate.h"
#include "nonrestoringdivisionthread.h"

NonRestoringDivision::NonRestoringDivision(QObject *parent) : QObject(parent){
    fOperand1 = fOperand2 = -32767;
}


void NonRestoringDivision::setInputA(const QString &InputA){
    if(inputA != InputA){
        inputA = InputA;
        emit InputAChanged();
    }
}

void NonRestoringDivision::setInputB(const QString &InputB){
    if(inputB != InputB){
        inputB = InputB;
        emit InputBChanged();
    }
}

void NonRestoringDivision::setNumberSystem(const int &NumberSystem){
    if(numberSystem != NumberSystem){
        numberSystem = NumberSystem;
        emit NumberSystemChanged();
    }
}

void NonRestoringDivision::calculate(){
    if(numberSystem == 0){
        inputABin = makeBin(inputA);
        inputBBin = makeBin(inputB);
    }
    else if(numberSystem == 1){
        inputABin = decToBin(inputA.toInt(nullptr, 10));
        inputBBin = decToBin(inputB.toInt(nullptr, 10));
    }
    else if(numberSystem == 2){
        //just changing the base to 16 makes it usable with decToBin as well
        inputABin = decToBin(inputA.toInt(nullptr, 16));
        inputBBin = decToBin(inputB.toInt(nullptr, 16));
    }
    if(binToDec(inputBBin) == 0){
        operationText = "Here's your final result";
        emit OperationTextChanged();
    }
    else{
        inputBStr = binToStr(inputBBin);

        outputCBin = initBin(outputCBin, inputABin.length());

        NonRestoringDivisionThread *nrdt = new NonRestoringDivisionThread(inputABin, inputBBin, outputCBin);
        connect(nrdt, &NonRestoringDivisionThread::updateList, this, &NonRestoringDivision::receiveUpdate);
        connect(this, &NonRestoringDivision::triggerThread, nrdt, &NonRestoringDivisionThread::calculate);
        nrdt->moveToThread(&workerThread);

        if(workerThread.isRunning())
            workerThread.quit();

        operationSteps.clear();
        emit OperationStepsChanged();

        workerThread.start();
        emit triggerThread();
    }

}

void NonRestoringDivision::receiveUpdate(QList<int> InputA, QList<int> InputB, QString Comment, int op, bool dash, bool newStep){
    operation = op;
    emit operationChanged();

    outputCBin = InputA;
    inputABin = InputB;

    OutputTemplate *out = new OutputTemplate(binToStr(InputA), binToStr(InputB, dash), inputBStr, Comment, newStep);
    operationSteps.append(out);

    if(op != 1 && op != 4){
        emit Operand1Changed();
        emit Operand2Changed();
        emit OperationStepsChanged();
    }

    if(op == 0)
        operationText = "Initializing values, Accumulator with 00... and Multiplier with Q";
    else if(op == 1)
        operationText = "Left shift contents of A & Q by 1 bit and keep the Qₙ₋₁ empty, to be filled later";
    else if(op == 2)
        operationText = "Add contents of Accumulator and Multiplier and store the result in Accumulator, since A₀ bit is 1";
    else if(op == 3)
        operationText = "Subtract contents of Accumulator from Multiplier and store the result in Accumulator, since A₀ bit is 0";
    else if(op == 4)
        operationText = "Set A₀ bit as inverse Qₙ₋₁ bit";
    else if(op == 5)
        operationText = "Since final result in Accumulator is negative (11...), add A + M one more time and consider it as the result";
    else{
        fOperand1 = binToDec(outputCBin);
        emit FOperand1Changed();
        fOperand2 = binToDec(inputABin);
        emit FOperand2Changed();
        operationText = "Here's your final result";
    }

    emit OperationTextChanged();

}

void NonRestoringDivision::letFurtherUpdateHappen(){
    emit Operand1Changed();
    emit Operand2Changed();
    emit OperationStepsChanged();
}


QList<int> NonRestoringDivision::makeBin(QString bin){
    QList<int> binO;
    for(int i = bin.length() - 1; i >= 0; i--){
        binO.append(bin.at(i).unicode() - '0');
    }
    return binO;
}

QList<int> NonRestoringDivision::decToBin(int dec, int bits){
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


QList<int> NonRestoringDivision::initBin(QList<int> input, int bit){
    bit -= input.length();
    for(; bit > 0; bit--)
        input.append(0);
    return input;
}



QStringList NonRestoringDivision::makeString(QList<int> binList){
    QStringList output;
    for(int i = binList.length() - 1; i >= 0; i--)
        output.append(QString::number(binList.at(i)));
    return output;
}

QString NonRestoringDivision::binToStr(QList<int> binList, bool dash){
    QString str;
    while (!binList.isEmpty()) {
        str.append(QString::number(binList.last()));
        binList.removeLast();
    }
    if(dash)
        str.append("_");

    return str;
}

int NonRestoringDivision::binToDec(QList<int> bin){
    int output = 0;
    for (int i = 0; bin.length() > 0; i++) {
        output += static_cast<int>(bin.first()*pow(2, i));
        bin.removeFirst();
    }
    return output;
}
