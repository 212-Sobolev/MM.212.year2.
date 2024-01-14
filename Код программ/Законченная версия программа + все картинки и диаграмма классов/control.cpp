//212-Соболев-Никита

#include "config.h"
#include "Landscape.h"
#include "Log.h"
#include "Stoun.h"
#include "control.h"
#include <string>
#include <vector>
#include <iostream>
#include "Hill.h"
#include "my_ran.h"
#include <time.h>
#include "Rover.h"


Control::Control(Landscape *land)
{
  landscape = land;
  this->logfile = std::ofstream(CONTROL_LOGFILE_NAME);
}


Control::Control(Landscape *land, R_Processor *proc)
{
    landscape = land;
    processor = proc;
    this->logfile = std::ofstream(CONTROL_LOGFILE_NAME);

}


void Control::log_print()
{
  time_t seconds = time(NULL);
  tm* timeinfo = localtime(&seconds);
  logfile << asctime(timeinfo);
}






void Control::create_field(std::vector<double> params)
{
      landscape->set_sizex(params[0]);
      landscape->set_sizey(params[1]);

      log_print();
      logfile <<  "Command executed: create_field | " << "A " << landscape->get_sizex()
              << " by " << landscape->get_sizey() << " field was generated" << std::endl;
      logfile << std::endl; 
}


void Control::create_hill(std::vector<double> params)
{
    double x = params[0];
    double y = params[1];
    double dispx = params[2];
    double dispy = params[3];
    double hight = params[4];
    std::vector<Hill> temp = landscape->get_contain_hill();
    temp.push_back(Hill(x, y, dispx, dispy, hight));
    landscape->set_contain_hill(temp);

    log_print();
    logfile <<  "Command executed: create_hill | " << "A hill was created with parameters " 
            <<"x is: " <<  x << ", y is: "  << y << ", dispx is: " << dispx << ", dispy is: "
            << dispy << ", hight is: " << hight << std::endl;
    logfile << std::endl;
}



void Control::create_stone(std::vector<double> params)
{
  double x = params[0];
  double y = params[1];
  double r = params[2];

  std::vector<Stoun> temp = landscape->get_contain_stoun();
  temp.push_back(Stoun(x, y, r));
  landscape->set_contain_stoun(temp);

  log_print();
  logfile << "Command executed: create_stone | " << "A stone was created with parameters "
          << "x is: " << x << ", y is " << y << ", r is: " << r << std::endl;
  logfile << std::endl;

}

void Control::create_log(std::vector<double> params)
{

  double x1 = params[0];
  double y1 = params[1];
  double x2 = params[2];
  double y2 = params[3];
  double r = params[4];
  
  std::vector<Log> temp = landscape->get_contain_log();
  temp.push_back(Log(x1, y1, x2, y2, r));
  landscape->set_contain_log(temp);

  log_print();
  logfile << "Commad executed: create_log | " << "A log was created with parameters " 
          << "x1 is: " << x1 << ", y1 is: " << y1 << ", x2 is: " << x2 << ", y2 is: " 
          << y2 << ", r is: " << r << std::endl;
  logfile << std::endl;

}
//*****



void Control::print_field()
{
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
            for(std::vector<Stoun>::size_type k = 0; k < (landscape->get_contain_stoun()).size(); k++)
            {
              z+=((landscape->get_contain_stoun())[k]).sphere(i,j);
            }
            for(std::vector<Stoun>::size_type k = 0; k < (landscape->get_contain_log()).size(); k++)
            {
              z+=((landscape->get_contain_log())[k]).cylinder(i,j);
            }
            fout << i << " " << j << " " << z << std::endl;
        }
        fout << std::endl;
    }
  log_print();
  logfile << "field was generated in file out2.txt" << std::endl;
  logfile << std::endl;
}

void Control::random_hills(std::vector<double> params)
{
  //сделать проверку что получаем интовый параметр
  int n = (int) params[0];

  for(int i = 0; i < n; i++)
  {
    double  x = ran() * landscape->get_sizex();
    double y = ran() * landscape->get_sizey();
    double dispx = ran() + 1.5;
    double dispy = ran() + 1;
    double hight = ran()*30 - 15 ;  

    std::vector<Hill> temp = landscape->get_contain_hill();
    temp.push_back(Hill(x, y, dispx, dispy, hight));
    landscape->set_contain_hill(temp);
  }
  log_print();
  logfile <<  "Command executed: random_hills " << n << " hills randomly generated"<< std::endl;
  logfile << std::endl;
}

void Control::random_stones(std::vector<double>params)
{
  int n = (int) params[0];

  for(int i = 0; i < n; i++)
  {
    double  x = ran() * landscape->get_sizex();
    double y = ran() * landscape->get_sizey();
    double r = ran() + 0.5;

    std::vector<Stoun> temp = landscape->get_contain_stoun();
    temp.push_back(Stoun(x, y, r));
    landscape->set_contain_stoun(temp);
  }
  log_print();
  logfile <<  "Command executed: random_stouns " << n << " stouns randomly generated"<< std::endl;
  logfile << std::endl;
}

void Control::random_logs(std::vector<double>params)
{
  int n = (int) params[0];

  for(int i = 0; i < n; i++)
  {
    double x1 = ran() * landscape->get_sizex();
    double y1 = ran() * landscape->get_sizey();
    double x2 = ran() * landscape->get_sizex();
    double y2 = ran() * landscape->get_sizey();
    double R = ran() - 0.2;

    std::vector<Log> temp = landscape->get_contain_log();
    temp.push_back(Log(x1, y1, x2, y2, R));
    landscape->set_contain_log(temp);
  }
  log_print();
  logfile <<  "Command executed: random_logs " << n << " logs randomly generated"<< std::endl;
  logfile << std::endl;
}


void Control::Rover_move(std::string direction)
{
  processor->make_move(direction);
  log_print();
  logfile <<  "Command executed: Rover_move " << params_rover[0] << std::endl;
  logfile << std::endl;
}

void Control::create_rover(std::vector<double> params)
{
  Point a(params[0], params[1]);

  processor->place_rover_start(a);
  log_print();
  logfile <<  "Command executed: create_rover in (" << params[0] << ", " << params[1] << ")" << std::endl;
  logfile << std::endl;
}

void Control::make_rout()
{
  processor->Djkstra();
  log_print();
  logfile <<  "Command executed: make_rout " << std::endl;
  logfile << std::endl;

}