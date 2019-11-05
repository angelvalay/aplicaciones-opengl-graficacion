//
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

    void dibujar();

    int getNum() const;

    void setNum(int num);

    bool estaDentro(int x, int y);
};


#endif //PRACTICAS_PIEZA_H
