//
// Created by angel on 30/10/19.
//

#include "Pieza.h"

Pieza::Pieza(int pos1[2], int pos2[2], int num) {
    this->num = num;
    this->pos = new int*[2];
    this->pos[0] = pos1;
    this->pos[1] = pos2;
    if (this->pos[0][0] == this->pos[1][0]){
        this->orientacion = false;
    }else if (this->pos[0][1] == this->pos[1][1]){
        this->orientacion = true;
    }else
        exit(0);
//    std::cout<<this->orientacion<<std::endl;
    this->puntos[0][0] = -(float)SIZE/2 + (float)(this->pos[0][0])*((float)SIZE/NUM_SQUARES); //x1
    this->puntos[0][1] = -(float)SIZE/2 + (float)(this->pos[0][1])*((float)SIZE/NUM_SQUARES); //y1
    this->puntos[0][2] = 0;
}


GLdouble *Pieza::getPunto(int index) {
    return this->puntos[index];
}

int Pieza::getNum() const {
    return num;
}

void Pieza::setNum(int num) {
    Pieza::num = num;
}

void Pieza::dibujar() {
    glBegin(GL_POLYGON);
//    glPointSize(10.0);
    glColor3f(0.1 * this->num,0.1*this->num,0.1*this->num);
    if (this->orientacion){
        this->puntos[0][0]=-(float)SIZE/2 + (float)(this->pos[0][0])*((float)SIZE/NUM_SQUARES);
        this->puntos[0][1]=-(float)SIZE/2 + (float)(this->pos[0][1])*((float)SIZE/NUM_SQUARES);
        this->puntos[0][2]=0;
        this->puntos[1][0]=-(float)SIZE/2 + (float)(this->pos[1][0]+1)*((float)SIZE/NUM_SQUARES);
        this->puntos[1][1]=-(float)SIZE/2 + (float)(this->pos[1][1])*((float)SIZE/NUM_SQUARES);
        this->puntos[1][2]=0;
        this->puntos[2][0]=-(float)SIZE/2 + (float)(this->pos[1][0]+1)*((float)SIZE/NUM_SQUARES);
        this->puntos[2][1]=-(float)SIZE/2 + (float)(this->pos[1][1]+1)*((float)SIZE/NUM_SQUARES);
        this->puntos[2][2]=0;
        this->puntos[3][0]=-(float)SIZE/2 + (float)(this->pos[0][0])*((float)SIZE/NUM_SQUARES);
        this->puntos[3][1]=-(float)SIZE/2 + (float)(this->pos[0][1]+1)*((float)SIZE/NUM_SQUARES);
        this->puntos[3][2]=0;
    }else{
        this->puntos[0][0]=-(float)SIZE/2 + (float)(this->pos[0][0])*((float)SIZE/NUM_SQUARES);
        this->puntos[0][1]=-(float)SIZE/2 + (float)(this->pos[0][1])*((float)SIZE/NUM_SQUARES);
        this->puntos[0][2]=0;
        this->puntos[1][0]=-(float)SIZE/2 + (float)(this->pos[1][0])*((float)SIZE/NUM_SQUARES);
        this->puntos[1][1]=-(float)SIZE/2 + (float)(this->pos[1][1]+1)*((float)SIZE/NUM_SQUARES);
        this->puntos[1][2]=0;
        this->puntos[2][0]=-(float)SIZE/2 + (float)(this->pos[1][0]+1)*((float)SIZE/NUM_SQUARES);
        this->puntos[2][1]=-(float)SIZE/2 + (float)(this->pos[1][1]+1)*((float)SIZE/NUM_SQUARES);
        this->puntos[2][2]=0;
        this->puntos[3][0]=-(float)SIZE/2 + (float)(this->pos[0][0]+1)*((float)SIZE/NUM_SQUARES);
        this->puntos[3][1]=-(float)SIZE/2 + (float)(this->pos[0][1])*((float)SIZE/NUM_SQUARES);
        this->puntos[3][2]=0;
    }
    glVertex3dv(this->puntos[0]);
    glVertex3dv(this->puntos[1]);
    glVertex3dv(this->puntos[2]);
    glVertex3dv(this->puntos[3]);
    glEnd();
}


