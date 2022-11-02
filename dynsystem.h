#ifndef DYNSYSTEM_H
#define DYNSYSTEM_H


class DynSystem
{
public:
    DynSystem(double beta, double gamma, double n, double tau, double x1, double t, double dt);

    double beta() const {return beta_;}
    double gamma() const {return gamma_;}
    double n() const {return n_;}
    double tau() const {return tau_;}
    double x1() const {return x1_;}
    double x2() const {return x2_;}
    double v() const {return v_;}
    double t() const {return t_;}
    double dt() const {return dt_;}
    double l() const {return l_;}
    void step( double x2);

private:
    int l_;
    double beta_;
    double gamma_;
    double n_;
    double tau_;
    double x1_;
    double x2_;
    double v_;
    double t_;
    double dt_;
};

#endif // DYNSYSTEM_H
