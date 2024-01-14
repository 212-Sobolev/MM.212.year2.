//212-Соболев-Никита

#include "Point.h"
#include "config.h"

void Point::set_x(double a) {x_cord = a;}
double Point::get_x() const {return x_cord;}

void Point::set_y(double a) {y_cord = a;}
double Point::get_y() const {return y_cord;}

void Point::set_z(double a) {z_cord = a;}
double Point::get_z() const {return z_cord;}


Point::Point (double x, double y, double z)
{
    set_x(x); set_y(y); set_z(z);
}

Point::Point (double x, double y)
{
    set_x(x); set_y(y);
}

/*bool operator== (const Point &lhs, const Point &rhs)
{
    if(abs(lhs.get_x() - rhs.get_x()) < EPS and abs(lhs.get_y() - rhs.get_y()) < EPS 
       and abs(lhs.get_z() - rhs.get_z()) < EPS) { return true;}
    else {return false;}
} */