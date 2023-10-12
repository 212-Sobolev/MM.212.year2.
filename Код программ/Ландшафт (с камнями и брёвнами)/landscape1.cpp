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

class Stoun
{
private:
  double x;
  double y;
  double r;
public:
  Stoun(double size_x, double size_y);
  Stoun(double x0, double y0, double r0)
   : x(x0), y(y0), r(r0) {}

   double get_x() const {return x;}
   double get_y() const {return y;}
   double get_r() const {return r;}
   double dist(double x0, double y0) const;

};

class Log
{
private:
    double x1;
    double y1;
    double x2;
    double y2;
    double r; 
public:
    Log(double size_x, double size_y);
    Log(double x01, double y01, double x02, double y02, double r0)
    : x1(x01), y1(y01), x2(x02), y2(y02), r(r0){}

    double get_x1() const {return x1;}
    double get_y1() const {return y1;}
    double get_x2() const {return x2;}
    double get_y2() const {return y2;}
    double get_r() const {return r;}
    double dist(double x0, double y0) const;
};


//Ландшафт
class Landscape
{
private:
    double size_x; //размеры поверхности
    double size_y;
    std::vector<Hill> hills; 
    std::vector<Stoun> stouns;
    std::vector<Log> logs;
    int count_hills;
    int count_stouns;
    int count_logs;
public:
    Landscape() = default;
    Landscape(double x, double y, int count_hills = 0, int count_stones = 0, int count_logs = 0);

    // Записываем в файл, для рисунка в GNUplot
    void print(std::ofstream &file1, std::ofstream &file2, std::ofstream &file3) const;

};

int main()
{
    srand(time(NULL));
    Landscape landscape(25, 25, 15, 8, 4);
    std::ofstream file1("hills.txt");
    std::ofstream file2("stouns.txt");
    std::ofstream file3("logs.txt");
    landscape.print(file1, file2, file3);
    file1.close();
    file2.close();
    file3.close();
    return 0;

}

Hill::Hill(double size_x,double size_y)
{
    x = rand() / double(RAND_MAX) * size_x - size_x/2;
    y = rand() / double(RAND_MAX) * size_y - size_y/2; 
    sigma = rand() / double(RAND_MAX) * 1.9 + 0.1;
    hight = rand() / double(RAND_MAX) * 10 - 5;
}

Stoun::Stoun(double size_x, double size_y)
{
    r = rand() / double(RAND_MAX) * 1.2 + 0.5;
    x = rand() / double(RAND_MAX) * (size_x-r) - (size_x-r)/2;
    y = rand() / double(RAND_MAX) * (size_y-r) - (size_y-r)/2;
    
}

Log::Log(double size_x, double size_y)
{
    x1 = rand() / double(RAND_MAX) * size_x - size_x/2;
    y1 = rand() / double(RAND_MAX) * size_y - size_y/2;
    r = rand() / double(RAND_MAX) * 1 + 0.5;
    double lenght = (rand() / double(RAND_MAX) * 3 + 1) * r;
    double direction = rand() / double(RAND_MAX) * 2;
    x2 = x1 + lenght * cos(direction * M_PI);
    y2 = y1 + lenght * sin(direction * M_PI);
}

Landscape::Landscape(double x, double y, int count_hills, int count_stouns, int count_logs):
                    size_x(x), size_y(y), count_hills(count_hills),
                    count_stouns(count_stouns), count_logs(count_logs)
{
    for(int i=0; i < count_hills; i++)
    {
        hills.push_back(Hill(x,y));
    }
    for(int i = 0; i < count_stouns; i++)
    {
        stouns.push_back(Stoun(x,y));
    }
    for(int i=0; i < count_logs; i++)
    {
        logs.push_back(Log(x,y));
    }
}

double Hill::Gauss(double x0, double y0) const
{
  double e = exp(-((x - x0) * (x - x0) + (y - y0) * (y - y0)) / 2 * sigma * sigma);
  return (hight * e) / (sigma * sqrt(2 * M_PI));
}

void Landscape::print(std::ofstream &file1, std::ofstream &file2, std::ofstream &file3) const
{
    /*if (!file1.is_open())
    {
        std::cout << "Ошибка: Не удалось открыть файл file1." << std::endl;
        return;
    }

    if (!file2.is_open())
    {
        std::cout << "Ошибка: Не удалось открыть файл file2." << std::endl;
        return;
    } */


    double z;
    for(double i = -size_x/2; i <= size_x/2; i+=size_x/100)
    {
        for(double j = -size_y/2; j <= size_y/2; j+=size_y/100)
        {
            z=0;
            for(int k = 0; k < count_hills; k++)
            {
                z+=hills[k].Gauss(i,j);
            }
            file1 << i << " " << j << " " << z << "\n";
        }
        file1 << "\n";
    }    

    //печатаем в файл камни
    for(int k = 0; k < count_stouns; k++)
    {
        //std::cout << k+1 << "Number of stouns" << std::endl;
        z=0;
        for(int m = 0; m < count_hills; m++)
        {
            z+=hills[m].Gauss(stouns[k].get_x(), stouns[k].get_y());
        }

        //рисуем верхнюю часть камня
        for(double i = stouns[k].get_r(); i > 0; i-=stouns[k].get_r()/20)
        {
            for (double j = 0; j < 2.1; j+=0.1)
            {
                file2 << stouns[k].get_x() + i * cos(j * M_PI) << 
                 " "  << stouns[k].get_y() + i * sin(j * M_PI) <<
                 " "  << sqrt(stouns[k].get_r() * stouns[k].get_r() - i * i) + z << "\n";
            }
            file2 << "\n";
        }
        file2 << "\n";

        //рисуем нижнюю часть камня
        for(double i = stouns[k].get_r(); i > 0; i-=stouns[k].get_r()/20)
        {
            for (double j = 0; j < 2.1; j+=0.1)
            {
                file2 << stouns[k].get_x() + i * cos(j * M_PI) << 
                 " "  << stouns[k].get_y() + i * sin(j * M_PI) <<
                 " "  << -sqrt(stouns[k].get_r() * stouns[k].get_r() - i * i) + z << "\n";
            }
            file2 << "\n";
        }
        file2 << "\n";
    }

    
    //печатаем в файл брёвна
    double z1, z2;
    for(int k = 0; k < count_logs; k++)
    {
        z1=0;
        z2=0;
        for(int m=0; m < count_hills; m++)
        {
            z1+=hills[m].Gauss(logs[k].get_x1(), logs[k].get_y1());
            z2+=hills[m].Gauss(logs[k].get_x2(), logs[k].get_y2());
        }

        //рисуем концы брева
        for(double i=logs[k].get_r(); i>0; i-=logs[k].get_r()/10)
            {
                for(double j=0; j<2.1; j+=0.1)
                {
                    file3 << logs[k].get_x1() + i * cos(j*M_PI) << " " << logs[k].get_y1() << " " << z1 + i*sin(j*M_PI) << "\n";
                }
                file3 << "\n";
            }
            file3 << std::endl;
        
        for(double i=logs[k].get_r(); i>0; i-=logs[k].get_r()/10)
            {
                for(double j=0; j<2.1; j+=0.1)
                {
                    file3 << logs[k].get_x2() + i * cos(j*M_PI) << " " << logs[k].get_y2() << " " << z2 + i*sin(j*M_PI) << "\n";
                }
                file3 << "\n";
            }
            file3 << std::endl;

        //рисуем оставшуюся поверхность бревна
        for(double j=0; j<2.1; j+=0.05)
        {
            file3 << logs[k].get_x1() + logs[k].get_r() * cos(j*M_PI) <<
              " " << logs[k].get_y1() << " " << z1 + logs[k].get_r()*sin(j*M_PI) << "\n";

            file3 << logs[k].get_x2() + logs[k].get_r() * cos(j*M_PI) <<
              " " << logs[k].get_y2() << " " << z2 + logs[k].get_r()*sin(j*M_PI) << "\n";

            file3 << std::endl;
        }
    }
}
