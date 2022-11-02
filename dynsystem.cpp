#include "dynsystem.h"
#include <QtMath>
#include <queue>

DynSystem:: DynSystem(double beta, double gamma, double n, double tau, double x0,  double t, double dt):
    beta_(beta), gamma_(gamma),n_(n), tau_(tau), x1_(x0), x2_(x0), t_(t), dt_(dt)
{

}

void DynSystem::step (double x2)
{
    t_ += dt_;


    x1_ += (beta_*(x2)/(1+ qPow(x2,n_))-gamma_*x1_)*dt_;


}
