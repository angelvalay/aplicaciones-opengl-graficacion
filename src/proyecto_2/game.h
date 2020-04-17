#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <iostream>
#include "matrix.h"

using namespace std;

float UNIT_CUBE = 1;
//types of figures
int FIG_LINEAL = 0; // |
int FIG_L = 1; // L
int FIG_S = 2; // S

//constant for define width and height
const int LIM_X = 7;
const int LIM_Z = 7;

//state of rotation of figures
const int STATE_BASE = 0; //state base
const int STATE_UP = 1; //state to up
const int STATE_REV = 2;// state to reverse
const int STATE_DOWN = 3; //state to down

struct Point
{
    float x;
    float y;
    float z;
};

class Wall
{
	public:
		Wall(int width, int height, char axis); //constructor
        vector<Point> getPoints();
		
	private:
		int width = 1; //anchura de la malla
	    int height = 1;//altura de la malla
	    char axis = 'X'; //eje donde se hara la malla
};

/*
Constructor para inicializar una malla
:param width: Anchura de la malla
:param height: Altura de la malla
:param axis: Un caracter para determinar que eje
*/
Wall::Wall(int width, int height, char axis)
{	
	this->width = width;
	this->height = height;
	this->axis = axis;
}

/*Funcion para crear los puntos necesarios para crear la malla
:return: Una lista de un array de longitud 3*/
vector<Point> Wall::getPoints()
{
	//se inicializa el arreglo
	vector<Point> points;
	int y;
    Point point{};
    y = this-> height+1;
	//este ciclo me permite crear los puntos sobre la anchura
	for (int x = 0; x <= this-> width + 1; ++x)
	{
        //y = this-> height;
		if (this-> axis == 'X')
		{
			//se agrega de un lado			
			point = {0,(float)x,(float)y};
            points.push_back(point);
            //se agrega del otro extremo            
            point = {0,(float)x,0};
            points.push_back(point);
		}
		else if (this-> axis == 'Y')
		{
			//se agrega de un lado
			point = {(float)x,0,(float)y};
			points.push_back(point);            
            //se agrega del otro extremo
            point = {(float)x,0,0};
            points.push_back(point);            
		}
		else if (this-> axis == 'Z')
		{
			//se agrega de un lado
			point = {(float)x,(float)y,0};
			points.push_back(point);			
            //se agrega del otro extremo
            point = {(float)x,0,0};
            points.push_back(point);            
		}
	}

    //este ciclo me permite crear los puntos sobre la altura
    int x = this-> width+1;
    //preguntar x = this-> width;
    for (int y = 0; y <= this-> height+1; ++y) {
        //x = this-> width;
        if(this-> axis == 'X')
        {
            // se agrega de un lado
            point = {0,(float)x,(float)y};
            points.push_back(point);
            // se agrega del otro extremo
            point = {0,0,(float)y};
            points.push_back(point);
        }
        else if (this->axis == 'Y')
        {
            //se agrega de un lado
            point = {(float)x,0,(float)y};
            points.push_back(point);
            //se agrega del otro extremo
            point = {0,0,(float)y};
            points.push_back(point);
        }
        else if (this->axis == 'Z')
        {
            //se agrega de un lado
            point = {(float)x,(float)y,0};
            points.push_back(point);
            //se agrega del otro extremo
            point = {0,(float)y,0};
            points.push_back(point);
        }
    }
    return  points;
}

class Cube
{
    public:
        Cube(float centerX, float centerY, float centerZ);
        void generatePoints();
        float centerX();
        void centerX(float val);
        float centerY();
        void centerY(float val);
        float centerZ();
        void centerZ(float val);
        Point* pointsCube();
        void pointsCube(Point* points);
        float* getPointToArray();
        Point* getFaces( int numberFace);
        Point* getPoints();
private:
        Point* points = new Point[8];
        float* pointCenter = new float[3];

};

Cube::Cube(float centerX, float centerY, float centerZ)
{
    this->pointCenter[0] = centerX;
    this->pointCenter[1] = centerY;
    this->pointCenter[2] = centerZ;
    this->generatePoints();
}

void Cube::generatePoints()
{
    //Punto 1 [-,+,-]
    this->points[0] = {this->pointCenter[0] - (UNIT_CUBE/2),
                       this->pointCenter[1] + (UNIT_CUBE/2),
                       this->pointCenter[2] - (UNIT_CUBE/2)};

    //Punto 2 [+,+,-]
    this->points[1] = {this->pointCenter[0] + (UNIT_CUBE/2),
                       this->pointCenter[1] + (UNIT_CUBE/2),
                       this->pointCenter[2] - (UNIT_CUBE/2)};

    //Punto 3 [-,+,+]
    this->points[2] = {this->pointCenter[0] - (UNIT_CUBE/2),
                       this->pointCenter[1] + (UNIT_CUBE/2),
                       this->pointCenter[2] + (UNIT_CUBE/2)};

    //Punto 4 [+,+,+]
    this->points[3] = {this->pointCenter[0] + (UNIT_CUBE/2),
                       this->pointCenter[1] + (UNIT_CUBE/2),
                       this->pointCenter[2] + (UNIT_CUBE/2)};

    //Punto 5 [-,-,+]
    this->points[4] = {this->pointCenter[0] - (UNIT_CUBE/2),
                       this->pointCenter[1] - (UNIT_CUBE/2),
                       this->pointCenter[2] + (UNIT_CUBE/2)};

    //Punto 6 [-,-,-]
    this->points[5] = {this->pointCenter[0] - (UNIT_CUBE/2),
                       this->pointCenter[1] - (UNIT_CUBE/2),
                       this->pointCenter[2] - (UNIT_CUBE/2)};

    //Punto 7 [+,-,-]
    this->points[6] = {this->pointCenter[0] + (UNIT_CUBE/2),
                       this->pointCenter[1] - (UNIT_CUBE/2),
                       this->pointCenter[2] - (UNIT_CUBE/2)};

    //Punto 8 [+,-,+]
    this->points[7] = {this->pointCenter[0] + (UNIT_CUBE/2),
                       this->pointCenter[1] - (UNIT_CUBE/2),
                       this->pointCenter[2] + (UNIT_CUBE/2)};
}

float Cube::centerX()
{
    return this->pointCenter[0];
}

void Cube::centerX(float val)
{
    this->pointCenter[0] = val;
}

float Cube::centerY()
{
    return this->pointCenter[1];
}

void Cube::centerY(float val)
{
    this->pointCenter[1] = val;
}

float Cube::centerZ()
{
    return this->pointCenter[2];
}

void Cube::centerZ(float val)
{
    this->pointCenter[2] = val;
}

Point* Cube::pointsCube()
{
    return  this->points;
}

void Cube::pointsCube(Point* points)
{
    this->points = points;
}

float* Cube::getPointToArray()
{
    return  this->pointCenter;
}

Point* Cube::getFaces(int numberFace)
{
    Point* subPoints = new Point[4];
    if (numberFace == 0)
    {
        subPoints[0] = this->points[0];
        subPoints[1] = this->points[1];
        subPoints[2] = this->points[3];
        subPoints[3] = this->points[2];
    }
    else if(numberFace == 1)
    {
        subPoints[0] = this->points[1];
        subPoints[1] = this->points[3];
        subPoints[2] = this->points[7];
        subPoints[3] = this->points[6];
    }
    else if(numberFace == 2)
    {
        subPoints[0] = this->points[6];
        subPoints[1] = this->points[7];
        subPoints[2] = this->points[4];
        subPoints[3] = this->points[5];
    }
    else if(numberFace == 3)
    {
        subPoints[0] = this->points[4];
        subPoints[1] = this->points[5];
        subPoints[2] = this->points[0];
        subPoints[3] = this->points[2];
    }
    else if(numberFace == 4)
    {
        subPoints[0] = this->points[4];
        subPoints[1] = this->points[7];
        subPoints[2] = this->points[3];
        subPoints[3] = this->points[2];
    }
    else if(numberFace == 5)
    {
        subPoints[0] = this->points[0];
        subPoints[1] = this->points[1];
        subPoints[2] = this->points[6];
        subPoints[3] = this->points[5];
    }
    return subPoints;
}

Point *Cube::getPoints() {
    return this->points;
}


class Figure
{
    public:
        Figure(int typeFigure, int posX, int posY, int posZ);
        void moveX(float posX);
        void moveY(float posY);
        void moveZ(float posZ);
        void rotationX();
        void rotationY();
        void rotationZ();
        const vector<Cube> cubes();
        void cubes(vector<Cube> val);
        bool isValidateMove(float posX, float posY, float posZ, vector<Figure*>* figures);
        //void toString();
        float* getColor();
        bool isValidateRotateX(vector<Figure*>* figures);
        bool isValidateRotateY(vector<Figure *> *figures);
        bool isValidateRotateZ(vector<Figure *> *figures);
    private:
        void createCubes();
        vector<Cube> _cubes;
        vector<Point> _pointBase;
        int posX;
        int posY;
        int posZ;
        float* colors = new float[3];
        int typeFigure;
        int stateRotationX;
        int stateRotationY;
        int stateRotationZ;
};

//constructor
Figure::Figure(int typeFigure, int posX, int posY, int posZ)
{
    this->posX = posX;
    this->posY = posY;
    this->posZ = posZ;
//    this->_cubes.push_back(Cube(posX,posY,posZ));
    this->_pointBase.push_back({0,0,0});
    if (typeFigure == FIG_L)
    {
//        this->_cubes.push_back(Cube(posX,posY,posZ - 1));
        this->_pointBase.push_back({0,0,1});
//        this->_cubes.push_back(Cube(posX,posY,posZ + 1));
        this->_pointBase.push_back({0,0,2});
//        this->_cubes.push_back(Cube(posX + 1,posY,posZ + 1));
        this->_pointBase.push_back({1,0,2});
    }
    else if (typeFigure == FIG_LINEAL)
    {
//        this->_cubes.push_back(Cube(posX,posY,posZ - 1));
        this->_pointBase.push_back({0,0,-1});
//        this->_cubes.push_back(Cube(posX,posY,posZ + 1));
        this->_pointBase.push_back({0,0,1});
    }
    else if (typeFigure == FIG_S)
    {
//        this->_cubes.push_back(Cube(posX - 1,posY,posZ));
        this->_pointBase.push_back({-1,0,0});
//        this->_cubes.push_back(Cube(posX, posY, posZ + 1));
        this->_pointBase.push_back({0,0,1});
//        this->_cubes.push_back(Cube(posX + 1,posY,posZ + 1));
        this->_pointBase.push_back({1,0,1});
    }
    this->colors[0] = (float)(rand() % 10)/10;
    this->colors[1] = (float)(rand() % 10)/10;
    this->colors[2] = (float)(rand() % 10)/10;
    this->typeFigure = typeFigure;
    this->stateRotationX = STATE_BASE;
    this->stateRotationY = STATE_BASE;
    this->stateRotationZ = STATE_BASE;
    createCubes();
}

void Figure::moveX(float posX)
{
    this->posX += posX;
    for(Cube &cube : this->_cubes)
    {
        cube.centerX(cube.centerX() + posX);
        cube.generatePoints();
    }
}

void Figure::moveY(float posY)
{
    this->posY += posY;
    for(Cube &cube : this->_cubes)
    {
        cube.centerY(cube.centerY() + posY);
        cube.generatePoints();
    }
}

void Figure::moveZ(float posZ)
{
    this->posZ += posZ;
    for(Cube &cube : this->_cubes)
    {
        cube.centerZ(cube.centerZ() + posZ);
        cube.generatePoints();
    }
}

const vector<Cube> Figure::cubes()
{
    return this->_cubes;
}

void Figure::cubes(vector<Cube> val)
{
    this->_cubes = val;
}

bool Figure::isValidateMove(float posX, float posY, float posZ, vector<Figure*>* figures)
{
    for(Figure* figure: *figures){
        for(Cube cubeOnFig: (figure->cubes())) {
            for (Cube &myCubes : this->_cubes) {
                //checa si hay choque con algun otro cubo en esa posicion
                if ((myCubes.centerX() + posX) == cubeOnFig.centerX()&& (myCubes.centerY() + posY) == cubeOnFig.centerY() &&
                (myCubes.centerZ() + posZ) == cubeOnFig.centerZ()) {
//                    cout << "X sobre pasa del terreno\n";
//                    cout << cubeOnFig.centerX();
//                    cout << "\n";
                    return false;
                }
            }
        }
    }
    for(Cube &myCubes : this->_cubes){
        if((myCubes.centerX() + posX) > LIM_X || (myCubes.centerX() + posX) < 0)
        {
//            cout << "X sobre pasa del terreno\n";
//            cout << myCubes.centerX();
//            cout << "\n";
            return false;
        }
        else if ((myCubes.centerY() + posY) < 0)
        {
//            cout << "Y sobre pasa del terreno ";
//            cout << myCubes.centerY();
//            cout << "\n";
            return  false;
        }
        else if((myCubes.centerZ() + posZ) > LIM_Z || (myCubes.centerZ() + posZ) < 0)
        {
//            cout << "Z sobre pasa del terreno ";
//            cout << myCubes.centerZ();
//            cout << "\n";
            return false;
        }

    }
    return true;
}

float *Figure::getColor() {
    return this->colors;
}

void Figure::rotationX() {
    for(Point &cubeOnFig: this->_pointBase) {
        ::rotationX(&cubeOnFig.x, &cubeOnFig.y, &cubeOnFig.z);
    }
    createCubes();
}

void Figure::rotationY() {
    for(Point &cubeOnFig: this->_pointBase) {
        ::rotationY(&cubeOnFig.x, &cubeOnFig.y, &cubeOnFig.z);
    }
    createCubes();
}

void Figure::rotationZ() {
    for(Point &cubeOnFig: this->_pointBase) {
        ::rotationZ(&cubeOnFig.x, &cubeOnFig.y, &cubeOnFig.z);
    }
    createCubes();
}

bool Figure::isValidateRotateX(vector<Figure*>* figures) {
    for(Point &cubeOnFig: this->_pointBase){
        Point point{cubeOnFig.x,cubeOnFig.y, cubeOnFig.z};
        ::rotationX(&point.x, &point.y, &point.z);
        for(Figure* figure: *figures){
            for(Cube cubeOnFig: (figure->cubes())) {
                for (Cube &myCubes : this->_cubes) {
                    //checa si hay choque con algun otro cubo en esa posicion
                    if (((posX + point.x) == cubeOnFig.centerX()&&
                        (posY + point.y) == cubeOnFig.centerY() &&
                        (posZ + point.z) == cubeOnFig.centerZ())) {
//                        cout << "Choca con un cubo\n";
                        return false;
                    }else if((posX + point.x) > LIM_X || (posX + point.x)<0){
//                        cout << "Choca con la pared x\n";
                        return false;
                    }else if((posY + point.y) < 0){
//                        cout << "Choca con la pared y\n";
                        return false;
                    }else if((posZ + point.z) > LIM_Z || (posZ + point.z)<0){
//                        cout << "Choca con la pared z\n";
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool Figure::isValidateRotateY(vector<Figure*>* figures) {
    for(Point &cubeOnFig: this->_pointBase){
        Point point{cubeOnFig.x,cubeOnFig.y, cubeOnFig.z};
        ::rotationY(&point.x, &point.y, &point.z);
        for(Figure* figure: *figures){
            for(Cube cubeOnFig: (figure->cubes())) {
                for (Cube &myCubes : this->_cubes) {
                    //checa si hay choque con algun otro cubo en esa posicion
                    if (((posX + point.x) == cubeOnFig.centerX()&&
                         (posY + point.y) == cubeOnFig.centerY() &&
                         (posZ + point.z) == cubeOnFig.centerZ())) {
//                        cout << "Choca con un cubo\n";
                        return false;
                    }else if((posX + point.x) > LIM_X || (posX + point.x)<0){
//                        cout << "Choca con la pared x\n";
                        return false;
                    }else if((posY + point.y) < 0){
//                        cout << "Choca con la pared y\n";
                        return false;
                    }else if((posZ + point.z) > LIM_Z || (posZ + point.z)<0){
//                        cout << "Choca con la pared z\n";
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool Figure::isValidateRotateZ(vector<Figure*>* figures) {
    for(Point &point1: this->_pointBase){
        Point point{point1.x,point1.y, point1.z};
        ::rotationZ(&point.x, &point.y, &point.z);
        for(Figure* figure: *figures){
            for(Cube cubeOnFig: (figure->cubes())) {
                for (Cube &myCubes : this->_cubes) {
                    //checa si hay choque con algun otro cubo en esa posicion
                    if (((posX + point.x) == cubeOnFig.centerX()&&
                         (posY + point.y) == cubeOnFig.centerY() &&
                         (posZ + point.z) == cubeOnFig.centerZ())) {
//                        cout << "Choca con un cubo\n";
                        return false;
                    }else if((posX + point.x) > LIM_X || (posX + point.x)<0){
//                        cout << "Choca con la pared x\n";
                        return false;
                    }else if((posY + point.y) < 0){
//                        cout << "Choca con la pared y\n";
                        return false;
                    }else if((posZ + point.z) > LIM_Z || (posZ + point.z)<0){
//                        cout << "Choca con la pared z\n";
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

void Figure::createCubes() {
    this->_cubes.clear();
    for(Point punto: this->_pointBase){
        this->_cubes.push_back(Cube(posX + punto.x,
                posY + punto.y,posZ +punto.z));
    }
}
