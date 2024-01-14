#include "config.h"
#include <iostream>
#include "Rprocessor.h"
#include "Point.h"
#include <fstream>
#include <math.h>
#include <cmath>
#include <queue>
#include <algorithm>
#include <string>
#include "Landscape.h"

R_Processor::R_Processor(Rover *rov, Landscape *land)
{
    rover = rov;
    landscape = land;
    this->routfile = std::ofstream("finrout.txt");

    start_point = START;
    end_point = END;

}


void R_Processor::print_orig_rout()
{
    std::ofstream file("rout.txt");
    for (Point point : rout)
    {
        file << point.get_x() << " " << point.get_y() << " "
             << landscape->get_landscape_hight(point.get_x(), point.get_y()) << std::endl;      
    }
}

void R_Processor::make_move(std::string dir)
{
    rover->Rover_make_move(dir);
}

void R_Processor::place_rover_start(Point a)
{
    rover->Rover_first_position(a.get_x(), a.get_y());
    if(rover->check_tilts() == 0){
        std::cout << "Bad start point" << std::endl;
        error = 1;
    }

    center_rover.push_back((landscape->get_rover_pixels())[0]);
    tilts_angle_forback.push_back(rover->get_tilt_angle_forback());
    tilts_angle_side.push_back(rover->get_tilt_angle_side());
    directions.push_back(rover->get_direction());
}

std::string R_Processor::decod_direction(int a, int b)
{
    if(abs(a - b) > 1 || abs(a - b) == 0){
        std::cout << "Error with decoding the direction by R-Processor" << std::endl;
        return 0;
    }
    auto it1 = std::next(rout.begin(), a);
    auto it2 = std::next(rout.begin(), b);

    double dX = (*it1).get_x() - (*it2).get_x();
    double dY = (*it1).get_y() - (*it2).get_y();

    if(abs(dX) < EPS and dY > 0){
        return "NN";
    } else if(dX > 0 and dY > 0){
        return "NE";
    } else if(dX > 0 and abs(dY) < EPS){
        return "EE";
    } else if(dX > 0 and dY < 0){
        return "SE";
    } else if(abs(dX) < EPS and dY < 0){
        return "SS";
    } else if(dX < 0 and dY < 0){
        return "SW";
    } else if(dX < 0 and abs(dY) < EPS){
        return "WW";
    } else {                                                                //if(dX < 0 and dY > 0)
        return "NW";
    }
}




void R_Processor::final_rout()
{
    std::cout << "printing final rout" << std::endl;
    std::ofstream file2("final_rout.txt");
    for (size_t i = 0; i < rout.size(); i++)
    {
        file2 << center_rover[i].get_x() << " " << center_rover[i].get_y() << " "
              << landscape->get_landscape_hight(center_rover[i].get_x(), center_rover[i].get_y())  << std::endl;      
    }
}


std::string R_Processor::inverse_dir(std::string direct)
{
    if(direct == "NN"){
        return "SS";
    } else if(direct == "NE"){
        return "SW";
    } else if(direct == "EE"){
        return "WW";
    } else if(direct == "SE"){
        return "NW";
    } else if(direct == "SS"){
        return "NN";
    } else if(direct == "SW"){
        return "NE";
    } else if(direct == "WW"){
        return "EE";
    } else {
        return "SE";
    }
}




class Point2D 
{
private:
    int i;
    int j;

public:
    Point2D() = default;
    Point2D(int i, int j) {
        this->i = i;
        this->j = j;
    }

    int getI() const {return i;}

    int getJ() const {return j;}
};


class Vertex
{
private:
    Point2D Coordinate;
    double Height;
    Point2D CameFrom;
    double Label;
    bool IsVisited;
    bool IsObstacle;


public:
    Vertex() = default;
    Vertex(int i, int j, Point2D CameFrom = Point2D(), double Height = 0.0, double Label = std::numeric_limits<double>::max(), bool IsVisited = false, bool IsObstacle = false) {
        Coordinate = Point2D(i, j);
        this->CameFrom = CameFrom;
        this->Height = Height;
        this->Label = Label;
        this->IsVisited = IsVisited;
        this->IsObstacle = IsObstacle;
    }

    Vertex(int i, int j, double Height){
        Coordinate = Point2D(i, j);
        this->Height = Height;
        Label = std::numeric_limits<double>::max();
        IsVisited = false;
        IsObstacle = false;
    }

    Point2D getCoordinate() const {return Coordinate;}

    double getHeight() const {return Height;}

    void setHeight(double height) {Height = height;}

    Point2D getCameFrom() const {return CameFrom;}

    void setCameFrom(Point2D cameFrom) {CameFrom = cameFrom;}

    double getLabel() const {return Label;}

    void setLabel(double label) {Label = label;}

    bool getIsVisited() const {return IsVisited;}

    void setIsVisited(bool isVisited) {IsVisited = isVisited;}

    bool getIsObstacle() const {return IsObstacle;}

    void setIsObstacle(bool isObstacle) {IsObstacle = isObstacle;}

};

struct MyDoubleComparer {
    bool operator()(const Vertex& v1, const Vertex& v2) const {
        return v1.getLabel() > v2.getLabel();
    }
};



class Graph {
public:
    /// Шаг сетки по оси Ox
    double dx;
    /// Шаг сетки по оси Oy
    double dy;
    /// Количество вершин по оси Ox
    int N;
    /// Количество вершин по оси Oy
    int M;
    /// Матрица вершин графа
    Vertex** Vertices;
    /// Предельная величина уклона в градусах
    double MaxSlope;
    Landscape *landscape;

    Graph(double dx, double dy, int N, int M, Landscape *land) {
        this->dx = dx;
        this->dy = dy;
        this->N = N;
        this->M = M;
        landscape = land;
        MaxSlope = 60;

        Vertices = new Vertex*[N];
        for (int i = 0; i < N; i++) {
            Vertices[i] = new Vertex[M];
        }
        
        for (int j = 0; j < M; j++){
                for (int i = 0; i < N; i++) {
                    Vertices[i][j] = Vertex(i, j, landscape->get_landscape_hight(i * dx, j * dy));
                }
        }
    }

    ~Graph() {
        for (int i = 0; i < N; i++) {
            delete[] Vertices[i];
        }
        delete[] Vertices;
    }

    std::pair<double, double> GetRealXY(Vertex vertex) {
    double x = vertex.getCoordinate().getI() * dx;
    double y = vertex.getCoordinate().getJ() * dy;

    return std::make_pair(x, y);
    }

    double Weight(Vertex v1, Vertex v2) {
    std::pair<double, double> x1y1 = GetRealXY(v1);
    std::pair<double, double> x2y2 = GetRealXY(v2);

    double xDiff = x1y1.first - x2y2.first;
    double yDiff = x1y1.second - x2y2.second;
    double zDiff = v1.getHeight() - v2.getHeight();

    double sumOfSquares = pow(xDiff, 2.0) + pow(yDiff, 2.0) + pow(zDiff, 2.0);

    return sqrt(sumOfSquares);
    }

    double Slope(Vertex v1, Vertex v2) {
        double hypotenuse = Weight(v1, v2); // Вес ребра - это и есть по факту расстояние между точками
        double zDiffAbs = std::abs(v1.getHeight() - v2.getHeight()); // Модуль разности по высоте

        return std::asin(zDiffAbs / hypotenuse) * 180.0 / M_PI; // Переводим радианы в градусы
    }

    Vertex GetNNVertex(Vertex v) {return Vertices[v.getCoordinate().getI()][v.getCoordinate().getJ() + 1];}
    Vertex GetNEVertex(Vertex v) {return Vertices[v.getCoordinate().getI() + 1][v.getCoordinate().getJ() + 1];}
    Vertex GetEEVertex(Vertex v) {return Vertices[v.getCoordinate().getI() + 1][v.getCoordinate().getJ()];}
    Vertex GetSEVertex(Vertex v) {return Vertices[v.getCoordinate().getI() + 1][v.getCoordinate().getJ() - 1];}
    Vertex GetSSVertex(Vertex v) {return Vertices[v.getCoordinate().getI()][v.getCoordinate().getJ() - 1];}
    Vertex GetSWVertex(Vertex v) {return Vertices[v.getCoordinate().getI() - 1][v.getCoordinate().getJ() - 1];}
    Vertex GetWWVertex(Vertex v) {return Vertices[v.getCoordinate().getI() - 1][v.getCoordinate().getJ()];}
    Vertex GetNWVertex(Vertex v) {return Vertices[v.getCoordinate().getI() - 1][v.getCoordinate().getJ() + 1];}

    bool IsTopRightVertex(Vertex v1) {return v1.getCoordinate().getI() == N - 1 && v1.getCoordinate().getJ() == M - 1;}

    bool IsVertexOnTheRightSide(Vertex v1) {return v1.getCoordinate().getI() == N - 1;}

    bool IsTopLeftVertex(Vertex v1) {return v1.getCoordinate().getI() == 0 && v1.getCoordinate().getJ() == M - 1;}

    bool IsBottomRightVertex(Vertex v1) {return v1.getCoordinate().getI() == N - 1 && v1.getCoordinate().getJ() == 0;}

    bool IsBottomLeftVertex(Vertex v1) {return v1.getCoordinate().getI() == 0 && v1.getCoordinate().getJ() == 0;}

    bool IsVertexOnTheLeftSide(Vertex v1) {return v1.getCoordinate().getI() == 0;}

    bool IsVertexOnTheTopSide(Vertex v1) {return v1.getCoordinate().getJ() == M - 1;}

    bool IsVertexOnTheBottomSide(Vertex v1) {return v1.getCoordinate().getJ() == 0;}

    std::vector<Vertex> GetAllAdjacentVertices(Vertex vertex) {
        // Рассматриваем угловые вершины
        if (IsTopRightVertex(vertex)) {
            return {
                GetWWVertex(vertex),
                GetNWVertex(vertex),
                GetSSVertex(vertex)
            };
        } else if (IsBottomRightVertex(vertex)) {
            return {
                GetNNVertex(vertex),
                GetNWVertex(vertex),
                GetWWVertex(vertex)
            };
        } else if (IsBottomLeftVertex(vertex)) {
            return {
                GetNNVertex(vertex),
                GetNEVertex(vertex),
                GetEEVertex(vertex)
            };
        } else if (IsTopLeftVertex(vertex)) {
            return {
                GetSSVertex(vertex),
                GetSEVertex(vertex),
                GetEEVertex(vertex)
            };
        } else if (IsVertexOnTheTopSide(vertex)) {
            return {
                GetWWVertex(vertex),
                GetSWVertex(vertex),
                GetSSVertex(vertex),
                GetSEVertex(vertex),
                GetEEVertex(vertex)
            };
        } else if (IsVertexOnTheRightSide(vertex)) {
            return {
                GetNNVertex(vertex),
                GetNWVertex(vertex),
                GetWWVertex(vertex),
                GetSWVertex(vertex),
                GetSSVertex(vertex)
            };
        } else if (IsVertexOnTheBottomSide(vertex)) {
            return {
                GetWWVertex(vertex),
                GetNWVertex(vertex),
                GetNNVertex(vertex),
                GetNEVertex(vertex),
                GetEEVertex(vertex)
            };
        } else if (IsVertexOnTheLeftSide(vertex)) {
            return {
                GetNNVertex(vertex),
                GetNEVertex(vertex),
                GetEEVertex(vertex),
                GetSEVertex(vertex),
                GetSSVertex(vertex)
            };
        } else {
            return {
            GetNNVertex(vertex),
            GetEEVertex(vertex),
            GetSSVertex(vertex),
            GetWWVertex(vertex),
            GetNEVertex(vertex),
            GetSEVertex(vertex),
            GetSWVertex(vertex),
            GetNWVertex(vertex)
        };
    }
}
    

    std::vector<Vertex> GetValidNeighbors(Vertex current) {
        // Из всех смежных вершин оставляем только те, которые 
        // 1. Еще не посещены
        // 2. Не являются вершинами-препятствиями
        // 3. Наклон к которым меньше заданной величины (например, 30 градусов)



        std::vector<Vertex> result;



        std::vector<Vertex> adjacentVertices = GetAllAdjacentVertices(current);
        std::copy_if(adjacentVertices.begin(), adjacentVertices.end(), std::back_inserter(result), [this, current](const Vertex& v) {

            return !v.getIsVisited() && !v.getIsObstacle() && Slope(v, current) < MaxSlope;
        });

        return result;
    }

    std::vector<Point2D> FindShortestPathAndLength(Point2D startPoint, Point2D goalPoint, double& shortestPathLength) {

        //if(error == 1) {return std::vector<Point2D>();}

        shortestPathLength = 0.0;

        Vertex& start = Vertices[startPoint.getI()][startPoint.getJ()];
        start.setLabel(0);


        Vertex& goal = Vertices[goalPoint.getI()][goalPoint.getJ()];
        goal.setCameFrom(Point2D(-1, -1));

        std::priority_queue<Vertex, std::vector<Vertex>, MyDoubleComparer> priorityQueue;
        priorityQueue.push(start);

        

        while (!priorityQueue.empty() && !goal.getIsVisited()) {
            Vertex current = priorityQueue.top();
            priorityQueue.pop();

            if (Vertices[current.getCoordinate().getI()][current.getCoordinate().getJ()].getIsVisited()) {
                continue;
            }
            


            Vertices[current.getCoordinate().getI()][current.getCoordinate().getJ()].setIsVisited(1);


            std::vector<Vertex> neighbors = GetValidNeighbors(current);



            for (Vertex& neighbor : neighbors) {
                double currentWeight = current.getLabel() + Weight(current, neighbor);
                if (currentWeight < neighbor.getLabel()) {
                    Vertices[neighbor.getCoordinate().getI()][neighbor.getCoordinate().getJ()].setLabel(currentWeight);
                    Vertices[neighbor.getCoordinate().getI()][neighbor.getCoordinate().getJ()].setCameFrom(current.getCoordinate());
                    neighbor.setLabel(currentWeight);
                    priorityQueue.push(neighbor);
                }
            }

        }


        shortestPathLength = goal.getLabel();



        std::vector<Point2D> shortestPath;
        Vertex current = goal;
        if(goal.getCameFrom().getI() == -1 and goal.getCameFrom().getJ() == -1) {
            std::cout << "Wrong points or landscape" << std::endl;
            return std::vector<Point2D>();
        }
        while (abs(current.getCoordinate().getI() - startPoint.getI()) > EPS || abs(current.getCoordinate().getJ() != startPoint.getJ()) > EPS) {
            shortestPath.push_back(current.getCoordinate());
            current = Vertices[current.getCameFrom().getI()][current.getCameFrom().getJ()];
        }
        shortestPath.push_back(startPoint);

        std::reverse(shortestPath.begin(), shortestPath.end());

        return shortestPath;
    }
};

void R_Processor::Djkstra()
{
    Graph G(0.2, 0.2, 50, 50, landscape);
    Point2D startPoint(START.get_x() * 5, START.get_y() * 5);
    Point2D goalPoint(END.get_x() * 5, END.get_y() * 5);
    std::ofstream file("Djkstra_rout.txt");


    double length;
    std::vector<Point2D> Djkstra_rout = G.FindShortestPathAndLength(startPoint, goalPoint, length);
    if (Djkstra_rout.size() == 0) {return;}
    std::cout << "rout created with size: " << Djkstra_rout.size() << " and length: " << length << std::endl;
    for(int i = 0; i < (int)Djkstra_rout.size(); i++){
        
        double x = Djkstra_rout[i].getI() * G.dx;
        double y = Djkstra_rout[i].getJ() * G.dy;
        double z = landscape->get_landscape_hight(Djkstra_rout[i].getI()*G.dx, Djkstra_rout[i].getJ()*G.dy);
        file << x << " " << y << " "<< z <<  std::endl;

        rout.push_back(Point(x, y, z));
    }
    //std::cout << rout.size() << std::endl;

    folow_rout();
}

void R_Processor::folow_rout()
{
    place_rover_start(rout[0]);

    for(int i = 0; i < (int)rout.size(); i++){
        std::string dir = decod_direction(i, i+1);
        make_move(dir);
        center_rover.push_back(rout[i+1]);
        tilts_angle_forback.push_back(rover->get_tilt_angle_forback());
        tilts_angle_side.push_back(rover->get_tilt_angle_side());
        directions.push_back(dir);
    }

    //std::cout << "count fixing points " << center_rover.size() << std::endl;
    //std::cout << "count tilts angle forback " << tilts_angle_forback.size() << std::endl;
    //std::cout << "count tilts angle side " << tilts_angle_side.size() << std::endl;
    //std::cout << "count rover directions " << directions.size() << std::endl;
}