/*  Program:  practica6
    Ana Cristina Martinez Hernandez

    Se uso la libreria openglut.h

    FUENTE: http://openglut.sourceforge.net/index.html
*/

#include<GL/glut.h>
#include <iostream>
#include "GL/freeglut.h"

using namespace std;
//LUZ
static GLfloat light0_position[] = {2.0, 8.0, 2.0, 0.0};
GLfloat light_diffuse[] = {1.0, 1.0, 1.0,1.0 };
GLfloat light_ambient[] = {0.0, 0.0, 0.0,1.0};
GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};

//1ER Material
GLfloat mat_ambient2[] ={ (float)191/256,   (float)127/256,  (float)95/256,   1.0};
GLfloat mat_diffuse2[] ={(float)191/256,   (float)127/256,  (float)95/256,   1.0};
GLfloat mat_specular2[] ={1.0, 1.0, 1.0, 1.0};
GLfloat mat_shininess2[]        = { 100};
//2DO Material
GLfloat mat_ambient[] ={ (float)240/256,   (float)131/256,  (float)128/256,   1.0};
GLfloat mat_diffuse[] ={(float)240/256,   (float)131/256,  (float)128/256,   1.0};
GLfloat mat_specular[] ={1.0, 1.0, 1.0, 1.0};
GLfloat mat_shininess[]        = { 100};
//3ER Material
GLfloat mat_ambient3[] ={ (float)152/256,   (float)172/256,  (float)154/256,   1.0};
GLfloat mat_diffuse3[] ={(float)152/256,   (float)172/256,  (float)154/256,   1.0};
GLfloat mat_specular3[] ={1.0, 1.0, 1.0, 1.0};
GLfloat mat_shininess3[]        = { 100};

//Estructura para almacenar las alturas de cada cilindro
struct heights{
    float h1=0.5; bool isUph1 = true; int conth1=20;
    float h2=0.5; bool isUph2 = true; int conth2=17;
    float h3=0.5; bool isUph3 = true; int conth3=14;
    float h4=0.5; bool isUph4 = true; int conth4=11;
    float h7=0.5; bool isUph7 = true; int conth7=8;
    float h6=0.5; bool isUph6 = true; int conth6=5;
    float h5=0.5; bool isUph5 = true; int conth5=2;
} heights;

static int animationPeriod = 20; // TIntervalo del tiempo

//FUncion que cambiar el valor de la altura de acuerdo a su incremento
void changeValue(float & h, bool & isUp, int & cont){
    if (isUp){
        h+=0.15;
        if (h>2.0)
            isUp = false;
    }else{
        if (h<0.3){
            if (cont >0){
                cont --;
            }else{
                cont = 20;
                isUp = true;
            }
        }else{
            h-=0.15;
        }
    }
}

//FUncion que cambia de material de acuerdo a la altura del cilindro
void changeMaterial(float &h){
    if(h<=1.0){
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient3);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular3);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess3);
    }else{
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    }
}

//FUncion inicilizador
void init () {
    glClearColor((float)152/256, (float)104/256, (float)99/256, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

//FUncion para dibujar las bases de cada cilindro
void displayBases(){
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess2);

    glPushMatrix();
    glTranslated(0,0,-4);
    glRotatef(90, 1.0, 0.0, 0.0);
    glScalef(1.5, 1.5, 1.5);
    glTranslatef(0,0,0.5);
    glutSolidCylinder(1.0,0.5,25,25);
    glPopMatrix();

    glPushMatrix();
    glTranslated(3.08,0,-2.56);
    glRotatef(90, 1.0, 0.0, 0.0);
    glScalef(1.5, 1.5, 1.5);
    glTranslatef(0,0,0.5);
    glutSolidCylinder(1.0,0.5,25,25);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-3.08,0,-2.56);
    glRotatef(90, 1.0, 0.0, 0.0);
    glScalef(1.5, 1.5, 1.5);
    glTranslatef(0,0,0.5);
    glutSolidCylinder(1.0,0.5,25,25);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-3.93,0,0.73);
    glRotatef(90, 1.0, 0.0, 0.0);
    glScalef(1.5, 1.5, 1.5);
    glTranslatef(0,0,0.5);
    glutSolidCylinder(1.0,0.5,25,25);
    glPopMatrix();

    glPushMatrix();
    glTranslated(3.93,0,0.64);
    glRotatef(90, 1.0, 0.0, 0.0);
    glScalef(1.5, 1.5, 1.5);
    glTranslatef(0,0,0.5);
    glutSolidCylinder(1.0,0.5,25,25);
    glPopMatrix();


    glPushMatrix();
    glTranslated(-1.96,0,3.49);
    glRotatef(90, 1.0, 0.0, 0.0);
    glScalef(1.5, 1.5, 1.5);
    glTranslatef(0,0,0.5);
    glutSolidCylinder(1.0,0.5,25,25);
    glPopMatrix();


    glPushMatrix();
    glTranslated(2,0,3.46);
    glRotatef(90, 1.0, 0.0, 0.0);
    glScalef(1.5, 1.5, 1.5);
    glTranslatef(0,0,0.5);
    glutSolidCylinder(1.0,0.5,25,25);
    glPopMatrix();
}

//FUncion para dibujar un cilindro
void drawCylinder(float &h, float x, float z){
    changeMaterial(h);
    glPushMatrix();
    glTranslated(x,0,z);
    glRotatef(90, 1.0, 0.0, 0.0);
    glScalef(1.5, 1.5, 1.5);
    glTranslatef(0,0,0.0 - h +0.5);
    //funcion de la libreria openglut.h
    glutSolidCylinder(0.8,h,25,25);
    glPopMatrix();
}

//Funcion del display para los cilindros que cambian de altura
void displayCilindros(){

    drawCylinder(heights.h1,0,-4);

    drawCylinder(heights.h2,-3.08,-2.56);

    drawCylinder(heights.h3,-3.93,0.73);

    drawCylinder(heights.h4,-1.96,3.49);

    drawCylinder(heights.h5,3.95,0.64);

    drawCylinder(heights.h6,2,3.46);

    drawCylinder(heights.h7,3.08,-2.56);


}

//Funcion del display
void display (void)
{ glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);


    glLoadIdentity();
    gluLookAt(-15, 15.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    displayBases();

    displayCilindros();

    glutSwapBuffers();

}

// Funcion del timer
void animate(int value)
{
    changeValue(heights.h1, heights.isUph1, heights.conth1);
    changeValue(heights.h2, heights.isUph2, heights.conth2);
    changeValue(heights.h3, heights.isUph3, heights.conth3);
    changeValue(heights.h4, heights.isUph4, heights.conth4);
    changeValue(heights.h5, heights.isUph5, heights.conth5);
    changeValue(heights.h6, heights.isUph6, heights.conth6);
    changeValue(heights.h7, heights.isUph7, heights.conth7);
    glutPostRedisplay();

    glutTimerFunc(animationPeriod, animate, 1);
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();	/*  define the projection  */
    gluPerspective(45.0, (GLfloat) w / (GLfloat) h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition (0, 0);
    glutInitWindowSize(400, 400);
    glutCreateWindow ("Practica 6");
    init();
    glutTimerFunc(0, animate, 0);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;

}

