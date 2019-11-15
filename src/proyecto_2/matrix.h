//
// Created by angel on 14/11/19.
//

#ifndef PRACTICAS_MATRIX_H
#define PRACTICAS_MATRIX_H

/**
 * Matrix for rotate 90 grades on Z
 */
float matrizRotationZ[4][4] ={
        {0/*cos90*/,    -1/*-sen90*/,   0,0},
        {1/*sen90*/,    0 /*-cos90*/,   0,0},
        {0,             0,              1,0},
        {0,             0,              0,1}
};

/**
 * Matrix for rotate 90 grades on X
 */
float matrizRotationX[4][4] ={
        {1,             -1,             0,0},
        {1,             0/*cos90*/,     -1/*-sen90*/,0},
        {0,             1/*sen90*/,     0 /*-cos90*/,0},
        {0,             0,              0,1}
};

/**
 * Matrix for rotate 90 grades on X
 */
float matrizRotationY[4][4] ={
        {0/*cos90*/,    0,             1/*sen90*/,0},
        {0,             1,              0,0},
        {-1/*-sen90*/,  0,              0 /*cos90*/,0},
        {0,             0,              0,1}
};


void rotationX(float* values);
void rotationY(float *values);
void rotationZ(float *values);

void rotationX(float *values) {
    auto* newValues = new float[3];
    for (int i = 0; i < 3; ++i) {
        float acum = 0;
        for (int k = 0; k < 3; ++k) {
            acum+= matrizRotationX[i][k]*values[k];
        }
        newValues[i] = acum;
    }
    std::cout<<" "<<newValues[0]<<" "<<newValues[1]<<" "<<newValues[2]<<" "<<std::endl;
//    *values = *newValues;
}

void rotationY(float *values) {
    auto* newValues = new float[3];
    for (int i = 0; i < 3; ++i) {
        float acum = 0;
        for (int k = 0; k < 3; ++k) {
            acum+= matrizRotationY[i][k]*values[k];
            std::cout<<" "<<acum<<" ";
        }
        std::cout<<std::endl;
        newValues[i] = acum;
    }
//    *values = *newValues;
}

void rotationZ(float *values) {
    auto* newValues = new float[3];
    for (int i = 0; i < 3; ++i) {
        float acum = 0;
        for (int k = 0; k < 3; ++k) {
            acum+= matrizRotationZ[i][k]*values[k];
        }
        newValues[i] = acum;
    }
    //    *values = *newValues;
}

#endif //PRACTICAS_MATRIX_H
