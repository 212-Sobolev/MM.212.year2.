//212-Соболев-Никита

#include "Landscape.h"
#include "Hill.h"
#include "Stoun.h"
#include "my_ran.h"
#include "Log.h"
#include <vector>
#include <math.h>
#include <iostream>
#include <fstream>
#include "Point.h"


std::vector<Point> Landscape::get_rover_pixels() const {return rover_pixels;}
void Landscape::set_rover_pixels(Point a, int i) {rover_pixels[i] = a;}

std::vector<Point> Landscape::get_fixing_points() const {return fixing_points;}
void Landscape::set_fixing_points(std::vector<Point> a) {fixing_points = a;}

void Landscape::set_sizex(double a) {size_x = a;}
double Landscape::get_sizex() const {return size_x;}

void Landscape::set_sizey(double a) {size_y = a;}
double Landscape::get_sizey() const {return size_y;}

std::vector<Hill> Landscape::get_contain_hill() const {return hills;}
std::vector<Stoun> Landscape::get_contain_stoun() const {return stouns;}
std::vector<Log> Landscape::get_contain_log() const {return logs;}

Landscape::Landscape(double x, double y)
{
    if (x<0 || y < 0) throw 1;
    set_sizex(x); set_sizey(y);
    int i = 0;
    Point a(-1, -1, -1);
    while(i<9)
    {
        rover_pixels.push_back(a);
        i++;
    }
}

Landscape::Landscape() 
{
    int i=0;
    Point a(-1, -1, -1);
    while(i<9)
    {
        rover_pixels.push_back(a);
        i++;
    }
}

void Landscape::create(int h, int s, int l)
{
    double x, y, dispx, dispy, hight, R, x2, y2;
    int i;
    for(i = 0; i < h; i++)
    {
        x = ran() * get_sizex();
        y = ran() * get_sizey();
        dispx = ran() + 1.5;
        dispy = ran() + 1;
        hight = ran()*30 - 15 ;
        hills.push_back(Hill(x, y, dispx, dispy, hight));
    }

    for(i = 0; i < s; i++)
    {
        x = ran() * get_sizex();
        y = ran() * get_sizey();
        R = ran() + 0.5;
        stouns.push_back(Stoun(x, y, R));
    }

    for(i = 0; i < l; i++)
    {
        x = ran() * get_sizex();
        y = ran() * get_sizey();
        x2 = ran() * get_sizex();
        y2 = ran() * get_sizey();
        R = ran() - 0.2;
        logs.push_back(Log(x, y, x2, y2, R));
    }
}


void Landscape::draw()
{
    double z;
    std::ofstream fout("out.txt");
    for(double i = 0; i <= size_x; i += size_x/200)
    {
        for(double j = 0; j < size_y; j += size_y/200)
        {
            z=0;
            for(std::vector<Hill>::size_type k=0; k < hills.size(); k++)
            {
                z+=hills[k].Gauss(i, j);
            }
            for(std::vector<Stoun>::size_type k=0; k < stouns.size(); k++)
            {
                z+=stouns[k].sphere(i, j);
            }
            for(std::vector<Log>::size_type k=0; k < logs.size(); k++)
            {
                z+=logs[k].cylinder(i, j);
            }
            fout << i << " " << j << " " << z << std::endl;
            pixels.push_back(Point(i,j,z));
        }
        fout << std::endl;
    }
}

double Landscape::get_landscape_hight(double x, double y)
{
    double hight = 0;
    for(std::vector<Hill>::size_type k=0; k < hills.size(); k++)
            {
                hight+=hills[k].Gauss(x, y);
            }
            for(std::vector<Stoun>::size_type k=0; k < stouns.size(); k++)
            {
                hight+=stouns[k].sphere(x, y);
            }
            for(std::vector<Log>::size_type k=0; k < logs.size(); k++)
            {
                hight+=logs[k].cylinder(x, y);
            }

    return hight;
}


