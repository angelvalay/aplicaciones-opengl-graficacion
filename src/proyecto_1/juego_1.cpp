//
//
#include <iostream>
#include <vector>
#include "Librerias.h"
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

using namespace std;

int main(int argc, char** argv)
{
    // Para generar las configuraciones iniciales de la ventana
    generarPantalla(argc, argv,"Practica 1 | Grafica lineal");
    // Funcion para dibujar en pantalla los graficos necesarios
    glutDisplayFunc(dibujarPantalla);
    // Funcion para redimensionar la pantalla
    glutReshapeFunc(redimensionarPantalla);
    //Iniciar funcion del mouse
    glutMotionFunc(motion);
    //Funcion del motion
    glutMouseFunc(mouse);
    // Funcion para iniciar la configuracion
    iniciarConfiguracion();

    return 0;
}

