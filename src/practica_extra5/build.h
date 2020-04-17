//
// Created by ana on 24/03/20.
//
#include <vector>
#include <math.h>

#define PI 3.14159265

//structura
struct pack {
    float p_x;
    float p_y;
    float p_z;
    float c_r;
    float c_g;
    float c_b;
    float t_x;
    float t_y;
};

// funcion para generar circulos
void gluCircle(std::vector<pack>* data, float r, float p_x, float p_y, float p_z){
    for (int i = 0; i < 360; ++i) {
        data->push_back(pack{
            (float)(cos(i*PI/180) * r) + p_x,
            p_y,
            (float)(sin(i*PI/180) * r) + p_z,
           1.0,
           1.0,
           1.0,
           (float)(cos(i*PI/180)),
            (float)(sin(i*PI/180))
        });
    }
}
//funcion para generar aros
void gluAro(std::vector<pack>* data, float rMax, float rMin,
        float p_x, float p_y, float p_z){

}
