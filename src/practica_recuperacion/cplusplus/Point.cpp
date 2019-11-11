//
// Created by angel on 10/11/19.
//

#include "Point.h"

Point::Point(float x, float y) {
    this->punto[0] = x;
    this->punto[1] = y;
    this->punto[2] = 0;
}

Point::Point(float x, float y, float z) {
    this->punto[0] = x;
    this->punto[1] = y;
    this->punto[2] = z;
}

float *Point::getPunto() const {
    return punto;
}


