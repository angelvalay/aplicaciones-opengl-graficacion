//
// Created by angel on 24/10/19.
//
#include <stdio.h>
#include <GL/glut.h>
#include <vector>
#include <iostream>

#define AlturaVentana 700
#define AnchuraVentana 700

using namespace std;

int i = 0;

class Figuras {
public:
    Figuras(float x1, float x2, float y1, float y2, bool acos){
        xVal1 = x1;
        xVal2 = x2;
        yVal1 = y1;
        yVal2 = y2;
        acostado = acos;
    }
    Figuras();

    float getX1();
    float getX2();
    float getY1();
    float getY2();
private:
    float xVal1, xVal2, yVal1, yVal2;
    bool acostado;

};

float Figuras::getX1(){
    return xVal1;
}

float Figuras::getX2(){
    return xVal2;
}

float Figuras::getY1(){
    return yVal1;
}

float Figuras::getY2(){
    return yVal2;
}

std::vector<Figuras> fig;

void mouseControl(int button, int state, int x, int y) {
    bool xActive, yActive;
    float newX = 0, newY = 0;
    int i = 0;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (x < AnchuraVentana / 2) {
            newX = (float)(AnchuraVentana / 2 - x) / (-AnchuraVentana / 2);
        } else {
            newX = (float)(x - 350) / (AnchuraVentana / 2);
        }

        if (y < AlturaVentana / 2) {
            newY = (float)(AlturaVentana / 2 - y) / (AlturaVentana / 2);
        } else {
            newY = (float)(y - 350) / (-AlturaVentana / 2);
        }

        while ((xActive == false || yActive == false) && i < fig.size()) {
            xActive = false;
            yActive = false;
            if (fig[i].getX1() < newX && fig[i].getX2() > newX) {
                xActive = true;
            }

            if (fig[i].getY1() > newY && fig[i].getY2() < newY) {
                yActive = true;
            }
            i++;
        }

        if (xActive && yActive) {
            cout << x << endl;
            cout << y << endl;
            cout << "Entro" << endl;
        }
    }
}

void Funcionx(float distancia){
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0, 1.0);
    glVertex2f(-0.20, 1.0);
    glVertex2f(-0.20, 0.60);
    glVertex2f(-1.0, 0.60);
    glEnd();

    fig.push_back(Figuras(-1.0f, -0.2f, 1.0f, 0.6f, true));

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0, 0.60);
    glVertex2f(-0.20, 0.60);
    glVertex2f(-0.20, 0.20);
    glVertex2f(-1.0, 0.20);
    glEnd();

    fig.push_back(Figuras(-1.0f, -0.2f, 0.6f, 0.2f, true));

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0, 0.20);
    glVertex2f(-0.20, 0.20);
    glVertex2f(-0.20, -0.20);
    glVertex2f(-1.0, -0.20);
    glEnd();

    fig.push_back(Figuras(-1.0f, -0.2f, 0.2f, -0.2f, true));

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0, -0.20);
    glVertex2f(-0.20, -0.20);
    glVertex2f(-0.20, -0.60);
    glVertex2f(-1.0, -0.60);
    glEnd();

    fig.push_back(Figuras(-1.0f, -0.2f, -0.2f, -0.6f, true));

    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0, -0.60);
    glVertex2f(-0.20, -0.60);
    glVertex2f(-0.20, -1.0);
    glVertex2f(-1.0, -1.0);
    glEnd();

    fig.push_back(Figuras(-1.0f, -0.2f, -0.6f, -1.0f, true));

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(0.60, 1.0);
    glVertex2f(1.0, 1.0);
    glVertex2f(1.0, 0.2);
    glVertex2f(0.60, 0.2);
    glEnd();


    fig.push_back(Figuras(0.6f, 1.0f, 1.0f, 0.2f, true));

    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.20, 1.0);
    glVertex2f(0.60, 1.0);
    glVertex2f(0.60, 0.6);
    glVertex2f(-0.20, 0.6);
    glEnd();

    fig.push_back(Figuras(-0.2f, 0.6f, 1.0f, 0.6f, true));
}

void displayMe(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    Funcionx(0.5);
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(AnchuraVentana, AlturaVentana);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hola mundo en OpenGL Python");
    glutDisplayFunc(displayMe);
    glutMouseFunc(mouseControl);

    glutMainLoop();
    return 0;
}

