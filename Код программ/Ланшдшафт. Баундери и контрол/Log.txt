#include "Log.h"
#include <math.h>

void Log::set_x1(double a) {x1=a;}
double Log::get_x1() const {return x1;}

void Log::set_y1(double a) {y1=a;}
double Log::get_y1() const {return y1;}

void Log::set_x2(double a) {x2=a;}
double Log::get_x2() const {return x2;}

void Log::set_y2(double a) {y2=a;}
double Log::get_y2() const {return y2;}

void Log::set_r(double a) {r=a;}
double Log::get_r() const {return r;}

Log::Log(double x01, double y01, double x02, double y02, double r0)
{
    set_x1(x01); set_y1(y01); set_x2(x02); set_y2(y02); set_r(r0);
}

double Log::cylinder(double x0, double y0)
{
    double A = y2-y1;
    double B = x2-x1;
    double D = A * A + B * B;
    double C1 = (-y1 * B - x1 * A);
    double C2 = B * (x1+x2) / 2 - A * (y1+y2) / 2;
    double d1 = abs(A * x0 + B * y0 + C1) / sqrt(D);
    double d2 = abs(-B * x0 + A * y0 + C2) / sqrt(D);
    if(r * r > d1 * d1 && D/4 > d2 * d2)
    {
        return sqrt(r * r - d1 *d1);
    }
    return 0;
}