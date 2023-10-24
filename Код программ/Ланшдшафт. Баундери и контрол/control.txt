#include "config.h"
#include "Landscape.h"
#include "Log.h"
#include "Stoun.h"
#include "control.h"
#include <string>
#include <vector>
#include <iostream>
#include "Hill.h"


Control::Control(Landscape *land)
{
  landscape = land;
  this->logfile = std::ofstream(CONTROL_LOGFILE_NAME);
}




void Control::read_message_from_Boundary(std::string command_name, std::vector<double> command_params, int* error_code)
{
  if (command_name == "create_field") {
    if (command_params.size() < 2) {
      double defaultParam1 = FIELD_SIZE_X;
      double defaultParam2 = FIELD_SIZE_Y;
      create_field({defaultParam1, defaultParam2}, error_code);
    } else {
      create_field(command_params, error_code);
    }
  } else if (command_name == "create_hill") {
    if (command_params.size() < 5) {
      double defaultParam1 = CURSOR_POSITION_X;
      double defaultParam2 = CURSOR_POSITION_Y;
      double defaultParam3 = HILL_SIGMA[0][0];
      double defaultParam4 = HILL_SIGMA[1][1];
      double defaultParam5 = HILL_HIGHT;
      create_hill({defaultParam1, defaultParam2, defaultParam3, defaultParam4, defaultParam5}, error_code);
    } else {
      create_hill(command_params, error_code);
    }
  } else if (command_name == "create_stone") {
    if (command_params.size() < 3) {
      double defaultParam1 = CURSOR_POSITION_X;
      double defaultParam2 = CURSOR_POSITION_Y;
      double defaultParam3 = STONE_R;
      create_stone({defaultParam1, defaultParam2, defaultParam3}, error_code);
    } else {
      create_stone(command_params, error_code);
    }
  } else if (command_name == "create_log") {
    if (command_params.size() < 5) {
      double defaultParam1 = CURSOR_POSITION_X;
      double defaultParam2 = CURSOR_POSITION_Y;
      double defaultParam3 = CURSOR_POSITION_X;
      double defaultParam4 = CURSOR_POSITION_Y;
      double defaultParam5 = LOG_R;
      create_log({defaultParam1, defaultParam2, defaultParam3, defaultParam4, defaultParam5}, error_code);
    } else {
      create_log(command_params, error_code);
    }
  } else if (command_name == "print_field") {
    print_field(error_code);
  }
}








void Control::create_field(std::vector<double> params, int* error_code)
{
  *error_code = 0;
  try
  {
    if(params.size() == 0)
    {

      landscape->set_sizex(FIELD_SIZE_X);
      landscape->set_sizey(FIELD_SIZE_Y);
    }
    else 
    {

      landscape->set_sizex(params[0]);
      landscape->set_sizey(params[1]);
    }
  } catch (int exception)
  {
    if (exception == 1) 
    {
      *error_code = 1; // некорректные размеры поля
    }
  }

}


void Control::create_hill(std::vector<double> params, int* error_code)
{
  try
  {
    if(params.size() != 5)
    {
      *error_code = 1; // Incorrect number of parameters
      return;
    }
    double x = params[0];
    double y = params[1];
    double dispx = params[2];
    double dispy = params[3];
    double hight = params[4];
    std::vector<Hill> temp = landscape->get_contain_hill();
    temp.push_back(Hill(x, y, dispx, dispy, hight));
    landscape->set_contain_hill(temp);
  }
  catch(int e)
  {
    std::cout << "fail int: " <<  e << std::endl;
  }
  


}

void Control::create_stone(std::vector<double> params, int* error_code)
{
  if(params.size() != 3) {
    *error_code = 1; // Incorrect number of parameters
    return;
  }
  double x = params[0];
  double y = params[1];
  double r = params[2];
  Stoun stone(x, y, r);

}

void Control::create_log(std::vector<double> params, int* error_code)
{
  if(params.size() != 5) {
    *error_code = 1; // Incorrect number of parameters
    return;
  }
  double x1 = params[0];
  double y1 = params[1];
  double x2 = params[2];
  double y2 = params[3];
  double r = params[4];
  Log log(x1, y1, x2, y2, r);

}
//*****



void Control::print_field(int* error_code)
{
  if (params.size() > 1)
  {
    *error_code = 1;
  }
  double z;
    std::ofstream fout("out2.txt");
    for(double i = 0; i <= landscape->get_sizex(); i += landscape->get_sizex() / 200)
    {
        for(double j = 0; j < landscape->get_sizey(); j += landscape->get_sizey() / 200)
        {
            z=0;
            for(std::vector<Hill>::size_type k=0; k < (landscape->get_contain_hill()).size(); k++)
            {
                z+=((landscape->get_contain_hill())[k]).Gauss(i, j);
            }
            fout << i << " " << j << " " << z << std::endl;
        }
        fout << std::endl;
    }

}

