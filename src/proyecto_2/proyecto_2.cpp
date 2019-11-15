//
// 2 JUEGO
// ANGEL ARMANDO VALAY MARTINEZ
// Created by angel on 14/11/19.
//
#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include "game.h"


//Dimensiones de la pantalla
#define WidthWin 600
#define HeightWin 600

//variables globales
double NEAR_Z = 1.0;
double FAR_Z = 400.0;

//zoom por ejes
float zoom = 80;
float zoom_x = 0;
float zoom_y = 0;
float zoom_z = 0;

// is show message?
bool showMessageStart = true;

// timer
int refreshMillis = 800;

//Mallas del juego
Wall wallX = Wall(LIM_X,LIM_Z,'Y');
vector<Point> pointsWallX = wallX.getPoints();
Wall wallY = Wall(LIM_X,15,'Z');
vector<Point> pointsWallY = wallY.getPoints();
Wall wallZ = Wall(15,LIM_Z,'X');
vector<Point> pointsWallZ = wallZ.getPoints();

vector<Figure*> figures;


Figure *figure = new Figure(rand() % 3 ,1,15,1);

void timer(int value){
    if (showMessageStart){
//        for(Cube cube: figure->cubes()){
//            std::cout<<cube.getPointToArray().x<<" "<<cube.getPointToArray().y<<" "<<cube.getPointToArray().y<<endl;
//        }
        if (figure->isValidateMove(0,-1,0, &figures)){
//            cout<<"Puede bajar"<<endl;
            //refrescar pantalla
            figure->moveY(-1);
            glutPostRedisplay();
        }else{
//            cout<<"No se puede bajar"<<endl;
            figures.push_back(figure);
            figure = new Figure(rand() % 3,1,10,1);
            glutPostRedisplay();
        }
    }
    glutTimerFunc(refreshMillis, timer, 0);
}

void printInteraction(){
    cout<<""<<endl;
    cout<<""<<endl;
}

void init(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void resize(int w, int h){
    if (h == 0){
        h = 1;
    }
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(10.0, w / h, NEAR_Z, FAR_Z);
    glMatrixMode(GL_MODELVIEW);
}

void key(unsigned char key, int x, int y){
    switch (key){
        case ' ':
            showMessageStart = !showMessageStart;
            break;
        case '+':
            figure->isValidateRotate(false, false, false);
            break;
        case '-':
            break;
        case 'x':
//            zoom_x = zoom_x + 10;
            figure->rotationX();
            break;
        case 'X':
            zoom_x = zoom_x - 10;
//            figure->rotationY();
            break;
        case 'y':
//            zoom_y = zoom_y + 10;
            figure->rotationY();
            break;
        case 'Y':
            zoom_y = zoom_y - 10;
            break;
        case 'z':
            figure->rotationZ();
            break;
        case '\n':
            break;
        default:
            break;
    }
    if (zoom_x > 360)
        zoom_x = 10;
    if (zoom_x < 0)
        zoom_x = 360;
    if (zoom_y > 360)
        zoom_y = 10;
    if (zoom_y < 0)
        zoom_y = 360;
    glutPostRedisplay();
}
void displayText(){
    /**
     * IMPRIMIR TEXTO
     */
}
void displayMe(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(zoom, zoom, zoom,0.0,5,0.0,0.0,1.0,0.0);
    glRotatef(zoom_x,1,0,0);
    glRotatef(zoom_y,0,1,0);
    glRotatef(zoom_z,0,0,1);
    //display text
    glBegin(GL_LINES);
    for(Point &point: pointsWallX){
        glVertex3d(point.x,point.y, point.z);
    }
    glEnd();
    glColor3f(0.5,0.6,0.7);
    glBegin(GL_LINES);
    for(Point &point: pointsWallY){
        glVertex3d(point.x,point.y, point.z);
    }
    glEnd();
    glColor3f(0.8, 0.1, 0.7);
    glBegin(GL_LINES);
    for(Point &point: pointsWallZ){
        glVertex3d(point.x,point.y, point.z);
    }
    glEnd();
    //hago un translei para mover las figuras una mitad del cubo hacia el inferior para que
    // coloquen bien
    glTranslatef(UNIT_CUBE/2,UNIT_CUBE/2,UNIT_CUBE/2);
//    se imprimen las figuras almacenadas
    for(Figure* figure1 : figures){
        glColor3fv(figure1->getColor());
        for (Cube cube: figure1->cubes()){
            for (int i = 0; i < 6; ++i) {
                glBegin(GL_POLYGON);
                for (int j = 0; j < 4; ++j) {
                    glVertex3d(cube.getFaces(i)[j].x, cube.getFaces(i)[j].y, cube.getFaces(i)[j].z);
                }
                glEnd();
            }
        }
        glColor3f(1,1,1);
        for (Cube cube: figure1->cubes()){
            for (int i = 0; i < 6; ++i) {
                glBegin(GL_LINE_LOOP);
                for (int j = 0; j < 4; ++j) {
                    glVertex3d(cube.getFaces(i)[j].x, cube.getFaces(i)[j].y, cube.getFaces(i)[j].z);
                }
                glEnd();
            }
        }
    }
    //aqui se imprimen la figura seleccionada
    glColor3fv(figure->getColor());
    for (Cube cube: figure->cubes()){
        for (int i = 0; i < 6; ++i) {
            glBegin(GL_POLYGON);
            for (int j = 0; j < 4; ++j) {
                glVertex3d(cube.getFaces(i)[j].x, cube.getFaces(i)[j].y, cube.getFaces(i)[j].z);
            }
            glEnd();

        }
    }
    glColor3f(1,1,1);
    for (Cube cube: figure->cubes()){
        for (int i = 0; i < 6; ++i) {
            glBegin(GL_LINE_LOOP);
            for (int j = 0; j < 4; ++j) {
                glVertex3d(cube.getFaces(i)[j].x, cube.getFaces(i)[j].y, cube.getFaces(i)[j].z);
            }
            glEnd();

        }
    }
    glutSwapBuffers();
}

void specialKeyInput(int key, int x, int y){
    if (key == GLUT_KEY_UP)
    {
        if (figure->isValidateMove(0,0,1, &figures)){
            figure->moveZ(1);
            glutPostRedisplay();
        }
    }
    if (key == GLUT_KEY_DOWN)
    {
        if (figure->isValidateMove(0,0,-1, &figures)){
            figure->moveZ(-1);
            glutPostRedisplay();
        }
    }
    if (key == GLUT_KEY_RIGHT)
    {
        if (figure->isValidateMove(1,0,0, &figures)){
            figure->moveX(1);
            glutPostRedisplay();
        }
    }
    if (key == GLUT_KEY_LEFT)
    {
        if (figure->isValidateMove(-1,0,0, &figures)){
            figure->moveX(-1);
            glutPostRedisplay();
        }
    }
}

int main(int argc, char **argv){
    float point1 [3]={1,0,1};
    float point2 [3]={0,0,0};
    float point3 [3]={0,0,-1};
    float point4 [3]={0,0,1};
//    cout<<point1[0]<<" "<<point1[1]<<" "<<point1[2]<<endl;
//    rotationZ(point1);
//    cout<<point1[0]<<" "<<point1[1]<<" "<<point1[2]<<endl<<endl;
//    cout<<point2[0]<<" "<<point2[1]<<" "<<point2[2]<<endl;
//    rotationZ(point2);
//    cout<<point2[0]<<" "<<point2[1]<<" "<<point2[2]<<endl<<endl;
//    cout<<point3[0]<<" "<<point3[1]<<" "<<point3[2]<<endl;
//    rotationZ(point3);
//    cout<<point3[0]<<" "<<point3[1]<<" "<<point3[2]<<endl<<endl;
//    cout<<point4[0]<<" "<<point4[1]<<" "<<point4[2]<<endl;
//    rotationZ(point3);
//    cout<<point4[0]<<" "<<point4[1]<<" "<<point4[2]<<endl<<endl;
    printInteraction();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE);
    glutInitWindowSize(HeightWin, WidthWin);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Juego 2 | Tetris 3D");
    glutReshapeFunc(resize);
    glutDisplayFunc(displayMe);
    glutKeyboardFunc(key);
    glutTimerFunc(0,timer,0);
    glutSpecialFunc(specialKeyInput);
    init();
    glutMainLoop();
    return 0;
}