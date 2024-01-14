//212-Соболев-Никита

#ifndef __LOG_H__
#define __LOG_H__

class Log
{
private:
    double x1;
    double y1;
    double x2;
    double y2;
    double r; 
public:
    Log(double x01, double y01, double x02, double y02, double r0);

    void set_x1(double a);
    double get_x1() const;

    void set_y1(double a);
    double get_y1() const;

    void set_x2(double a);
    double get_x2() const;

    void set_y2(double a);
    double get_y2() const;

    void set_r(double a);
    double get_r() const;

    double cylinder(double x0, double y0);
};

#endif
