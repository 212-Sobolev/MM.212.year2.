/*#include "includes.h"


class Boundary
{
private:
  std::string message;
  std::ofstream logfile;
  Control *ctrl;
public:
  Boundary(Control *c);
  

  void console_read();
  //bool check_command_name(std::string command_name);
  //bool check_command_params(int count);

  //void console_write(int error_code);
  
};

*/
#pragma once
#include <string>
#include <fstream>
#include "control.h"
#include "config.h"

class Control;

class Boundary
{
private:
    std::string massage;
    std::ofstream logfile;
    Control *ctrl;
public:
    Boundary(Control *c);

    void console_read();

};