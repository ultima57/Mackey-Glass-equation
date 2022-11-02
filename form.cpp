#include "form.h"

#include <QLayout>

#include <qwt_plot_legenditem.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>

Form::Form(QWidget *parent)
    : QWidget(parent), system(nullptr)
{
    timer = new QTimer(this);
    timer->setInterval(0);

    curveTimeCoordinate = new QwtPlotCurve("coordinate");
    curveTimeCoordinate->setPen(Qt::red, 3.0);


    labelBeta = new QLabel("beta");
    labelGamma = new QLabel("gamma");
    labelN = new QLabel("n");    
    labelTau = new QLabel("tau");
    labelInitX = new QLabel("initial coordinate");
    labelDt = new QLabel("time step");

    doubleSpinBoxBeta = new QDoubleSpinBox;
    doubleSpinBoxBeta->setMinimum(-1.0);
    doubleSpinBoxBeta->setMaximum(100.0);
    doubleSpinBoxBeta->setSingleStep(1.0);
    doubleSpinBoxBeta->setDecimals(2);
    doubleSpinBoxGamma = new QDoubleSpinBox;
    doubleSpinBoxGamma->setMinimum(-100.0);
    doubleSpinBoxGamma->setMaximum(100.0);
    doubleSpinBoxGamma->setSingleStep(1.0);
    doubleSpinBoxGamma->setDecimals(2);
    doubleSpinBoxN = new QDoubleSpinBox;
    doubleSpinBoxN->setMinimum(-1.0);
    doubleSpinBoxN->setMaximum(100.0);
    doubleSpinBoxN->setSingleStep(1.0);
    doubleSpinBoxN->setDecimals(2);
    doubleSpinBoxTau = new QDoubleSpinBox;
    doubleSpinBoxTau->setMinimum(-100.0);
    doubleSpinBoxTau->setMaximum(100.0);
    doubleSpinBoxTau->setSingleStep(1.0);
    doubleSpinBoxTau->setDecimals(2);
    doubleSpinBoxInitX = new QDoubleSpinBox;
    doubleSpinBoxInitX->setMinimum(-100.0);
    doubleSpinBoxInitX->setMaximum(100.0);
    doubleSpinBoxInitX->setSingleStep(1.0);
    doubleSpinBoxInitX->setDecimals(2);
    doubleSpinBoxDt = new QDoubleSpinBox;
    doubleSpinBoxDt->setMinimum(1e-6);
    doubleSpinBoxDt->setMaximum(1.0);
    doubleSpinBoxDt->setSingleStep(0.001);
    doubleSpinBoxDt->setDecimals(6);
    doubleSpinBoxDt->setValue(0.001);

    doubleSpinBoxInitX->setValue(1.0);
    doubleSpinBoxN->setValue(1.0);
    doubleSpinBoxGamma->setValue(1.0);
    doubleSpinBoxBeta->setValue(1.0);
    pushButtonStart = new QPushButton("Start");
    pushButtonStop = new QPushButton("Stop");

    textEditLog = new QTextEdit;
    textEditLog->setReadOnly(true);

    plotTime = new QwtPlot(QString("Time plots"));

    plotTime->setAxisTitle(QwtPlot::yLeft, "Coordinate");
    plotTime->setAxisTitle(QwtPlot::xBottom, "Time");




    curveTimeCoordinate->attach(plotTime);
    curveTimeCoordinate->setAxes(QwtPlot::xBottom, QwtPlot::yLeft);


    QwtPlotLegendItem *legendTime = new QwtPlotLegendItem;
    legendTime->attach(plotTime);
    legendTime->setAlignment(Qt::AlignRight);
    legendTime->setMaxColumns(1);





    QGridLayout *layoutParameters = new QGridLayout;
    layoutParameters->addWidget(labelBeta, 0, 0);
    layoutParameters->addWidget(doubleSpinBoxBeta, 0, 1);
    layoutParameters->addWidget(labelGamma, 1, 0);
    layoutParameters->addWidget(doubleSpinBoxGamma, 1, 1);
    layoutParameters->addWidget(labelN, 2, 0);
    layoutParameters->addWidget(doubleSpinBoxN, 2, 1);
    layoutParameters->addWidget(labelTau, 1, 2);
    layoutParameters->addWidget(doubleSpinBoxTau, 1, 3);

    layoutParameters->addWidget(labelInitX, 0, 2);

    layoutParameters->addWidget(labelDt, 2, 2);
    layoutParameters->addWidget(doubleSpinBoxInitX, 0, 3);

    layoutParameters->addWidget(doubleSpinBoxDt, 2, 3);

    QHBoxLayout *layoutButtons = new QHBoxLayout;
    layoutButtons->addWidget(pushButtonStart);
    layoutButtons->addWidget(pushButtonStop);

    QVBoxLayout *layoutLeft = new QVBoxLayout;
    layoutLeft->addLayout(layoutParameters);
    layoutLeft->addLayout(layoutButtons);
    layoutLeft->addWidget(textEditLog);

    QVBoxLayout *layoutPlots = new QVBoxLayout;
    layoutPlots->addWidget(plotTime);


    QHBoxLayout *layoutMain = new QHBoxLayout;
    layoutMain->addLayout(layoutLeft);
    layoutMain->addLayout(layoutPlots);

    this->setLayout(layoutMain);


    connect(pushButtonStart, &QPushButton::clicked, this, &Form::startCalculation);
    connect(pushButtonStop, &QPushButton::clicked, this, &Form::stopCalculation);
    connect(timer, &QTimer::timeout, this, &Form::makeStep);
}

Form::~Form()
{
    delete system;
}

void Form::startCalculation()
{
    textEditLog->clear();
    dataT.clear();
    dataX.clear();

    delete system;


    system = new DynSystem(doubleSpinBoxBeta->value(),
                           doubleSpinBoxGamma->value(),
                           doubleSpinBoxN->value(),
                           doubleSpinBoxTau->value(),
                           doubleSpinBoxInitX->value(),                    
                           0.0,
                           doubleSpinBoxDt->value()
                           );
    j=-doubleSpinBoxTau->value();
    l = doubleSpinBoxTau->value()/doubleSpinBoxDt->value();
    dataT.append(j);
    dataX.append( doubleSpinBoxInitX->value());

    textEditLog->append("system created");
    textEditLog->append("parameters:");

    textEditLog->append(QString("%1\t%2")
                        .arg(system->t())
                        .arg(system->x1()));


    curveTimeCoordinate->setSamples(dataT, dataX);

    plotTime->replot();

    timer->start();
}

void Form::stopCalculation()
{
    timer->stop();
}

void Form::makeStep()
{


    if(j<0){

           dataT.append(j);
           dataX.append( doubleSpinBoxInitX->value());

           textEditLog->append(QString("%1\t%2")
                               .arg(j)
                               .arg(system->x1()));
            j+=doubleSpinBoxDt->value();

        }
    else{

    for (int i = 0; i < 10; ++i)

        system->step(dataX[dataT.size()-l-1]);

    textEditLog->append(QString("%1\t%2")
                        .arg(system->t())
                        .arg(system->x1()));

    dataT.append(system->t());
    dataX.append(system->x1());
    }

    curveTimeCoordinate->setSamples(dataT, dataX);

    plotTime->replot();

}

