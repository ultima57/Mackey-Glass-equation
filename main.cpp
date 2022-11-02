#include "form.h"
#include "dynsystem.h"

#include <cmath>

#include <QDebug>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Form w;
    w.show();
    return a.exec();
/*
    DynSystem sys(1.0, 0.0, 10.0, 1.0, 0.0, 0.0, 1.0e-3 * 2.0*M_PI*std::sqrt(1.0/10.0));
    qDebug() << sys.t() << sys.x() << sys.v();
    for (int n = 0; n < 500; ++n) sys.step();
    qDebug() << sys.t() << sys.x() << sys.v();*/
}
