//212-Соболев-Никита

#include "Landscape.h"
#include "Hill.h"
#include "Stoun.h"
#include "Log.h"
#include "my_ran.h"
#include "control.h"
#include "boundary.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <random>
#include <vector>
#include <string>


int main()
{

    //Landscape landscape(50, 50);
    //landscape.create(50, 15, 7);
    //landscape.draw();

    Landscape land;

    Control control(&land);
    Boundary boundary(&control);
    boundary.console_read();


    //std::cout << (control.get_land()).get_sizex() << std::endl;
    //(control.get_land()).get_sizex()
    return 0;

}
