#ifndef OUTPUTTEMPLATE_H
#define OUTPUTTEMPLATE_H

#include <QObject>
#include "intdata.h"


class OutputTemplate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString InputA READ InputA NOTIFY InputAChanged)
    Q_PROPERTY(QString InputB READ InputB NOTIFY InputBChanged)
    Q_PROPERTY(QString OutputC READ OutputC NOTIFY OutputCChanged)
    Q_PROPERTY(QString Comment READ Comment NOTIFY CommentChanged)
    Q_PROPERTY(bool IsStepDivision READ IsStepDivision NOTIFY IsStepDivisionChanged)

public:
    explicit OutputTemplate(QObject *parent = nullptr)
        :QObject (parent){}
    OutputTemplate(QString InputA, QString InputB, QString OutputC, QString Comment, bool IsStepDivision = false, QObject *parent = nullptr)
        :QObject (parent), inputA(InputA), inputB(InputB), outputC(OutputC), comment(Comment), isStepDivision(IsStepDivision)
    {}

    QString InputA() const{ return inputA;}
    QString InputB() const{ return inputB;}
    QString OutputC() const{ return outputC;}
    bool IsStepDivision() const{ return isStepDivision;}
    QString Comment() const{ return comment;}
signals:
    void InputAChanged();
    void InputBChanged();
    void OutputCChanged();
    void CommentChanged();
    void IsStepDivisionChanged();

private:
    QString inputA, inputB, outputC;
    QString comment;
    bool isStepDivision;
};

#endif // OUTPUTTEMPLATE_H


