//212-Соболев-Никита

#include "my_ran.h"
#include <random>
#include "Point.h"
#include <vector>
#include <fstream>
#include <iostream>

double ran() 
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0,1);
    return dis(gen);
}

double avg_hight(std::vector<Point> a, std::vector<Point> b, std::vector<Point> c) 
{
    double sum = 0;
    double count;
    for(int i = 0; i < 5; i++) {sum += (a[i]).get_z(); count++;}
    for(int k = 0; k < 7; k++) {sum += (b[k]).get_z(); count++;}
    for(int l = 0; l < 9; l++) {sum += (c[l]).get_z(); count++;}
    return (sum/count);
}

void help()
{
    std::ofstream file("help.txt");
    file << "Commands for Landscape:\n" << std::endl;
    file << "Command: create_field | waiting params:\n" << "1) double X - size Landscape of X\n" << "2) double Y - size Landscape of Y\n"
         << "Waiting form of command: create_field X Y" << std::endl;

    file << "-------------------------------------------------------------------------" << std::endl;

    file << "Command: create_hill  | waiting params:\n" << "1) double X - coord x of center hill\n" << "2) double Y - coord y of center hill\n"
         << "3) double DispX - dipersion of x\n" << "4) double DispY - despersion of y\n" << "5) double Hight - hight of hill\n"
         << "Wating form of command: create_hill X Y DispX DispY Hight" << std::endl;

    file << "-------------------------------------------------------------------------" << std::endl;

    file << "Command: create_stone  | waiting params:\n" << "1) double X - coord x of center stone\n" << "2) double Y - coord y of center stone\n"
         << "3) double R - radius of stone\n" << "Wating form of command: create_stone X Y R" << std::endl;

    file << "-------------------------------------------------------------------------" << std::endl;

    file << "Command: create_log    | waiting params:\n" << "1) double X1 - coord x the center of first edge of the log\n" << "2) double Y1 - coord y the center of first edge of the log\n"
         << "3) double X2 - coord x the center of the second edge of the log\n" << "4) double Y2 - coord the center of the second edge of the log\n" << "5) double R - radius the log\n"
         << "Wating form of command: create_log X1 Y1 X2 Y2 R" << std::endl;

    file << "-------------------------------------------------------------------------" << std::endl;

    file << "Command: print_field   | no params\n" << "Waiting form of command: print_field" << std::endl;

    file << "-------------------------------------------------------------------------" << std::endl;

    file << "Command: random_hills  | waiting params:\n" << "int H - count generate hills\n"
         << "Waiting form of command: random_hills H" << std::endl;

    file << "-------------------------------------------------------------------------" << std::endl;

    file << "Command: random_stones | waiting params:\n" << "int S - count generate stones\n"
         << "Waiting form of command: random_stones S" << std::endl;

    file << "-------------------------------------------------------------------------" << std::endl;

    file << "Command: random_logs   | waiting params:\n" << "int L - count generate logs\n"
         << "Waiting form of command: random_logs L" << std::endl;

    file << std::endl;

    file << "Commands for Rover:\n" << std::endl;

    file << "Command: rover_move    | waiting params:\n" << "string Dir - direction of rover move (NN, NE, EE, SE, SS, SW, WW, NW)\n" 
         << "Waiting form of command: rover_move Dir" << std::endl;

    file << "-------------------------------------------------------------------------" << std::endl;

    file << "Command: create_rover  | waiting parms:\n" << "1) double X - position rover of x\n" << "2) double Y - position rover of y\n"
         << "Waiting form of command: create_rover X Y" << std::endl;

    file << "-------------------------------------------------------------------------" << std::endl;

    file << "Command: make_rout     | no params\n" << "Waiting form of command: make_rout" << std::endl;

    file << "-------------------------------------------------------------------------" << std::endl;

    file << "Command: exit          | no params\n" << "Waiting form of command: exit" << std::endl;

    file << std::endl;

    file << "If the command does not have enough parameters,\n" << "they are filled with default parameters that are in the configuration file" << std::endl;

    return;
}