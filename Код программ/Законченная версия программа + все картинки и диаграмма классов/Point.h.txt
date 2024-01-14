//212-Соболев-Никита

#ifndef __POINT_H__
#define __POINT_H__

class Point 
{
private:
    double x_cord;
    double y_cord;
    double z_cord;
public:
    Point() = default;
    Point (double x, double y);
    Point(double x, double y , double z);
    //bool operator== (const Point &lhs, const Point &rhs);


    void set_x(double a);
    double get_x() const;

    void set_y(double a);
    double get_y() const;

    void set_z(double a);
    double get_z() const;
};

#endif
