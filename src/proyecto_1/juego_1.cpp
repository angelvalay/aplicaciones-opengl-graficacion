//
// Created by angel on 24/10/19.
//
#include <iostream>
#include <vector>
#include "../core/Librerias.h"
#include "utils.h"
#include "Pieza.cpp"
#include "base.h"

int matriz[NUM_SQUARES][NUM_SQUARES]{
    {1,1,0,0,2,2},
    {0,0,0,0,0,3},
    {-1,-1,0,0,0,3},
    {0,5,4,0,7,0},
    {0,5,4,8,7,0},
    {0,6,6,8,9,9}
};

std::vector<Pieza> piezas;

void obtenerPiezas(){
    for (auto & i : matriz) {
        for (int j = 0; j < NUM_SQUARES-1; ++j) {
            if(i[j] == i[j+1] && i[j]!=0){
                piezas.push_back(Pieza(&i[j], &i[j+1], i[j]));
                std::cout<<i[j]<<"-"<<i[j+1]<<"\n";
                j++;
            }
        }
    }
    for (int k = 0; k < NUM_SQUARES - 1; ++k) {
        for (int i = 0; i < NUM_SQUARES; ++i) {
            if(matriz[k][i] == matriz[k+1][i] && matriz[k][i]!=0){
                piezas.push_back(Pieza(&matriz[k][i], &matriz[k+1][i], matriz[k][i]));
                std::cout<<matriz[k][i]<<"-"<<matriz[k+1][i]<<"\n";
//                k++;
            }
        }
    }
}


using namespace std;

int main(int argc, char** argv)
{
    obtenerPiezas();
//    // Para generar las configuraciones iniciales de la ventana
//    generarPantalla(argc, argv,"Practica 1 | Grafica lineal");
//    // Funcion para dibujar en pantalla los graficos necesarios
//    glutDisplayFunc(dibujarPantalla);
//    // Funcion para redimensionar la pantalla
//    glutReshapeFunc(redimensionarPantalla);
//    // Funcion para iniciar la configuracion
//    iniciarConfiguracion();
    return 0;
}

