#ifndef NONRESTORINGDIVISION_H
#define NONRESTORINGDIVISION_H

#include <QObject>
#include <QThread>

class NonRestoringDivision : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString InputA READ InputA WRITE setInputA NOTIFY InputAChanged)
    Q_PROPERTY(QString InputB READ InputB WRITE setInputB NOTIFY InputBChanged)
    Q_PROPERTY(int NumberSystem READ NumberSystem WRITE setNumberSystem NOTIFY NumberSystemChanged)
    Q_PROPERTY(QList<QObject*> OperationSteps READ OperationSteps NOTIFY OperationStepsChanged)

    Q_PROPERTY(QStringList Operand1 READ Operand1 NOTIFY Operand1Changed)
    Q_PROPERTY(int FOperand1 READ FOperand1 NOTIFY FOperand1Changed)

    Q_PROPERTY(QStringList Operand2 READ Operand2 NOTIFY Operand2Changed)
    Q_PROPERTY(int FOperand2 READ FOperand2 NOTIFY FOperand2Changed)

    Q_PROPERTY(int Operation READ Operation)
    Q_PROPERTY(QString OperationText READ OperationText NOTIFY OperationTextChanged)

public:
    explicit NonRestoringDivision(QObject *parent = nullptr);

    QString InputA() const{ return inputA;}
    void setInputA(const QString &InputA);

    QString InputB() const{ return inputB;}
    void setInputB(const QString &InputA);

    int NumberSystem() const{ return numberSystem;}
    void setNumberSystem(const int &NumberSystem);

    QList<QObject*> OperationSteps() const{ return operationSteps;}

    QStringList Operand1() {return makeString(outputCBin);}
    int FOperand1() const{ return fOperand1;}

    QStringList Operand2() {return makeString(inputABin);}
    int FOperand2() const{ return fOperand2;}

    int Operation() const{ return operation;}
    QString OperationText() const{ return operationText;}

signals:
    void InputAChanged();
    void InputBChanged();
    void NumberSystemChanged();
    void OperationStepsChanged();

    void Operand1Changed();
    void FOperand1Changed();
    void FOperand2Changed();
    void Operand2Changed();
    void operationChanged();
    void OperationTextChanged();

    void triggerThread();

public slots:
    void calculate();
    void receiveUpdate(QList<int>, QList<int>, QString, int op, bool dash, bool newStep);
    void letFurtherUpdateHappen();

private:
    QList<int> makeBin(QString bin); //convert binary string input into binary list
    QList<int> decToBin(int dec, int bits = 0); //convert decimal string input into binary list
    int binToDec(QList<int> bin);
    QList<int> initBin(QList<int> input, int bit); //initialize a binary number 000... with 'bit' number of bits
    QString binToStr(QList<int> binList, bool dash = false); //convert binary list to string for displaying

    QStringList makeString(QList<int>); //output for animation


    QString inputA;
    QString inputB;
    int numberSystem;
    QList<int> inputABin;
    int fOperand1;
    int fOperand2;
    QList<int> inputBBin;
    QString inputBStr;
    QList<int> outputCBin;
    int operation;
    QString operationText;
    QList<QObject*> operationSteps;
    QThread workerThread;
};

#endif // NONRESTORINGDIVISION_H
