//212-Соболев-Никита

#include "Stoun.h"
#include <math.h>


void Stoun::set_x(double a) {x=a;}
double Stoun::get_x() const {return x;}

void Stoun::set_y(double a) {y=a;}
double Stoun::get_y() const {return y;}

void Stoun::set_r(double a) {r=a;}
double Stoun::get_r() const {return r;}

Stoun::Stoun(double x0, double y0, double r0)
{
    set_x(x0); set_y(y0); set_r(r0);
}

double Stoun::sphere(double x0, double y0)
{
    if (r*r - (x-x0)*(x-x0) - (y-y0)*(y-y0) > 0)
    {
        return sqrt(r*r - (x-x0)*(x-x0) - (y-y0)*(y-y0));
    }
    return 0;
}

