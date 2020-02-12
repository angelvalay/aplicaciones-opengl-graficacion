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
        {1,             0,             0,0},
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


void rotationX(float *valueX,float *valueY, float *valueZ);
void rotationY(float *valueX,float *valueY, float *valueZ);
void rotationZ(float *valueX,float *valueY, float *valueZ);

void rotationX(float *valueX,float *valueY, float *valueZ) {
    float auxX = 0;
    auxX+= matrizRotationX[0][0]*(*valueX);
    auxX+= matrizRotationX[0][1]*(*valueY);
    auxX+= matrizRotationX[0][2]*(*valueZ);
    float auxY = 0;
    auxY+= matrizRotationX[1][0]*(*valueX);
    auxY+= matrizRotationX[1][1]*(*valueY);
    auxY+= matrizRotationX[1][2]*(*valueZ);
    float auxZ = 0;
    auxZ+= matrizRotationX[2][0]*(*valueX);
    auxZ+= matrizRotationX[2][1]*(*valueY);
    auxZ+= matrizRotationX[2][2]*(*valueZ);
    *valueX = auxX;
    *valueY = auxY;
    *valueZ = auxZ;
}

void rotationY(float *valueX,float *valueY, float *valueZ) {
    float auxX = 0;
    auxX+= matrizRotationY[0][0]*(*valueX);
    auxX+= matrizRotationY[0][1]*(*valueY);
    auxX+= matrizRotationY[0][2]*(*valueZ);
    float auxY = 0;
    auxY+= matrizRotationY[1][0]*(*valueX);
    auxY+= matrizRotationY[1][1]*(*valueY);
    auxY+= matrizRotationY[1][2]*(*valueZ);
    float auxZ = 0;
    auxZ+= matrizRotationY[2][0]*(*valueX);
    auxZ+= matrizRotationY[2][1]*(*valueY);
    auxZ+= matrizRotationY[2][2]*(*valueZ);
    *valueX = auxX;
    *valueY = auxY;
    *valueZ = auxZ;
}

void rotationZ(float *valueX,float *valueY, float *valueZ) {
    float auxX = 0;
    auxX+= matrizRotationZ[0][0]*(*valueX);
    auxX+= matrizRotationZ[0][1]*(*valueY);
    auxX+= matrizRotationZ[0][2]*(*valueZ);
    float auxY = 0;
    auxY+= matrizRotationZ[1][0]*(*valueX);
    auxY+= matrizRotationZ[1][1]*(*valueY);
    auxY+= matrizRotationZ[1][2]*(*valueZ);
    float auxZ = 0;
    auxZ+= matrizRotationZ[2][0]*(*valueX);
    auxZ+= matrizRotationZ[2][1]*(*valueY);
    auxZ+= matrizRotationZ[2][2]*(*valueZ);
    *valueX = auxX;
    *valueY = auxY;
    *valueZ = auxZ;
}

#endif //PRACTICAS_MATRIX_H
