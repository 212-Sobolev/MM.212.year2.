//212-Соболев-Никита

#include <iostream>
#include <fstream>
#include <math.h>
#include <random>
#include <time.h> 
#include <vector>


class Hill
{
private:
    double x; //координаты 
    double y;
    double sigma;
    double hight; //высота холма
public:
    Hill(double size_x, double size_y);
    Hill(double x0, double y0, double sigma0, double hight0)
    : x(x0), y(y0), hight(hight0) {sigma = abs(sigma0);}

    //Гауссово распределение в точке, относительно холмика
    double Gauss(double x0, double y0) const;
};

//Ландшафт
class Landscape
{
private:
    double size_x; //размеры поверхности
    double size_y;
    std::vector<Hill> hills; 
    int count_hills;
public:
    Landscape() = default;
    Landscape(double x, double y, int count_hills = 0);

    // Записываем в файл, для рисунка в GNUplot
    void print(std::ofstream &file) const;

};

int main()
{
    srand(time(NULL));
    Landscape landscape(100, 100, 250);
    std::ofstream file("hills.txt");
    landscape.print(file);
    file.close();
    return 0;

}

Hill::Hill(double size_x,double size_y)
{
    x = rand() / double(RAND_MAX) * size_x - size_x/2;
    y = rand() / double(RAND_MAX) * size_y - size_y/2; 
    sigma = rand() / double(RAND_MAX) * 2.9 + 0.1;
    hight = rand() / double(RAND_MAX) * 10 - 5;
}

Landscape::Landscape(double x, double y, int count_hills):
                    size_x(x), size_y(y), count_hills(count_hills)
{
    for(int i=0; i < count_hills; i++)
    {
        hills.push_back(Hill(x,y));
    }
}

double Hill::Gauss(double x0, double y0) const
{
  double e = exp(-((x - x0) * (x - x0) + (y - y0) * (y - y0)) / 2 * sigma * sigma);
  return (hight * e) / (sigma * sqrt(2 * M_PI));
}

void Landscape::print(std::ofstream&file) const
{
    double z;
    for(double i = -size_x/2; i <= size_x/2; i+=size_x/50)
    {
        for(double j = -size_y/2; j <= size_y/2; j+=size_y/50)
        {
            z=0;
            for(int k = 0; k< count_hills; k++)
            {
                z+=hills[k].Gauss(i,j);
            }
            file << i << " " << j << " " << z << "\n";
        }
        file << "\n";
    }    
}