#ifndef __HILL_H__
#define __HILL_H__

class Hill
{
private:
    double x; //координаты 
    double y;
    double dispx;
    double dispy;
    double dispxy;
    double hight; //высота холма
public:
    Hill(double x0, double y0, double dispx0, double dispy0, double hight0);

    //Гауссово распределение в точке, относительно холмика
    double Gauss(double x0, double y0);

    void set_x(double a);
    double get_x() const;

    void set_y(double a);
    double get_y() const;

    void set_dispx(double a);
    double get_dispx() const;

    void set_dispy(double a);
    double get_dispy() const; 

    void set_dispxy(double a); 
    double get_dispxy() const;

    void set_hight(double a);
    double get_hight() const; 
    
};

#endif
