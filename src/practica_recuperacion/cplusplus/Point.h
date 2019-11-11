//
// Created by angel on 10/11/19.
//

#ifndef PRACTICAS_POINT_H
#define PRACTICAS_POINT_H


#define WIDTH_FIG 200
#define HEIGHT_FIG 160

//dimensiones de las piezas
float SIZE_FIG_WIDTH = WIDTH_FIG/5;
float SIZE_FIG_HEIGHT = HEIGHT_FIG/4;


class Point {
private:
    float *punto;
public:
    Point(float x, float y);
    Point(float x, float y, float z);
    float *getPunto() const;
};


#endif //PRACTICAS_POINT_H
