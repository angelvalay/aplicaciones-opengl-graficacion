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


