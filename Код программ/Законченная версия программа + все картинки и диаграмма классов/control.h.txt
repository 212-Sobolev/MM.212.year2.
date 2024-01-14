//212-Соболев-Никита

#ifndef __CONTROL_H__
#define __CONTROL_H__
#include "config.h"
#include <fstream>
#include "boundary.h"
#include "Landscape.h"
#include "Rover.h"
#include "Rprocessor.h"


class Boundary;

class Control
{
private:
  std::string comand;
  std::vector<double> params;
  std::vector<std::string> params_rover;
  std::ofstream logfile;
  Landscape *landscape;
  R_Processor *processor;
  
  
public:
  Control(Landscape *land);
  Control(Landscape *land, R_Processor *proc);


  void create_field(std::vector<double> params);
  void create_hill(std::vector<double> params);
  void create_stone(std::vector<double> params);
  void create_log(std::vector<double> params);
  void print_field();
  void random_hills(std::vector<double>params);
  void random_stones(std::vector<double>params);
  void random_logs(std::vector<double>params);


  void create_rover(std::vector<double> params);
  void Rover_move(std::string direction);
  void log_print();
  void make_rout();

};

#endif
