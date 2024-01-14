//212-Соболев-Никита

#ifndef __BOUNDARY_H__
#define __BOUNDARY_H__
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
    void log_print();

};

#endif
