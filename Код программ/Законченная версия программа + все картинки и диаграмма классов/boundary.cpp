//212-Соболев-Никита

#include "boundary.h"
#include "config.h"
#include "control.h"
#include <iostream>
#include <sstream>
#include <time.h>
#include <fstream>


Boundary::Boundary(Control *c)
{
  ctrl = c;
  this->logfile = 
    std::ofstream(BOUNDARY_LOGFILE_NAME);
}

void Boundary::log_print()
{
  time_t seconds = time(NULL);
  tm* timeinfo = localtime(&seconds);
  logfile << asctime(timeinfo);
}

void Boundary::console_read()
{
  std::ifstream file("command.txt");
  std::string massage;
  while (getline(file, massage))
  {
    int status;
    char prove;
    char line_tail[1024];
    std::vector<double> params;
    char rover_direction[] = "NN";

    //std::cout << massage << std::endl;

    params.push_back(FIELD_SIZE_X);
    params.push_back(FIELD_SIZE_Y);
    status = sscanf(massage.c_str(), "create_fiel%c %lf %lf %s", &prove, &params[0], &params[1], line_tail);
    if (status > 0 and status <= 3 and prove == 'd') {
      ctrl->create_field(params); 
      std::string successMessage = "Command completed";
      log_print();
      logfile << "Command is: create_field | execution status: " << successMessage << std::endl;
      logfile << std::endl;
      continue;
      }
    params.clear();


    params.push_back(CURSOR_POSITION_X);
    params.push_back(CURSOR_POSITION_Y);
    params.push_back(HILL_SIGMA1);
    params.push_back(HILL_SIGMA2);
    params.push_back(HILL_HIGHT);
    status = sscanf(massage.c_str(), "create_hil%c %lf %lf %lf %lf %lf %s", &prove, &params[0], &params[1], &params[2], &params[3], &params[4], line_tail);
    if (status > 0 and status <= 6 and prove == 'l') {
      ctrl->create_hill(params); 
      std::string successMessage = "Command completed";
      log_print();
      logfile << "Command is: create_hill | execution status: " << successMessage << std::endl;
      logfile << std::endl;
      continue;
      }
    params.clear();


    params.push_back(CURSOR_POSITION_X);
    params.push_back(CURSOR_POSITION_Y);
    params.push_back(STONE_R);
    status = sscanf(massage.c_str(), "create_ston%c %lf %lf %lf %s", &prove, &params[0], &params[1], &params[2], line_tail);
    if(status > 0 and status <= 4 and prove == 'e') {
      ctrl->create_stone(params); 
      std::string successMessage = "Command completed";
      log_print();
      logfile << "Command is: create_stone | execution status: " << successMessage << std::endl;
      logfile << std::endl;
      continue;
      }
    params.clear();


    params.push_back(CURSOR_POSITION_X);
    params.push_back(CURSOR_POSITION_Y);
    params.push_back(CURSOR_POSITION_X);
    params.push_back(CURSOR_POSITION_Y);
    params.push_back(LOG_R);
    status = sscanf(massage.c_str(), "create_lo%c %lf %lf %lf %lf %lf %s", &prove, &params[0], &params[1], &params[2], &params[3], &params[4], line_tail);
    if (status > 0 and status <= 6 and prove == 'g') {
      ctrl->create_log(params);
      std::string successMessage = "Command completed";
      log_print();
      logfile << "Command is: create_log | execution status: " << successMessage << std::endl;
      logfile << std::endl;
      continue;
      }
    params.clear();


    status = sscanf(massage.c_str(), "print_fiel%c %s", &prove, line_tail);
    if(status == 1 and prove == 'd') {
      ctrl->print_field(); 
      std::string successMessage = "Command completed";
      log_print();
      logfile << "Command is: print_field | execution status: " << successMessage << std::endl;
      logfile << std::endl;
      continue;
      }


    params.push_back(COUNT_RANDOM_HILLS);
    status = sscanf(massage.c_str(), "random_hill%c %lf %s", &prove, &params[0], line_tail);
    if(status > 0 and status <=2 and prove == 's') {
      ctrl->random_hills(params); 
      std::string successMessage = "Command completed";
      log_print();
      logfile << "Command is: random_hills | execution status: " << successMessage << std::endl;
      logfile << std::endl;
      continue;
      }
    params.clear();


    params.push_back(COUNT_RANDOM_STONES);
    status = sscanf(massage.c_str(), "random_stone%c %lf %s", &prove, &params[0], line_tail);
    if(status > 0 and status <= 2 and prove == 's') {
      ctrl->random_stones(params); 
      std::string successMessage = "Command completed";
      log_print();
      logfile << "Command is: random_stones | execution status: " << successMessage << std::endl;
      logfile << std::endl;
      continue;
      }
    params.clear();


    params.push_back(COUNT_RANDOM_LOGS);
    status = sscanf(massage.c_str(), "random_log%c %lf %s", &prove, &params[0], line_tail);
    if(status > 0 and status <= 2 and prove == 's') {
      ctrl->random_logs(params);
      std::string successMessage = "Command completed";
      log_print();
      logfile << "Command is: random_logs | execution status: " << successMessage << std::endl;
      logfile << std::endl;
      continue;
       }
    params.clear();


    status = sscanf(massage.c_str(), "exi%c %s", &prove, line_tail);
    if(status == 1 and prove == 't') {
      std::string successMessage = "Command completed";
      log_print();
      logfile << "Command is: exit | execution status: " << successMessage << std::endl;
      logfile << std::endl;
      return;
      }
    

    status = sscanf(massage.c_str(), "rover_mov%c %s %s", &prove, rover_direction, line_tail);
    if(status > 0 and status <= 2 and prove == 'e'){
      std::string dir(rover_direction);
      ctrl->Rover_move(dir);
      std::string successMessage = "Command completed";
      log_print();
      logfile << "Command is: rover_move " << dir << " | execution status: " << successMessage << std::endl;
      logfile << std::endl;
      continue;
    }


    params.push_back(CURSOR_POSITION_X);
    params.push_back(CURSOR_POSITION_Y);
    status = sscanf(massage.c_str(), "create_rove%c %lf %lf %s", &prove, &params[0], &params[1], line_tail);
    if(status > 0 and status <= 3 and prove == 'r'){
      ctrl->create_rover(params);
      std::string successMessage = "Command completed";
      log_print();
      logfile << "Command is: create_rover | execution status: " << successMessage << std::endl;
      logfile << std::endl;
      continue;
    }


    status = sscanf(massage.c_str(), "make_rou%c %s", &prove, line_tail);
    if(status == 1 and prove == 't'){
      ctrl->make_rout();
      std::string successMessage = "Command completed";
      log_print();
      logfile << "Command is: make_rout | execution status: " << successMessage << std::endl;
      logfile << std::endl;
      continue;
    }


  std::string errorMessage = "Wrong command";
  std::cout << "This is unknown command, try again"<< std::endl;
  log_print();
  logfile << "Command is: " << massage << " | " << "execution status: " << errorMessage << std::endl;
  logfile << std::endl;
  }
}
