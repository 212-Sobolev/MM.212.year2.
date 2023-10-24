#include "Hill.h"
#include "my_ran.h"
#include <math.h>
#include <random>


void Hill::set_x(double a) {x=a;}
double Hill::get_x() const {return x;}

void Hill::set_y(double a) {y=a;}
double Hill::get_y() const {return y;}

void Hill::set_dispx(double a) {dispx=a;}
double Hill::get_dispx() const {return dispx;}

void Hill::set_dispy(double a) {dispy=a;}
double Hill::get_dispy() const {return dispy;}

void Hill::set_dispxy(double a) {dispxy=a;}
double Hill::get_dispxy() const {return dispxy;}

void Hill::set_hight(double a) {hight=a;}
double Hill::get_hight() const {return hight;}

Hill::Hill(double x0, double y0, double dispx0, double dispy0, double hight0)
{
    set_x(x0); set_y(y0); set_dispx(dispx0); set_dispy(dispy0);
    
    double a = ran() * get_dispx() * get_dispy();
    set_dispxy(a); set_hight(hight0);
}

double Hill::Gauss(double x0, double y0)
{
    double r = dispxy / (dispx * dispy);
    return hight * exp(-((x-x0)*(x-x0)/(dispx * dispx)
            - 2 * r * (x-x0)*(y-y0)/(dispx * dispy)
             + (y-y0)*(y-y0)/(dispy * dispy))/(2 * (1-r*r)))/(2 * dispx * dispy * sqrt(1-r*r));
}