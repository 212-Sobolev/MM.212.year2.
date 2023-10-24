#pragma once

#include <string>
#include <map>
#include <vector>

const std::string BOUNDARY_LOGFILE_NAME = "boundary_logfile.txt";
const std::string CONTROL_LOGFILE_NAME = "control_logfile.txt";
const double FIELD_SIZE_X = 10;
const double FIELD_SIZE_Y = 10;
const double CURSOR_POSITION_X = 5;
const double CURSOR_POSITION_Y = 5;
const double HILL_HIGHT = 4;
const double HILL_SIGMA[2][2] = {{0.4, 0}, {0, 0.4}};
const double STONE_R = 0.5;
const double LOG_R = 1;
const double ALPHA_P = 1;
const double BETA_P = 1;
const std::map<std::string, std::vector<double>> COMMAND_PARAMS = {
{"create_field", {0, 2}}, {"create_hill", {5, 5, 0.2, 0.2, 7.0}}, {"create_stone", {2, 3}}, {"create_log", {2, 3}},
{"print_field", {0}}
};
