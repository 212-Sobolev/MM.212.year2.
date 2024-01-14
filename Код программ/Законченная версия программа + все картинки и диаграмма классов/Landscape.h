//212-Соболев-Никита

#ifndef __LANDSCAPE_H__
#define __LANDSCAPE_H__

#include <vector>
#include "Hill.h"
#include "Stoun.h"
#include "Log.h"
#include "Point.h"

class Landscape
{
private:
    double size_x; //размеры поверхности
    double size_y;
    std::vector<Hill> hills; 
    std::vector<Stoun> stouns;
    std::vector<Log> logs;
    std::vector<Point> pixels;
    int count_hills;
    int count_stouns;
    int count_logs;

    std::vector<Point> rover_pixels;
    std::vector<Point> fixing_points;
public:


    Landscape();
    Landscape(double x, double y);

    void set_sizex(double a);
    double get_sizex() const;

    void set_sizey(double a);
    double get_sizey() const;

    void set_rover_pixels(Point a, int i);
    std::vector<Point> get_rover_pixels() const;

    void set_fixing_points(std::vector<Point> a);
    std::vector<Point> get_fixing_points() const;

    void set_contain_hill(std::vector<Hill> a) {hills = a;}
    std::vector<Hill> get_contain_hill() const;

    void set_contain_stoun(std::vector<Stoun> a) {stouns = a;}
    std::vector<Stoun> get_contain_stoun() const;
    
    void set_contain_log(std::vector<Log> a) {logs = a;}
    std::vector<Log> get_contain_log() const;

    double get_landscape_hight(double x, double y);
    void create(int h, int s, int l);
    void draw();
    



};

#endif
