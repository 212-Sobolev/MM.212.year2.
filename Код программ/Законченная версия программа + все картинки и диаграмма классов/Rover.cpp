//212-Соболев-Никита

#include "Rover.h"
#include "Point.h"
#include "Landscape.h"
#include "config.h"
#include "my_ran.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

void Rover::change_direction(std::string dir) {rover_direction = dir;}

void Rover::set_roll_code(int a) {rollover_error_code = a;}
int Rover::get_roll_code() const {return rollover_error_code;}

//void Rover::set_clearance(double a) {rover_clearance = a;}

double Rover::get_tilt_angle_forback() const {return tilt_angle_forback;}
double Rover::get_tilt_angle_side() const {return tilt_angle_side;}
std::string Rover::get_direction() const {return rover_direction;}



void Rover::Rover_first_position(double a, double b)
{
    Point temp = landscape->get_rover_pixels()[0];

    temp.set_x(a);
    temp.set_y(b);
    temp.set_z(landscape->get_landscape_hight(a , b));

    landscape->set_rover_pixels(temp, 0);

    turn_the_rover("NN");
    change_direction("NN");
    scan_terr();
    check_obstacle();

    
    /*std::cout <<"cord center in beggining "<< (landscape->get_rover_pixels())[0].get_x() << " "
              << (landscape->get_rover_pixels())[0].get_y() << " " 
              << (landscape->get_rover_pixels())[0].get_z() << std::endl; */

    calculate_tilts();
    if (check_tilts() == 0)
    {
        std::cout << "The rover overturned" << std::endl;
        std::cout << tilt_angle_forback << " " << tilt_angle_side << std::endl;
        //rollover_error_code = 1; 

    } else {
        //std::cout << tilt_angle_forback << " " << tilt_angle_side << std::endl;
    }

}



Rover::Rover(Landscape *land)
{
    landscape = land;
    rover_clearance = ROVER_CLEARENCE;

    Point a(-1, -1, -1);
    int i = 0;
    int k = 0;
    int j = 0;
    while(i < 5) {first_series.push_back(a); i++;}
    while(k < 7) {second_series.push_back(a); k++;}
    while(j < 9) {third_series.push_back(a); j++;}
}

void Rover::Rover_make_move_tact(std::string rover_direct)
{
    if(rover_direct == "NN") {

        Point temp = (landscape->get_rover_pixels())[0];  
        temp.set_y((landscape->get_rover_pixels())[0].get_y() + landscape->get_sizey()/200);
        temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y() + rover_clearance));
        landscape->set_rover_pixels(temp, 0);

        //std::cout << temp.get_x() << " " << temp.get_y() << " " << temp.get_z() << std::endl;

    } else if (rover_direct == "NE") {

        Point temp = (landscape->get_rover_pixels())[0];
        temp.set_x((landscape->get_rover_pixels())[0].get_x() + landscape->get_sizex()/200);
        temp.set_y((landscape->get_rover_pixels())[0].get_y() + landscape->get_sizey()/200);
        temp.set_z(landscape->get_landscape_hight(temp.get_x() , temp.get_y()) + rover_clearance);
        landscape->set_rover_pixels(temp, 0);

    } else if (rover_direct == "EE") {

        Point temp = (landscape->get_rover_pixels())[0];
        temp.set_x((landscape->get_rover_pixels())[0].get_x() + landscape->get_sizex()/200);
        temp.set_z(landscape->get_landscape_hight(temp.get_x() , temp.get_y()) + rover_clearance);
        landscape->set_rover_pixels(temp, 0);

        //std::cout << temp.get_x() << " " << temp.get_y() << " " << temp.get_z() << std::endl;

    } else if (rover_direct == "SE") {

        Point temp = (landscape->get_rover_pixels())[0];
        temp.set_x((landscape->get_rover_pixels())[0].get_x() + landscape->get_sizex()/200);
        temp.set_y((landscape->get_rover_pixels())[0].get_y() - landscape->get_sizey()/200);
        temp.set_z(landscape->get_landscape_hight(temp.get_x() , temp.get_y()) + rover_clearance);
        landscape->set_rover_pixels(temp, 0);

    } else if (rover_direct == "SS") {

        Point temp = (landscape->get_rover_pixels())[0];
        temp.set_y((landscape->get_rover_pixels())[0].get_y() - landscape->get_sizey()/200);
        temp.set_z(landscape->get_landscape_hight(temp.get_x() , temp.get_y()) + rover_clearance);
        landscape->set_rover_pixels(temp, 0);

    } else if (rover_direct == "SW") {

        Point temp = (landscape->get_rover_pixels())[0];
        temp.set_x((landscape->get_rover_pixels())[0].get_x() - landscape->get_sizex()/200);
        temp.set_y((landscape->get_rover_pixels())[0].get_y() - landscape->get_sizey()/200);
        temp.set_z(landscape->get_landscape_hight(temp.get_x() , temp.get_y()) + rover_clearance);
        landscape->set_rover_pixels(temp, 0);

    } else if (rover_direct == "WW") {

        Point temp = (landscape->get_rover_pixels())[0];
        temp.set_x((landscape->get_rover_pixels())[0].get_x() - landscape->get_sizex()/200);
        temp.set_z(landscape->get_landscape_hight(temp.get_x() , temp.get_y()) + rover_clearance);
        landscape->set_rover_pixels(temp, 0);

    } else if (rover_direct == "NW") {

        Point temp = (landscape->get_rover_pixels())[0];
        temp.set_x((landscape->get_rover_pixels())[0].get_x() - landscape->get_sizex()/200);
        temp.set_y((landscape->get_rover_pixels())[0].get_y() + landscape->get_sizey()/200);
        temp.set_z(landscape->get_landscape_hight(temp.get_x() , temp.get_y()) + rover_clearance);
        landscape->set_rover_pixels(temp, 0);

    } else {
        std::cout << "Unknow direction for rover" <<std::endl;
    }

    if(rover_direction != rover_direct) {change_direction(rover_direct);}

    calculate_tilts();
    if (check_tilts() == 0){
        //std::cout << "The rover overturned" << std::endl;
        //std::cout << "---------------" << tilt_angle_forback << " " << tilt_angle_side << std::endl;
        //rollover_error_code = 1;
    } else {
        //std::cout << tilt_angle_forback << " " << tilt_angle_side << std::endl;
    }

    scan_terr();
    check_obstacle();

}

int Rover::Rover_make_move(std::string rover_direct)
{
    turn_the_rover(rover_direct);
    for(int i = 0; i < 4; i++)
    {
        Rover_make_move_tact(rover_direct);
        //if(rollover_error_code == 1) {std::cout << "The rover overturned" << std::endl;}
        //if (has_obstacle == 1) {return 0;}
    }
    if (check_tilts() == 0) {rollover_error_code = 1;}
    //if(rollover_error_code == 1) {std::cout << "The rover overturned" << std::endl;}

    //std::cout << rover_direction << std::endl;
    calculate_tilts();

    std::vector<Point> temp = landscape->get_fixing_points();
    temp.push_back((landscape->get_rover_pixels())[0]);
    landscape->set_fixing_points(temp);

    return 1;
}


void Rover::calculate_tilts()
{
    turn_the_rover(rover_direction);
    

    double a1 = (landscape->get_rover_pixels())[1].get_z();
    double b1 = (landscape->get_rover_pixels())[5].get_z();

    double dz1 = abs(a1-b1);
    double dy = landscape->get_sizey()/100;

    //std::cout << "dif of z1: " << dz1 << " dif of y: " << dy << std::endl;

    tilt_angle_forback = atan(dz1/dy) * 180 / M_PI;

    double a2 = (landscape->get_rover_pixels())[3].get_z();
    double b2 = (landscape->get_rover_pixels())[7].get_z();

    double dz2 = abs(a2-b2);
    double dx = landscape->get_sizex() / 100;

    //std::cout << "dif of z2: " << dz2 << " dif of x: " << dx << std::endl;


    tilt_angle_side = atan(dz2/dx) * 180 / M_PI;

}

bool Rover::check_tilts()
{
    if(tilt_angle_forback < MAX_TILT_ANGLE_FORBACK && tilt_angle_side < MAX_TILT_ANGLE_SIDE)
    {
        return true;
    } else {
        return false;
    }
}


void Rover::turn_the_rover(std::string rover_direct)
{
   /* if(rover_direction == rover_direct)
    {
        return;
    } */
    Point temp1, temp3, temp5, temp7;

    if(rover_direct == "NN")
    {
        temp1.set_x((landscape->get_rover_pixels())[0].get_x());
        temp1.set_y((landscape->get_rover_pixels())[0].get_y() + landscape->get_sizey()/200);
        temp1.set_z(landscape->get_landscape_hight(temp1.get_x(), 
                                temp1.get_y()) + rover_clearance);
        
        landscape->set_rover_pixels(temp1, 1);

        temp3.set_x((landscape->get_rover_pixels())[0].get_x() + landscape->get_sizex()/200);
        temp3.set_y((landscape->get_rover_pixels())[0].get_y());
        temp3.set_z(landscape->get_landscape_hight(temp3.get_x(), 
                                temp3.get_y()) + rover_clearance);

        landscape->set_rover_pixels(temp3, 3);

        temp5.set_x((landscape->get_rover_pixels())[0].get_x());
        temp5.set_y((landscape->get_rover_pixels())[0].get_y() - landscape->get_sizey()/200);
        temp5.set_z(landscape->get_landscape_hight(temp5.get_x(),
                                temp5.get_y()) + rover_clearance);

        landscape->set_rover_pixels(temp5, 5);

        temp7.set_x((landscape->get_rover_pixels())[0].get_x() - landscape->get_sizex()/200);
        temp7.set_y((landscape->get_rover_pixels())[0].get_y());
        temp7.set_z(landscape->get_landscape_hight(temp7.get_x(),
                                temp7.get_y()) + rover_clearance);

        landscape->set_rover_pixels(temp7, 7);
    
    } else if(rover_direct == "EE" || rover_direct == "SE"){

        temp1.set_x((landscape->get_rover_pixels())[0].get_x() + landscape->get_sizex()/200);
        temp1.set_y((landscape->get_rover_pixels())[0].get_y());
        temp1.set_z(landscape->get_landscape_hight(temp1.get_x(), 
                                temp1.get_y()) + rover_clearance);

        landscape->set_rover_pixels(temp1, 1);

        temp3.set_x((landscape->get_rover_pixels())[0].get_x());
        temp3.set_y((landscape->get_rover_pixels())[0].get_y() - landscape->get_sizey() / 200);
        temp3.set_z(landscape->get_landscape_hight(temp3.get_x(),
                                temp3.get_y()) + rover_clearance);

        landscape->set_rover_pixels(temp3, 3);
        
        temp5.set_x((landscape->get_rover_pixels())[0].get_x() - landscape->get_sizex() / 200);
        temp5.set_y((landscape->get_rover_pixels())[0].get_y());
        temp5.set_z(landscape->get_landscape_hight(temp5.get_x(),
                                temp5.get_y()) + rover_clearance);

        landscape->set_rover_pixels(temp5, 5);

        temp7.set_x((landscape->get_rover_pixels())[0].get_x());
        temp7.set_y((landscape->get_rover_pixels())[0].get_y() + landscape->get_sizey()/200);
        temp7.set_z(landscape->get_landscape_hight(temp7.get_x(), 
                               temp7.get_y()) + rover_clearance);

        landscape->set_rover_pixels(temp7, 7);

    } else if(rover_direct == "SS" || rover_direct == "SW"){

        temp1.set_x((landscape->get_rover_pixels())[0].get_x());
        temp1.set_y((landscape->get_rover_pixels())[0].get_y() - landscape->get_sizey() / 200);
        temp1.set_z(landscape->get_landscape_hight(temp1.get_x(),
                                temp1.get_y()) + rover_clearance);

        landscape->set_rover_pixels(temp1, 1);

        temp3.set_x((landscape->get_rover_pixels())[0].get_x() - landscape->get_sizex() / 200);
        temp3.set_y((landscape->get_rover_pixels())[0].get_y());
        temp3.set_z(landscape->get_landscape_hight(temp3.get_x(),
                                temp3.get_y()) + rover_clearance);

        landscape->set_rover_pixels(temp3, 3);

        temp5.set_x((landscape->get_rover_pixels())[0].get_x());
        temp5.set_y((landscape->get_rover_pixels())[0].get_y() + landscape->get_sizey()/200);
        temp5.set_z(landscape->get_landscape_hight(temp5.get_x(), 
                                temp5.get_y()) + rover_clearance);

        landscape->set_rover_pixels(temp5, 5);

        temp7.set_x((landscape->get_rover_pixels())[0].get_x() + landscape->get_sizex()/200);
        temp7.set_y((landscape->get_rover_pixels())[0].get_y());
        temp7.set_z(landscape->get_landscape_hight(temp7.get_x(), 
                                temp7.get_y()) + rover_clearance);

        landscape->set_rover_pixels(temp7, 7);

    } else if(rover_direct == "WW") {

        temp1.set_x((landscape->get_rover_pixels())[0].get_x() - landscape->get_sizex() / 200);
        temp1.set_y((landscape->get_rover_pixels())[0].get_y());
        temp1.set_z(landscape->get_landscape_hight(temp1.get_x(),
                                temp1.get_y()) + rover_clearance);

        landscape->set_rover_pixels(temp1, 1);

        temp3.set_x((landscape->get_rover_pixels())[0].get_x());
        temp3.set_y((landscape->get_rover_pixels())[0].get_y() + landscape->get_sizey()/200);
        temp3.set_z(landscape->get_landscape_hight(temp3.get_x(), 
                                temp3.get_y()) + rover_clearance);

        landscape->set_rover_pixels(temp3, 3);

        temp5.set_x((landscape->get_rover_pixels())[0].get_x() + landscape->get_sizex()/200);
        temp5.set_y((landscape->get_rover_pixels())[0].get_y());
        temp5.set_z(landscape->get_landscape_hight(temp5.get_x(), 
                                temp5.get_y()) + rover_clearance);

        landscape->set_rover_pixels(temp5, 5);

        temp7.set_x((landscape->get_rover_pixels())[0].get_x());
        temp7.set_y((landscape->get_rover_pixels())[0].get_y() - landscape->get_sizey() / 200);
        temp7.set_z(landscape->get_landscape_hight(temp7.get_x(),
                                temp7.get_y()) + rover_clearance);

        landscape->set_rover_pixels(temp7, 7);
    }


}



void Rover::scan_terr()
{
    if(rover_direction == "NN") {
        for(int i = 0; i < 5; i++){
            Point temp;
            temp.set_x((landscape->get_rover_pixels())[0].get_x() + (i - 2) * landscape->get_sizex()/200);
            temp.set_y((landscape->get_rover_pixels())[0].get_y() + 2 * landscape->get_sizey()/200);
            temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));

            first_series[i] = temp;
        }
        for(int l = 0; l < 7; l++){
            Point temp;
            temp.set_x((landscape->get_rover_pixels())[0].get_x() + (l - 3) * landscape->get_sizex()/200);
            temp.set_y((landscape->get_rover_pixels())[0].get_y() + 3 * landscape->get_sizey()/200);
            temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
            second_series[l] = temp;
        }
        for(int m = 0; m < 9; m++){
            Point temp;
            temp.set_x((landscape->get_rover_pixels())[0].get_x() + (m - 4) * landscape->get_sizex()/200);
            temp.set_y((landscape->get_rover_pixels())[0].get_y() + 4 * landscape->get_sizey()/200);
            temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
            third_series[m] = temp;
        }

    } else if(rover_direction == "SS"){
        for(int i = 0; i < 5; i++){
            Point temp;
            temp.set_x((landscape->get_rover_pixels())[0].get_x() + (2 - i) * landscape->get_sizex()/200);
            temp.set_y((landscape->get_rover_pixels())[0].get_y() - 2 * landscape->get_sizey()/200);
            temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
            first_series[i] = temp;
        }
        for(int k = 0; k < 7; k++){
            Point temp;
            temp.set_x((landscape->get_rover_pixels())[0].get_x() + (3 - k) * landscape->get_sizex()/200);
            temp.set_y((landscape->get_rover_pixels())[0].get_y() - 3 * landscape->get_sizey()/200);
            temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
            second_series[k] = temp;
        }
        for(int l = 0; l < 9; l++){
            Point temp;
            temp.set_x((landscape->get_rover_pixels())[0].get_x() + (4 - l) * landscape->get_sizex()/200);
            temp.set_y((landscape->get_rover_pixels())[0].get_y() - 4 * landscape->get_sizey()/200);
            temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
            third_series[l] = temp;
        }

    } else if(rover_direction == "EE"){
        for (int i = 0; i < 5; i++)
        {
            Point temp;
            temp.set_x((landscape->get_rover_pixels())[0].get_x() + 2 * landscape->get_sizex()/200);
            temp.set_y((landscape->get_rover_pixels())[0].get_y() - (i - 2) * landscape->get_sizey()/200);
            temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
            first_series[i] = temp;
        }
        for(int k = 0; k < 7; k++){
            Point temp;
            temp.set_x((landscape->get_rover_pixels())[0].get_x() + 3 * landscape->get_sizex()/200);
            temp.set_y((landscape->get_rover_pixels())[0].get_y() - (k - 3) * landscape->get_sizey()/200);
            temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
            second_series[k] = temp;
        }
        for(int l = 0; l < 9; l++){
            Point temp;
            temp.set_x((landscape->get_rover_pixels())[0].get_x() + 4 * landscape->get_sizex()/200);
            temp.set_y((landscape->get_rover_pixels())[0].get_y() - (4 - l) * landscape->get_sizey()/200);
            temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
            third_series[l] = temp;
        }

    } else if(rover_direction == "WW"){
        for (int i = 0; i < 5; i++)
        {
            Point temp;
            temp.set_x((landscape->get_rover_pixels())[0].get_x() - 2 * landscape->get_sizex()/200);
            temp.set_y((landscape->get_rover_pixels())[0].get_y() + (i - 2) * landscape->get_sizey()/200);
            temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
            first_series[i] = temp;
        }
        for(int k = 0; k < 7; k++){
            Point temp;
            temp.set_x((landscape->get_rover_pixels())[0].get_x() - 3 * landscape->get_sizex()/200);
            temp.set_y((landscape->get_rover_pixels())[0].get_y() + (k - 3) * landscape->get_sizey()/200);
            temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
            second_series[k] = temp;
        }
        for(int l = 0; l < 9; l++){
            Point temp;
            temp.set_x((landscape->get_rover_pixels())[0].get_x() - 4 * landscape->get_sizex()/200);
            temp.set_y((landscape->get_rover_pixels())[0].get_y() + (4 - l) * landscape->get_sizey()/200);
            temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
            third_series[l] = temp;
        }

    } else if(rover_direction == "NE"){
        for(int i = 0; i < 5; i++)
        {
            Point temp;
            if(i < 3){
                temp.set_x((landscape->get_rover_pixels())[0].get_x() + i * landscape->get_sizex() / 200);
                temp.set_y(((landscape->get_rover_pixels())[0].get_y() + landscape->get_sizey() / 100));
                temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
                first_series[i] = temp;
            } else {
                temp.set_x((landscape->get_rover_pixels())[0].get_x() + landscape->get_sizex() / 100);
                temp.set_y(((landscape->get_rover_pixels())[0].get_y() + (4 - i) * landscape->get_sizey() / 200));
                temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
                first_series[i] = temp;
            }
        }

        for(int k = 0; k < 7; k++)
        {
            Point temp;
            if(k < 4){
                temp.set_x((landscape->get_rover_pixels())[0].get_x() + k * landscape->get_sizex() / 200);
                temp.set_y(((landscape->get_rover_pixels())[0].get_y() + 3 * landscape->get_sizey() / 200));
                temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
                second_series[k] = temp;
            } else {
                temp.set_x((landscape->get_rover_pixels())[0].get_x() + 3 * landscape->get_sizex() / 200);
                temp.set_y(((landscape->get_rover_pixels())[0].get_y() + (6 - k) * landscape->get_sizey() / 200));
                temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
                second_series[k] = temp;
            }
        }

        for(int l = 0; l < 9; l++)
        {
            Point temp;
            if(l < 5){
                temp.set_x((landscape->get_rover_pixels())[0].get_x() + l * landscape->get_sizex() / 200);
                temp.set_y(((landscape->get_rover_pixels())[0].get_y() + 4 * landscape->get_sizey() / 200));
                temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
                third_series[l] = temp;
            } else {
                temp.set_x((landscape->get_rover_pixels())[0].get_x() + 4 * landscape->get_sizex() / 200);
                temp.set_y(((landscape->get_rover_pixels())[0].get_y() + (8 - l) * landscape->get_sizey() / 200));
                temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
                third_series[l] = temp;
            }
        }

    } else if(rover_direction == "SE"){
        for(int i = 0; i < 5; i++){
            Point temp;
            if(i < 3){
                temp.set_x((landscape->get_rover_pixels())[0].get_x() + 2 * landscape->get_sizex() / 200);
                temp.set_y((landscape->get_rover_pixels())[0].get_y() - i * landscape->get_sizey() / 200);
                temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
                first_series[i] = temp;
            } else {
                temp.set_x((landscape->get_rover_pixels())[0].get_x() + (4 - i) * landscape->get_sizex() / 200);
                temp.set_y((landscape->get_rover_pixels())[0].get_y() - 2 * landscape->get_sizey() / 200);
                temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
                first_series[i] = temp;
            }
        }

        for(int k = 0; k < 7; k++){
            Point temp;
            if(k < 4){
                temp.set_x((landscape->get_rover_pixels())[0].get_x() + 3 * landscape->get_sizex() / 200);
                temp.set_y((landscape->get_rover_pixels())[0].get_y() - k * landscape->get_sizey() / 200);
                temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
                second_series[k] = temp;
            } else {
                temp.set_x((landscape->get_rover_pixels())[0].get_x() + (6 - k) * landscape->get_sizex() / 200);
                temp.set_y((landscape->get_rover_pixels())[0].get_y() - 3 * landscape->get_sizey() / 200);
                temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
                second_series[k] = temp;
            }
        }

        for(int l = 0; l < 7; l++){
            Point temp;
            if(l < 5){
                temp.set_x((landscape->get_rover_pixels())[0].get_x() + 4 * landscape->get_sizex() / 200);
                temp.set_y((landscape->get_rover_pixels())[0].get_y() - l * landscape->get_sizey() / 200);
                temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
                second_series[l] = temp;
            } else {
                temp.set_x((landscape->get_rover_pixels())[0].get_x() + (8 - l) * landscape->get_sizex() / 200);
                temp.set_y((landscape->get_rover_pixels())[0].get_y() - 4 * landscape->get_sizey() / 200);
                temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
                second_series[l] = temp;
            }
        }

    } else if(rover_direction == "SW"){
        for(int i = 0; i < 5; i++){
            Point temp;
            if(i < 3){
                temp.set_x((landscape->get_rover_pixels())[0].get_x() - i * landscape->get_sizex() / 200);
                temp.set_y((landscape->get_rover_pixels())[0].get_y() - 2 * landscape->get_sizey() / 200);
                temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
                first_series[i] = temp;
            } else {
                temp.set_x((landscape->get_rover_pixels())[0].get_x() - 2 * landscape->get_sizex() / 200);
                temp.set_y((landscape->get_rover_pixels())[0].get_y() - (4 - i) * landscape->get_sizey() / 200);
                temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
                first_series[i] = temp;
            }
        }

        for(int k = 0; k < 7; k++){
            Point temp;
            if(k < 4){
                temp.set_x((landscape->get_rover_pixels())[0].get_x() - k * landscape->get_sizex() / 200);
                temp.set_y((landscape->get_rover_pixels())[0].get_y() - 3 * landscape->get_sizey() / 200);
                temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
                second_series[k] = temp;
            } else {
                temp.set_x((landscape->get_rover_pixels())[0].get_x() - 3 * landscape->get_sizex() / 200);
                temp.set_y((landscape->get_rover_pixels())[0].get_y() - (6 - k) * landscape->get_sizey() / 200);
                temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
                second_series[k] = temp;
            }
        }

        for(int l = 0; l < 9; l++){
            Point temp;
            if(l < 5){
                temp.set_x((landscape->get_rover_pixels())[0].get_x() - l * landscape->get_sizex() / 200);
                temp.set_y((landscape->get_rover_pixels())[0].get_y() - 4 * landscape->get_sizey() / 200);
                temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
                third_series[l] = temp;
            } else {
                temp.set_x((landscape->get_rover_pixels())[0].get_x() - 4 * landscape->get_sizex() / 200);
                temp.set_y((landscape->get_rover_pixels())[0].get_y() - (8 - l) * landscape->get_sizey() / 200);
                temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
                third_series[l] = temp;
            }
        }

    } else if(rover_direction == "NW"){
        for(int i = 0; i < 5; i++){
            Point temp;
            if(i < 3){
                temp.set_x((landscape->get_rover_pixels())[0].get_x() - 2 * landscape->get_sizex() / 200);
                temp.set_y((landscape->get_rover_pixels())[0].get_y() + i * landscape->get_sizey() / 200);
                temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
                first_series[i] = temp;
            } else {
                temp.set_x((landscape->get_rover_pixels())[0].get_x() - (4 - i) * landscape->get_sizex() / 200);
                temp.set_y((landscape->get_rover_pixels())[0].get_y() + 2 * landscape->get_sizey() / 200);
                temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
                first_series[i] = temp;
            }
        }

        for(int k = 0; k < 7; k++){
            Point temp;
            if(k < 4){
                temp.set_x((landscape->get_rover_pixels())[0].get_x() - 3 * landscape->get_sizex() / 200);
                temp.set_y((landscape->get_rover_pixels())[0].get_y() + k * landscape->get_sizey() / 200);
                temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
                second_series[k] = temp;
            } else {
                temp.set_x((landscape->get_rover_pixels())[0].get_x() - (6 - k) * landscape->get_sizex() / 200);
                temp.set_y((landscape->get_rover_pixels())[0].get_y() + 3 * landscape->get_sizey() / 200);
                temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
                second_series[k] = temp;
            }
        }

        for(int l = 0; l < 9; l++){
            Point temp;
            if(l < 5){
                temp.set_x((landscape->get_rover_pixels())[0].get_x() - 4 * landscape->get_sizex() / 200);
                temp.set_y((landscape->get_rover_pixels())[0].get_y() + l * landscape->get_sizey() / 200);
                temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
                third_series[l] = temp;
            } else {
                temp.set_x((landscape->get_rover_pixels())[0].get_x() - (8 - l) * landscape->get_sizex() / 200);
                temp.set_y((landscape->get_rover_pixels())[0].get_y() + 4 * landscape->get_sizey() / 200);
                temp.set_z(landscape->get_landscape_hight(temp.get_x(), temp.get_y()));
                third_series[l] = temp;
            }
        }
    }
}



void Rover::check_obstacle()
{
    double avg = avg_hight(first_series, second_series, third_series);
    for(int i = 0; i < 5; i++)
    {
        if(first_series[i].get_z() - avg > rover_clearance) {has_obstacle = 1;}
    }
    for(int k = 0; k < 7; k++)
    {
        if(second_series[k].get_z() - avg > rover_clearance) {has_obstacle = 1;}
    }
    for(int l = 0; l < 9; l++)
    {
        if(third_series[l].get_z() - avg > rover_clearance) {has_obstacle = 1;}
    }
    has_obstacle = 0;
}