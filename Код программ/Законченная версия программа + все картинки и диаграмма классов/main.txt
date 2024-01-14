//212-Соболев-Никита

#include "Rover.h"
#include "Point.h"
#include "Landscape.h"
#include "Hill.h"
#include "Stoun.h"
#include "Log.h"
#include "my_ran.h"
#include "control.h"
#include "boundary.h"
#include "Rprocessor.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <random>
#include <vector>
#include <string>
#include <time.h>


int main()
{   
    clock_t start = clock();
    std::string command;
    
    std::cout << "If you want to read the set of rules for using the program enter: help\n"
              << "If you want start programm enter: running" << std::endl;

    std::cin >> command;
    if (command == "help") {
        help(); 
        std::cout << "Information in help.txt" << std::endl;
        return 0;
    }else if(command == "running") {}
    else {
        std::cout << "Wrong command" << std::endl;
        return 0;
    }

    Landscape land;
    Rover rover(&land);
    R_Processor proc(&rover, &land);
    Control control(&land, &proc);
    Boundary boundary(&control);

    boundary.console_read();
   
    clock_t end = clock();
    double seconds = (double)(end - start);
    std::cout << "The time: " << seconds << std::endl;
    
    return 0;
}
