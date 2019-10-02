/**
 * IMPORTACION DE LIBRERIAS NATIVAS
 */
#import <vector>
#include <iostream>
#include <map>
#include <cfloat>
#include <fstream>
#include <sstream>
#include <cmath>

// USANDO LA ABREVIATURA DEL std::...
using namespace std;

/**
 * IMPORTACION DE ARCHIVOS NECESARIOS PARA LA EJECUCION DEL PROGRAMA
 */
#import "../core/Librerias.h"
#import "../core/Colores.h"
#import "../core/Estructuras.h"

/**
 * estructura para almacenar los datos necesarios para la grafica
 */
struct Dato{
    std::string nombre; // nombre del correspondiente dato de entrada
    double valor; // valor numerico
};

vector<Dato> datos; // Vector de tipo dato
string tituloX = "Valores X"; // titulo para la coordenada X
string tituloY = "Valores Y"; // titulo para la coordenada Y
string tituloVentana = "titulo"; // titulo para la grafica
vector<Punto> puntos; // conjunto de puntos de la grafica

#import "Aplicacion.cpp" //importar las demas funciones que se utilizaron

/**
 * Function para leer los datos de un archivo CSV
 * @return un vector de tipo dato que contiene los datos necesarios para mostrar la grafica
 */
vector<Dato> leer_csv(string nombre_archivo)
{
    vector<Dato> datos_csv; //Vector temporal para agregar los datos.
    fstream fin; // Archivo CSV

    int cont_col = 0; // contador de columnas
    int cont_fila = 0; // contador de filas

    fin.open(nombre_archivo,
            ios::in); // Para generar un enlace de tipo lectura al archivo

    string linea; // Sirve para guardar temporalmente cada linea del archivo

    /**
     * Ciclo para leer el archivo CSV
     */
    while (getline(fin,linea)) {
        string _primerdato; // para guardar el datos de la 1era columna
        double _segundodato = 0.0; // para guardar el datos de la 2da columna
        string palabra; // Para guardar temporalmente la palabra que valla extrayendo por fila

        //Creamos un stream para usar las funciones propias del objecto en lugar de manuparlo como un string
        stringstream linea_auxiliar(linea);

        /**
         * Ciclo para obtener los valores por columna de la fila
         * Solo es necesario obtener los primeros dos columnas
         */
        while (getline(linea_auxiliar, palabra, ',')) {
//            cout << palabra<<"\t";
            if (cont_col ==0) // si es la 1era columna
                if (!cont_fila) // si la fila de los datos es la primera es encabezado
                    tituloX = palabra; // se guarda como el titulo para el eje X
                else
                    _primerdato = palabra; // se guarda el dato el vector
            else
            if (cont_col == 1)// si es la 2da columna
                if (!cont_fila) // si la fila de los datos es la primera es encabezado
                    tituloY = palabra; // se guarda como el titulo para el eje Y
                else
                    _segundodato = atof(palabra.c_str()); // se guarda el dato el vector
            cont_col++; // se incrementa el contador para las columnas
        }
//        cout<<endl;
        cont_col = 0; // se reinicia el contador de las columnas cada que cambia de fila
        if (cont_fila) // si se registro una fila (no encabezado) al vector
            datos_csv.push_back(Dato{_primerdato,_segundodato}); // guardar los valores de las variables
        cont_fila ++; // incrementa el contador de filas
    }
    return datos_csv; // returna los datos del csv
}


int main(int argc, char **argv)
{
    // Se valida que exactamente tenga como entrada el archivo fuente de datos
    if (argc != 1){
        cerr<<"./app nombre_archivo.csv"<<endl;
        cerr<<"No se ingreso un archivo de entrada como argumento, intentenlo de nuevo"<<endl;
        exit(0);
    }
    //Llama a la funcion para obtener los datos con el argumento del archivo
    datos = leer_csv(argv[1]);
    //Se pide el titulo para la grafica
    cout<<"Ingrese un titulo para la grafica que sera mostrado en la aplicacion"<<endl;
    getline(cin,tituloVentana);

    // Para generar las configuraciones iniciales de la ventana
    generarPantalla(argc, argv,"Practica 1 | Grafica lineal");
    // Funcion para dibujar en pantalla los graficos necesarios
    glutDisplayFunc(dibujarPantalla);
    // Funcion para redimensionar la pantalla
    glutReshapeFunc(redimensionarPantalla);
    // Funcion para iniciar la configuracion
    iniciarConfiguracion();
    return 0;
}
