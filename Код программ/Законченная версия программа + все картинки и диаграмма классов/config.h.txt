//212-Соболев-Никита

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>
#include <vector>
#include "Point.h"

const double EPS = 1e-9;
const std::string BOUNDARY_LOGFILE_NAME = "boundary_logfile.txt";
const std::string CONTROL_LOGFILE_NAME = "control_logfile.txt";
const double FIELD_SIZE_X = 10;
const double FIELD_SIZE_Y = 10;
const std::string possible_direction[8] = {"NN", "NE", "EE", "SE", "SS", "SW", "WW", "NW"};
const double CURSOR_POSITION_X = 5;
const double CURSOR_POSITION_Y = 5;
const double HILL_HIGHT = 4;
const double HILL_SIGMA1 = 0.4;
const double HILL_SIGMA2 = 0.4;
//const double HILL_SIGMA[2][2] = {{0.4, 0}, {0, 0.4}};
const double STONE_R = 0.5;
const double LOG_R = 1;
const double ALPHA_P = 1;
const double BETA_P = 1;
const double COUNT_RANDOM_HILLS = 5;
const double COUNT_RANDOM_STONES = 5;
const double COUNT_RANDOM_LOGS = 5;
const double MAX_TILT_ANGLE_FORBACK = 60;
const double MAX_TILT_ANGLE_SIDE = 60;
const double ROVER_CLEARENCE = 0.05;
const Point START(1,1);
const Point END(8,8);

#endif
