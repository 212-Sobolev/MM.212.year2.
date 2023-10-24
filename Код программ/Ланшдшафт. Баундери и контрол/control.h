#pragma once
#include "config.h"
#include <fstream>
#include "boundary.h"
#include "Landscape.h"


class Boundary;

class Control
{
private:
  std::string comand;
  std::vector<double> params;
  std::ofstream logfile;
  Landscape *landscape;
public:
  Control(Landscape *land);

  void read_message_from_Boundary(std::string command_name, std::vector<double> command_params, int* error_code);

  void create_field(std::vector<double> params, int* error_code);
  void create_hill(std::vector<double> params, int* error_code);
  void create_stone(std::vector<double> params, int* error_code);
  void create_log(std::vector<double> params, int* error_code);
  void print_field(int* error_code);

  
  //int print_message(int* error_code);
};
