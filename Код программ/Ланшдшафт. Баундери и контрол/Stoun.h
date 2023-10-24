#ifndef __STOUN_H__
#define __STOUN_H__


class Stoun
{
private:
    double x;
    double y;
    double r;
public:
    Stoun(double x0, double y0, double r0);

    void set_x(double a);
    double get_x() const;

    void set_y(double a);
    double get_y() const;

    void set_r(double a);
    double get_r() const;

    double sphere(double x0, double y0);

};

#endif
