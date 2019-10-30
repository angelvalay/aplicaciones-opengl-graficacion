// LIBRERIAS DEL OPEN GL Y DE ESTANDAR
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>       /* for cos(), sin(), and sqrt() */
#include <GL/glut.h>    /* OpenGL Utility Toolkit header */
#include <iostream>
#include "base.h"

GLfloat angleY = 360.0;   /* in degrees */
GLfloat angleX = 280.0;   /* in degrees */
GLfloat angleZ = 160;
#define NEAR_Z 1.0
#define FAR_Z 5000.0	// For the frustum size.
#define SIZE 700
float zoom = -2500.0;
float turnUpDown = 0.0;
static int isAnimate = 0; // Animated?
static int upDown = 0; // Up 0 Down 1
static int animationPeriod = 100; // Time interval between fram

void drawScene(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
        glTranslatef(-0, -0, zoom);
        glRotatef(angleX, 1.0, 0.0,0.0);
        glRotatef(angleY, 0.0, 1.0,0.0);
        glRotatef(angleZ, 0.0, 0.0,1.0);
        glColor3f(0.2,0.2,0.2);
        DibujarBase1();
        DibujarBase2();
        DibujarBase3();
        glPushMatrix();
        glRotatef(267,0.0,0.0,1.0);
        DibujaCilindro(-10,0,30, 200, true,50);
    glPopMatrix();
    DibujarBase4();
    glPushMatrix();
        glTranslatef(0,0,300);
        glColor3f(0.4,0.4,0.4);
        DibujaCilindro(0,375,30,325,false,50);
        glPopMatrix();
        glColor3f(0.2,0.2,0.2);
    DibujarBase5();
    //
    glPushMatrix();
        glTranslatef(30,0,475);
        glRotatef(90,0,1,0);
        glColor3f(0.55,0.55,0.55);
        DibujaCilindro(-30,0,30,35,false,30);
        glColor3f(0.3,0.3,0.3);
        DibujaCilindro(-30,0,30,40,false,28);
    glPopMatrix();
    //
    glPushMatrix();
        glTranslatef(-30,0,475);
        glRotatef(-90,0,1,0);
        glColor3f(0.55,0.55,0.55);
        DibujaCilindro(30,0,30,35,false,30);
        glColor3f(0.3,0.3,0.3);
        DibujaCilindro(30,0,30,40,false,28);
    glPopMatrix();
    //
    glPushMatrix();
        glTranslatef(-30,0,975);
        glRotatef(-90,0,1,0);
        glColor3f(0.55,0.55,0.55);
        DibujaCilindro(30,165,30,48,false,30);
        glColor3f(0.3,0.3,0.3);
        DibujaCilindro(30,165,30,55,false,28);
    glPopMatrix();
    //
    glPushMatrix();
        glTranslatef(30,0,975);
        glRotatef(90,0,1,0);
        glColor3f(0.55,0.55,0.55);
        DibujaCilindro(-30,165,30,48,false,30);
        glColor3f(0.3,0.3,0.3);
        DibujaCilindro(-30,165,30,55,false,28);
    glPopMatrix();

    //DIBUJAR LENTE PARA ROTAR
    glPushMatrix();
        glTranslatef(-30,165,975);
        glRotatef(turnUpDown,1,0,0);
        glTranslatef(30,-165,-275);
        glColor3f(0.6,0.6,0.6);
        DibujaCilindro(0,375,30,120,false,20);
        glTranslatef(0,0,-20);
        glColor3f(0.55,0.55,0.55);
        DibujaCilindro(0,375,30,110,false,20);
        glTranslatef(0,0,40);
        glColor3f(0.5,0.5,0.5);
        DibujaCilindro(0,300,30,30,false,330);
        glPushMatrix();
            glScalef(1,0.35,1);
            glTranslatef(0,400,270);
            glRotatef(-90,1,0,0);
            glColor3f(0.5,0.5,0.5);
            DibujarBase4();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,0,-110);
            glColor3f(0.7,0.7,0.7);
            DibujaCilindro(0,300,30,30,false,100);
            glPushMatrix();
                glTranslatef(0,0,-20);
                glColor3f(0.7,0.7,0.7);
                DibujaCilindro(0,300,20,20,false,20);
            glPopMatrix();
            glTranslatef(70,80,0);
            glColor3f(0.7,0.7,0.7);
            DibujaCilindro(0,300,30,30,false,100);
            glPushMatrix();
                glTranslatef(0,0,-20);
                glColor3f(0.7,0.7,0.7);
                DibujaCilindro(0,300,20,20,false,20);
            glPopMatrix();
            glTranslatef(-140,0,0);
            glColor3f(0.7,0.7,0.7);
            DibujaCilindro(0,300,30,30,false,100);
            glPushMatrix();
                glTranslatef(0,0,-20);
                glColor3f(0.7,0.7,0.7);
                DibujaCilindro(0,300,20,20,false,20);
            glPopMatrix();
        glPopMatrix();
        glTranslatef(0,0,330);
        glColor3f(0.4,0.4,0.4);
        DibujaCilindro(0,300,30,35,false,30);
        glTranslatef(0,0,20);
        glColor3f(0.6,0.6,0.6);
        DibujaCilindro(0,300,30,30,false,20);
        glTranslatef(0,0,20);
        glColor3f(0.6,0.6,0.6);
        DibujaCilindro(0,300,30,20,false,50);
        glTranslatef(0,0,50);
        glColor3f(0.4,0.4,0.4);
        DibujaCilindro(0,300,30,25,false,10);
    glPopMatrix();
    glutSwapBuffers();
}

// Timer function.
void animate(int value)
{
    if (isAnimate)
    {
        if (upDown){
            turnUpDown += 5.0;
        }else{
            turnUpDown -= 5.0;
        }

        if (turnUpDown >= 160.0) upDown = false;
        if (turnUpDown <= -20) upDown = true;

        glutPostRedisplay();
        glutTimerFunc(animationPeriod, animate, 1);
    }
}

// Initialization routine.
void setup(void)
{
    glEnable(GL_DEPTH_TEST);
    glClearColor((float)119/254,(float)136/254,(float)153/254, 0.0);
}

void key(unsigned char c, int x, int y)
{
    if (c == 'u'){
//        std::cout<<"turn: "<<turnUpDown<<std::endl;
        if(turnUpDown < 160)
            turnUpDown+=10.0;
    }
    if (c == 'U'){
//        std::cout<<"turn: "<<turnUpDown<<std::endl;
        if(turnUpDown >-20)
        turnUpDown-=10.0;
    }
    if (c == '+'){
//        std::cout<<"zoom: "<<zoom<<std::endl;
        zoom+=10.0;
    }if (c == '-'){
//        std::cout<<"zoom: "<<zoom<<std::endl;
        zoom-=10.0;
    }if (c == 'x'){
//        std::cout<<"angle x"<<angleX<<std::endl;
        angleX += 10.0;
        if (angleX>360)
            angleX =10;
    } if (c == 'y'){
//        std::cout<<"angle y"<<angleY<<std::endl;
        angleY += 10.0;
        if (angleY>360)
            angleY =10;
    } if (c == 'z'){
//        std::cout<<"angle z"<<angleZ<<std::endl;
        angleZ += 10.0;
        if (angleZ>360)
            angleZ =10;
    } if (c == 'X'){
//        std::cout<<"angle x"<<angleX<<std::endl;
        angleX -= 10.0;
        if (angleX<0)
            angleX=360;
    } if (c == 'Y'){
//        std::cout<<"angle y"<<angleY<<std::endl;
        angleY -= 10.0;
        if (angleY<0)
            angleY=360;
    } if (c == 'Z'){
//        std::cout<<"angle z"<<angleZ<<std::endl;
        angleZ -= 10.0;
        if (angleZ<0)
            angleZ=360;
    } if (c == 27) {
        exit(0);
    }
    if(c == ' '){
        if (isAnimate) isAnimate = 0;
        else
        {
            isAnimate = 1;
            animate(1);
        }
    }

    glutPostRedisplay();
}

void reshape(int w, int h)
{
    glViewport(0, -150, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, w/h, NEAR_Z, FAR_Z);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE);
    glutInitWindowSize(SIZE, SIZE);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Shadowy Leapin' Lizards");
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(key);
    glutReshapeFunc(reshape);
    setup();
    glutMainLoop();
    return 0;
}
