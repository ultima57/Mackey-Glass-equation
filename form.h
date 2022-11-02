#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QTextEdit>

#include <QTimer>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>

#include "dynsystem.h"

class Form : public QWidget
{
    Q_OBJECT

public:
    Form(QWidget *parent = nullptr);
    ~Form();
    double j;
    int l;

public slots:
    void startCalculation();
    void stopCalculation();
    void makeStep();

private:
    QLabel *labelBeta;
    QLabel *labelGamma;
    QLabel *labelN;
    QLabel *labelTau;
    QLabel *labelInitX;
    QLabel *labelDt;
    QDoubleSpinBox *doubleSpinBoxBeta;
    QDoubleSpinBox *doubleSpinBoxGamma;
    QDoubleSpinBox *doubleSpinBoxN;    
    QDoubleSpinBox *doubleSpinBoxTau;
    QDoubleSpinBox *doubleSpinBoxInitX;
    QDoubleSpinBox *doubleSpinBoxDt;
    QPushButton *pushButtonStart;
    QPushButton *pushButtonStop;
    QTextEdit *textEditLog;

    QwtPlot *plotTime;


    QTimer * timer;

    QwtPlotCurve *curveTimeCoordinate;

    DynSystem *system;

    QVector<double> dataT;
    QVector<double> dataX;

};
#endif // FORM_H
