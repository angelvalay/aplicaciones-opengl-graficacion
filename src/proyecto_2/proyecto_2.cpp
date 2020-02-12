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

// Globals.
static float square_color[3] = {1.0, 0.0, 0.0}; // Color of the square.


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


Figure *figure = new Figure(rand() % 3 ,rand() % 1+5,18,rand() % 3+5);

void timer(int value){
    for(Figure *figure1: figures){
        for(Cube  cube: figure1->cubes()) {
           if(cube.getPoints()->y > 16){
               std::cout<<"#################### FIN DEL JUEGO ##############"<<endl;
                exit(0);
           }
        }
    }
    if (showMessageStart)
        if (figure->isValidateMove(0,-1,0, &figures)){
            //refrescar pantalla
            figure->moveY(-1);
            glutPostRedisplay();
        }else{
            figures.push_back(figure);
            figure = new Figure(rand() % 3 ,rand() % 1+5,18,rand() % 1+5);
            glutPostRedisplay();
        }
    glutTimerFunc(refreshMillis, timer, 0);
}

void restartGame(){
    showMessageStart = false;
    for(Figure* figure1: figures){
        delete(figure1);
    }
    figures.clear();
    figure = new Figure(rand() % 3 ,rand() % 1+5,18,rand() % 1+5);
    glutPostRedisplay();
}

void printInteraction(){
    cout<<"Interation:"<<endl;
    cout<<"Key [p] for stop/resume"<<endl;
    cout<<"Key [z] for rotate on axis Z"<<endl;
    cout<<"Key [x] for rotate on axis X"<<endl;
    cout<<"Key [c] for rotate on axis Y"<<endl;
    cout<<"Key [UP ARROW] for move to far"<<endl;
    cout<<"Key [DOWN ARROW] for move to front"<<endl;
    cout<<"Key [LEFT ARROW] for move to left"<<endl;
    cout<<"Key [RIGHT ARROW] for move to right"<<endl;
    cout<<"Key [+] for more velocity"<<endl;
    cout<<"Key [END] for restart game"<<endl;
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
        case 'p':
            showMessageStart = !showMessageStart;
            break;
        case 'x':
            if (figure->isValidateRotateX(&figures)){
                figure->rotationX();
            }
            break;
        case 'c':
            if (figure->isValidateRotateY(&figures)){
                figure->rotationY();
            }
            break;
        case 'z':
            if (figure->isValidateRotateZ(&figures)){
                figure->rotationZ();
            }
            break;
        case 'u':
            zoom_y+=10;
//            cout<<"y "<<zoom_y<<endl;
            break;
        case 'i':
            zoom_x+=10;
//            cout<<"x "<<zoom_x<<endl;
            break;
        case 'o':
            zoom_z+=10;
//            cout<<" "<<zoom_z<<endl;
            break;
        case '+':
            if (showMessageStart)
                if (figure->isValidateMove(0,-1,0, &figures)){
                    //refrescar pantalla
                    figure->moveY(-1);
                    glutPostRedisplay();
                }else{
                    figures.push_back(figure);
                    figure = new Figure(rand() % 3,3,18,3);
                    glutPostRedisplay();
                }
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

// The top menu callback function.
void top_menu(int id)
{
    if (id==1) exit(0);
}
void sub_menu(int id){
    glutPostRedisplay();
}

// The sub-menu callback function.
void view_menu(int id)
{
    if (id==2)
    {
        zoom_x = 200;
        zoom_y =240;
        zoom_z =310;
    }

    if (id==4)
    {
        zoom_x = 0;
        zoom_y =0;
        zoom_z = 0;
    }
    glutPostRedisplay();
}
// Routine to make the menu.
void makeMenu(void)
{
    // The sub-menu is created first (because it should be visible when the top
    // menu is created): its callback function is registered and menu entries added.
    int sub_menu;
    sub_menu = glutCreateMenu(view_menu);
    glutAddMenuEntry("TOP", 2);
    glutAddMenuEntry("NORMAL",4);

    // The top menu is created: its callback function is registered and menu entries,
    // including a submenu, added.
    glutCreateMenu(top_menu);
    glutAddSubMenu("View", sub_menu);
    glutAddMenuEntry("Quit",1);

    // The menu is attached to a mouse button.
    glutAttachMenu(GLUT_RIGHT_BUTTON);
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
        if (figure->isValidateMove(0,0,-1, &figures)){
            figure->moveZ(-1);
            glutPostRedisplay();
        }
    }
    if (key == GLUT_KEY_DOWN)
    {
        if (figure->isValidateMove(0,0,1, &figures)){
            figure->moveZ(1);
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
    if(key == GLUT_KEY_END){
        restartGame();
    }
}

void init(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    // Make menu.
    makeMenu();
}

int main(int argc, char **argv){
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