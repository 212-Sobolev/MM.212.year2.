#include "boundary.h"
#include "config.h"
#include "control.h"
#include <iostream>
#include <sstream>


Boundary::Boundary(Control *c)
{
  ctrl = c;
  this->logfile = 
    std::ofstream(BOUNDARY_LOGFILE_NAME);
}

void Boundary::console_read()
{
    std::string comand;
    std::vector<double> count_args;
    double param;
    int error = 0;
    std::vector<double> args;
  while (getline(std::cin, massage))
  {
    std::istringstream iss(massage);
    iss >> comand;
    if (comand == "exit")
    {
      std::cout << "Programm end" << std::endl;
      return;
    }
    for (auto i = COMMAND_PARAMS.begin(); 
         i != COMMAND_PARAMS.end(); i++)
    {
      if (comand == i->first)
      {
        count_args = i->second;
        break;
      }
    }
    //flag = 1;
    if (count_args.size())
    {
      while(iss >> param)
      {
        args.push_back(param);
      }
      for (std::vector<int>::size_type i = 0; i < count_args.size(); i++)
      {
        if (args.size() ==(std::vector<double>::size_type)count_args[i])
        {
          //flag = 0;
          break;
        }
      }
      //if (flag) throw 2; // TODO исключение
    }
    // записать в logfile 
    ctrl->read_message_from_Boundary(comand, args, &error);


   //***** 
  if (error != 0) {
    std::string errorMessage = "Error message";
    std::cout << errorMessage << std::endl;
    logfile << errorMessage << std::endl;
  } else {
    std::string successMessage = "Successfully message";
    std::cout << successMessage << std::endl;
    logfile << successMessage << std::endl;
  }
//*****

  }
}
