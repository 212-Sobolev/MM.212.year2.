//212-Соболев-Никита

#ifndef __ROVER_H__
#define __ROVER_H__

#include "Point.h" 
#include "Landscape.h"
#include <string>


class Rover
{
private:
    double rover_clearance;           // клиренс ровера (зазор)
    double tilt_angle_side;           // угол наклона в бок
    double tilt_angle_forback;        // угол наклона вперед/назад
    std::string rover_direction;      // направление движения (NN, NE, EE, ES, SS....)
    Landscape *landscape;             // поверхность
    //double rover_speed;             // скорость ровера
    int rollover_error_code;          // пупупу, пока думаю над ним

    std::vector<Point> first_series;  //след. три вектора - так называемый угол обзора сенсора
    std::vector<Point> second_series;
    std::vector<Point> third_series;

    int has_obstacle;


public: 
    Rover(Landscape *land);

    void Rover_first_position(double a, double b);

    double get_tilt_angle_forback() const;
    double get_tilt_angle_side() const;
    std::string get_direction() const;


    //void set_clearance(double a);

    void change_direction(std::string dir);


    void Rover_make_move_tact(std::string rover_direct);
    int Rover_make_move(std::string rover_direct);

    void calculate_tilts();
    bool check_tilts();

    void turn_the_rover(std::string rover_direct);

    void scan_terr();
    void check_obstacle();

    //cеттеры и геттеры

    void set_roll_code(int a);
    int get_roll_code() const;


};

#endif