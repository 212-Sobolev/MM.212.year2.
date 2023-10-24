#pragma once
#include <vector>
#include "Hill.h"
#include "Stoun.h"
#include "Log.h"

class Landscape
{
private:
    double size_x; //размеры поверхности
    double size_y;
    std::vector<Hill> hills; 
    std::vector<Stoun> stouns;
    std::vector<Log> logs;
    int count_hills;
    int count_stouns;
    int count_logs;
public:


    Landscape() = default;
    Landscape(double x, double y);

    void set_sizex(double a);
    double get_sizex() const;

    void set_sizey(double a);
    double get_sizey() const;

    void set_contain_hill(std::vector<Hill> a) {hills = a;}
    std::vector<Hill> get_contain_hill() const;


    void create(int h, int s, int l);
    void draw();



};