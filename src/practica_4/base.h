//
// Created by angel on 29/10/19.
//

#ifndef PRACTICAS_BASE_H
#define PRACTICAS_BASE_H

#include <cmath>

#define GL_PI 3.1415f

double bases[36][3]={
        {400,700,0}, //A
        {400,700,50}, //B

        {350,700,0}, //C
        {350,700,50}, //D

        {-400,700,0}, //E
        {-400,700,50}, //F

        {-350,700,0}, //G
        {-350,700,50}, //H

        {400,-200,0}, //A1
        {400,-200,50}, //B1

        {350,-200,0}, //C1
        {350,-200,50}, //D1

        {-400,-200,0}, //E1
        {-400,-200,50}, //F1

        {-350,-200,0}, //G1
        {-350,-200,50}, //H1

        {-400,0,0}, //I
        {-400,0,50},//N
        {-400,50,50},//O
        {-400,50,0},//P

        {400,0,0},//J
        {400,0,50},//K
        {400,50,50},//L
        {400,50,0},//M

        {-30,-60,0}, //Q
        {30,-60,0}, //R
        {-25,50,0}, //S
        {25,50,0}, // T

        {-30,-60,500}, //U
        {30,-60,500}, //V
        {-30,50,500}, //W
        {30,50,500}, //Z
        {-30,220,1000}, //L1
        {30,220,1000}, //J1
        {-30,110,1000}, //K1
        {30,110,1000} //L1
};

void DibujarBase1(){
    glBegin(GL_POLYGON);
    glVertex3dv(bases[0]);
    glVertex3dv(bases[1]);
    glVertex3dv(bases[3]);
    glVertex3dv(bases[2]);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3dv(bases[8]);
    glVertex3dv(bases[9]);
    glVertex3dv(bases[11]);
    glVertex3dv(bases[10]);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3dv(bases[11]);
    glVertex3dv(bases[9]);
    glVertex3dv(bases[1]);
    glVertex3dv(bases[3]);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3dv(bases[10]);
    glVertex3dv(bases[8]);
    glVertex3dv(bases[0]);
    glVertex3dv(bases[2]);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3dv(bases[9]);
    glVertex3dv(bases[1]);
    glVertex3dv(bases[0]);
    glVertex3dv(bases[8]);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3dv(bases[11]);
    glVertex3dv(bases[3]);
    glVertex3dv(bases[2]);
    glVertex3dv(bases[10]);
    glEnd();
}

void DibujarBase2(){
    glBegin(GL_POLYGON);
    glVertex3dv(bases[7]);
    glVertex3dv(bases[5]);
    glVertex3dv(bases[4]);
    glVertex3dv(bases[6]);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3dv(bases[15]);
    glVertex3dv(bases[13]);
    glVertex3dv(bases[12]);
    glVertex3dv(bases[14]);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3dv(bases[5]);
    glVertex3dv(bases[13]);
    glVertex3dv(bases[12]);
    glVertex3dv(bases[4]);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3dv(bases[7]);
    glVertex3dv(bases[15]);
    glVertex3dv(bases[14]);
    glVertex3dv(bases[6]);
    glEnd();
    //
    glBegin(GL_POLYGON);
    glVertex3dv(bases[4]);
    glVertex3dv(bases[12]);
    glVertex3dv(bases[14]);
    glVertex3dv(bases[6]);
    glEnd();
    //
    glBegin(GL_POLYGON);
    glVertex3dv(bases[5]);
    glVertex3dv(bases[13]);
    glVertex3dv(bases[15]);
    glVertex3dv(bases[7]);
    glEnd();
}

void DibujarBase3(){
    glBegin(GL_POLYGON);
    glVertex3dv(bases[17]);
    glVertex3dv(bases[18]);
    glVertex3dv(bases[22]);
    glVertex3dv(bases[21]);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3dv(bases[19]);
    glVertex3dv(bases[23]);
    glVertex3dv(bases[20]);
    glVertex3dv(bases[16]);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3dv(bases[17]);
    glVertex3dv(bases[21]);
    glVertex3dv(bases[20]);
    glVertex3dv(bases[16]);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3dv(bases[18]);
    glVertex3dv(bases[22]);
    glVertex3dv(bases[23]);
    glVertex3dv(bases[19]);
    glEnd();
}

void DibujarBase4(){
    glBegin(GL_POLYGON);
    glVertex3dv(bases[25]);
    glVertex3dv(bases[27]);
    glVertex3dv(bases[31]);
    glVertex3dv(bases[29]);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3dv(bases[27]);
    glVertex3dv(bases[26]);
    glVertex3dv(bases[30]);
    glVertex3dv(bases[31]);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3dv(bases[26]);
    glVertex3dv(bases[24]);
    glVertex3dv(bases[28]);
    glVertex3dv(bases[30]);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3dv(bases[24]);
    glVertex3dv(bases[25]);
    glVertex3dv(bases[29]);
    glVertex3dv(bases[28]);
    glEnd();
}

void DibujarBase5(){
    glBegin(GL_POLYGON);
    glVertex3dv(bases[32]);
    glVertex3dv(bases[34]);
    glVertex3dv(bases[35]);
    glVertex3dv(bases[33]);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3dv(bases[29]);
    glVertex3dv(bases[31]);
    glVertex3dv(bases[33]);
    glVertex3dv(bases[35]);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3dv(bases[34]);
    glVertex3dv(bases[33]);
    glVertex3dv(bases[28]);
    glVertex3dv(bases[30]);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3dv(bases[32]);
    glVertex3dv(bases[34]);
    glVertex3dv(bases[28]);
    glVertex3dv(bases[30]);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3dv(bases[33]);
    glVertex3dv(bases[32]);
    glVertex3dv(bases[30]);
    glVertex3dv(bases[31]);
    glEnd();
}

void DibujaCilindro (GLdouble X, GLdouble Y, GLfloat LADOS, GLdouble radio, bool mitad, GLdouble z)
{
    GLfloat angle;

    int Contador = 0;
    GLdouble auxRadio = radio;

    GLfloat Puntos1[40][3];
    GLfloat Puntos2[40][3];

    glBegin(GL_POLYGON);
    GLdouble auxZ =0;
    Contador = 0;
    //printf ("\n Puntos Primer Poligono ");
    for(angle = 0.0f; angle < ((!mitad)?2.0f*GL_PI:GL_PI); angle += ((!mitad)?2.0f*GL_PI:GL_PI)/LADOS)
    {
        Puntos1[Contador][0] = radio*sin(angle)+X;
        Puntos1[Contador][1] = radio*cos(angle)+Y;
        Puntos1[Contador][2] = auxZ;
        glVertex3fv(Puntos1[Contador]);
        Contador++;
    }
    glEnd();

    //printf ("\n Puntos Segundo Poligono ");
    glBegin(GL_POLYGON);
    Contador = 0;
    for(angle = 0.0f; angle < ((!mitad)?2.0f*GL_PI:GL_PI); angle += ((!mitad)?2.0f*GL_PI:GL_PI)/LADOS)
    {
        Puntos2[Contador][0] = auxRadio*sin(angle)+X;
        Puntos2[Contador][1] = auxRadio*cos(angle)+Y;
        Puntos2[Contador][2] = z;
        glVertex3fv(Puntos2[Contador]);
        Contador++;
    }
    glEnd();

    for (Contador = 0; Contador<LADOS; Contador++)
    {
        glBegin(GL_POLYGON);
//        glColor3f(1.0,1.0,1.0/(Contador+1));
        int Temporal = 0;
        if (Contador==(int) (LADOS-1))
            Temporal = 0;
        else
            Temporal = Contador+1;
        glVertex3fv(Puntos1[Contador]);
        glVertex3fv(Puntos1[Temporal]);
        glVertex3fv(Puntos2[Temporal]);
        glVertex3fv(Puntos2[Contador]);
        glEnd();
    }
}

#endif //PRACTICAS_BASE_H
