//
// Created by angel on 30/10/19.
//

#ifndef PRACTICAS_PIEZA_H
#define PRACTICAS_PIEZA_H


class Pieza {
private:
    int num;
    bool orientacion; //false->parado true->acostado
    GLdouble puntos[4][3]={0};
    int** pos;
public:
    Pieza(int pos1[2], int pos2[2], int num);
    GLdouble* getPunto(int index);

    int getNum() const;

    void setNum(int num);
};


#endif //PRACTICAS_PIEZA_H
