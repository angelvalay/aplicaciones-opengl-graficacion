#import <vector>
#include <iostream>
#include <map>
#include <cfloat>
#include <tgmath.h>

using namespace std;

#import "../core/Librerias.h"
#import "../core/Colores.h"
#import "../core/Estructuras.h"

struct Dato{
    std::string nombre;
    double valor;
};
vector<Dato> datos;

#import "Aplicacion.cpp"

int main(int argc, char **argv)
{
    datos.push_back(Dato{"1970",15});
    datos.push_back(Dato{"1980",30});
    datos.push_back(Dato{"1990",60});
    datos.push_back(Dato{"2000",120});
    datos.push_back(Dato{"2010",240});
    datos.push_back(Dato{"2014",300});
//    datos.push_back(Dato{"Siete",-87});
//    datos.push_back(Dato{"Ocho",-87});
//    datos.push_back(Dato{"Nueve",-8});
//    datos.push_back(Dato{"Diez",-80});

    generarPantalla(argc, argv,"Practica 1 | Grafica lineal");
    glutDisplayFunc(dibujarPantalla);
    glutReshapeFunc(redimensionarPantalla);
    glutKeyboardFunc(onKeyInput);
    activarFunciones();
    return 0;
}
