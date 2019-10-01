//
// Created by angel on 27/09/19.
//

#define AlturaVentana 700 // Defino la altura predeterminada de la pantalla
#define AnchuraVentana 1000 // Defino la anchura predeterminada de la pantalla

#define UMBRAL 0.00000001 //Umbral necesaria para determinar la separacion de lineas

double colVen = AnchuraVentana / (24); // Valor de los pixeles que contiene cada columna
double filaVen = AlturaVentana /(16); // Pixeles que contiene cada fila

/**
 * Funcion para escribir texto como si fuera un conjunto de lineas
 * @param font Tipo de fuente
 * @param string Cadena de texto que se quiere mostrar
 */
void escribirTexto(void *font, char *string)
{
    char *c;
    for (c = string; *c != '\0'; c++) glutStrokeCharacter(font, *c);
}
/**
 * Funcion para escribir texto bitmap
 * @param font Tipo de fuente
 * @param string Cadena de texto que se quiere mostrar
 */
void escribirTextoBitMap(void *font, char *string)
{
    char *c;
    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void mostrarInfoPractica(){
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos3f(18*colVen, 1.8*filaVen, 0.0);
    escribirTextoBitMap(GLUT_BITMAP_8_BY_13, "Angel Armando Valay Martinez");
    glRasterPos3f(18*colVen, 1.4*filaVen, 0.0);
    escribirTextoBitMap(GLUT_BITMAP_8_BY_13, "1730322");
    glRasterPos3f(18*colVen, 1.0*filaVen, 0.0);
    escribirTextoBitMap(GLUT_BITMAP_8_BY_13, "INTRODUCCION A LA GRAFICACION ");
    glRasterPos3f(18*colVen, 0.6*filaVen, 0.0);
    escribirTextoBitMap(GLUT_BITMAP_8_BY_13, "POR COMPUTADORA");
}

/**
 * Funcion para generar la estructura inicial de la pantalla
 * @param argc Numero de argumentos de la app
 * @param argv Array de los argumentos
 * @param titulo Cadena de texto del titulo
 */
void generarPantalla(int argc, char **argv, char* titulo) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(AnchuraVentana, AlturaVentana);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(titulo);
}
/**
 * Funcion para redimensionar la pantalla
 * @param width Anchura predeterminada
 * @param height Altura predeterminada
 */
void redimensionarPantalla(int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, AnchuraVentana, 0.0, AlturaVentana, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
/**
 * Funcion para iniciarlizar la configuracion del programa
 */
void iniciarConfiguracion() {
    glClearColor(COLOR_BLANCO.Rojo, COLOR_BLANCO.Verde, COLOR_BLANCO.Azul, 0.0);
    glutMainLoop();
}

/**
 * Funcion para generar puntos en la grafica
 * @param puntos COnjunto de puntos para generar
 */
void generarPuntos(vector<Punto>& puntos){
    glColor3f(COLOR_ROJO.Rojo, COLOR_ROJO.Verde, COLOR_ROJO.Azul);
    glPointSize(5);
    glBegin(GL_POINTS);
        for (Punto & punto : puntos){
            glVertex3f(punto.x, punto.y, punto.z);
        }
    glEnd();
    glEnable(GL_PROGRAM_POINT_SIZE_EXT); // permite reiniciar el tamano del punto
    glPointSize(1);
}
/**
 * Funcion para generar el cuadro de la grafica lineal en donde se
 * contendra la grafica lineal de acuerdo a los datos obtenidos
 */
void generarCuadro(){
    glColor3f(0.7, 0.7, 0.7);
    //cuadro de la grafica
    glBegin(GL_POLYGON);
        glVertex3f(3*colVen, 3*filaVen, 0.0);
        glVertex3f(24*colVen, 3*filaVen, 0.0);
        glVertex3f(24*colVen, 15*filaVen, 0.0);
        glVertex3f(3*colVen, 15*filaVen, 0.0);
    glEnd();
}
/**
 * FUncion para generar las lineas que enmarcan el cuadro de la grafica
 */
void generarLineas(){
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINE_LOOP);
        glVertex3f(3*colVen, 3*filaVen, 0.0);
        glVertex3f(24*colVen, 3*filaVen, 0.0);
        glVertex3f(24*colVen, 15*filaVen, 0.0);
        glVertex3f(3*colVen, 15*filaVen, 0.0);
    glEnd();

}
/**
 * Funcion para generar las lineas punteadas sobre el eje Y
 * @param min Valor minimo que contiene la grafica
 * @param max VAlor maximo que contiene la grafica
 * @param umbral La diferencia que existe entre cada linea que sera dibujada
 * @param dif Valor diferencial entre el maximo y minimo
 */
void generarLineasYGrafico(double min, double max, double umbral, double dif){
    double difFila = 12/dif;
    double contFila = 0;
    glColor3f(0.5, 0.5, 0.5);
    //Aqui se empiezan a dibujar las lineas punteadas
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
    glBegin(GL_LINES);
        for (double i = min; i < max;) {
            if(fmod(i,umbral) == 0) {
                glVertex3f(3*colVen, 3*filaVen + (contFila*difFila*filaVen), 0.0);
                glVertex3f(24*colVen, 3*filaVen + (contFila*difFila*filaVen), 0.0);
            }
            i+=1;
            contFila++;
        }
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    contFila = 0;
    glColor3f(0.0, 0.0, 0.0);
    //Aqui se empieza a anadir el texto que representa el valor de cada linea punteada
    for (double i = min; i < max;) {
        if(fmod(i,umbral) == 0) {
            glRasterPos3f(2*colVen, 3*filaVen + (contFila*difFila*filaVen), 0.0);
            char* string = const_cast<char *>(to_string((int)i).c_str());
            escribirTextoBitMap(GLUT_BITMAP_8_BY_13, string);
        }
        i+=1;
        contFila++;
    }
}
/**
 * Funcion para generar los puntos y lineas de la grafica lineal y texto en el eje X
 * @param min Valor minimo en funcion para el eje Y
 * @param max Valor maximo en funcion para el eje Y
 * @param size Cantidad de puntos que se agregaran a la grafica
 */
void generarPuntosGrafico(double min, double max, int size){
    double difFila = 12/(max-min);
    double contFila = 0;
    double difCol = 21.00/(size+1);
    int contCol = 1;
    glColor3f(0.0, 0.0, 0.0);
    //Aqui empieza la generacion de texto en el eje X
    for (int i = 0; i < size; ++i) {
        glRasterPos3f(3*colVen + (contCol*difCol*colVen), 2.5*filaVen , 0.0);
        char* string = const_cast<char *>(datos[i].nombre.c_str());
        escribirTextoBitMap(GLUT_BITMAP_8_BY_13, string);
        contCol++;
    }
    contCol = 1;
    glColor3f(COLOR_ROJO.Rojo, COLOR_ROJO.Verde, COLOR_ROJO.Azul);
    // AQui empieza la generacion de lineas para la grafica lineal
    glBegin(GL_LINE_STRIP);
    for (Dato & dato : datos){
        contFila = 0;
        for (double j = min; j < max;) {
            if(j == dato.valor){
                glVertex3f(3*colVen + (contCol*difCol*colVen), 3*filaVen + (contFila*difFila*filaVen), 0.0);
                //AQui se van guardando los puntos que se van generando al vector puntos
                puntos.push_back(Punto{
                        3*colVen + (contCol*difCol*colVen),
                        3*filaVen + (contFila*difFila*filaVen)
                });
            }
            contFila ++;
            j+=1;
        }
        contCol++;

    }
    glEnd();
}
/**
 * FUncion para la generacion de los texto del EJe X, Y y el titulo.
 */
void generarTextosPrimarios(){
    glColor3f(0.0, 0.0, 0.0);
    // Texto titulo
    glRasterPos3f(7*colVen , 15.5*filaVen , 0.0);
    char* string = const_cast<char *>(tituloVentana.c_str());
    escribirTextoBitMap(GLUT_BITMAP_TIMES_ROMAN_24, string);

    //Texto Y
    glPushMatrix();
        glTranslatef(colVen, 7*filaVen, 0.0);
        glRotatef(90.0, 0.0, 0.0, 1.0);
        glScalef(10/colVen, 10/filaVen, 0.001);
        escribirTexto(GLUT_STROKE_ROMAN, const_cast<char *>(tituloY.c_str()));
    glPopMatrix();
    //Texto X
    glPushMatrix();
    glTranslatef(7*colVen, filaVen, 0.0);
    glRotatef(0.0, 0.0, 0.0, 1.0);
    glScalef(10/colVen, 10/filaVen, 0.001);
    escribirTexto(GLUT_STROKE_ROMAN, const_cast<char *>(tituloX.c_str()));
    glPopMatrix();
}
/**
 * FUncion para generar el cuerpo de la grafica lineal
 */
void generarGrafica(){
    // datos para la grafica
    double minValor = DBL_MAX;
    double maxValor = DBL_MIN;
    double diferencia = 0;
    int contador = 0;

    // para obtener el maximo y minimo
    for(Dato& val:datos){
        if(val.valor < minValor)
            minValor = val.valor;
        if (val.valor > maxValor)
            maxValor = val.valor;
        contador++;
    }
    // se guarda la diferencia que existe entre los extremos
    diferencia = maxValor - minValor;
    diferencia = (diferencia<0)?((-1)*diferencia):diferencia;
    // con estos calculos se permite dar un valor aproximado sobre
    // cuanta separacion tendran las lineas punteadas
    double umbral = UMBRAL;
    long int dec = 0;
    do{
        dec = diferencia / umbral;
        if((dec/10) <= 1)
            break;
        umbral*=10;
    }while(true);
    // Llamar a la funcion para generar las lineas punteadas y textos en el EJE Y
    generarLineasYGrafico(minValor-umbral,
            maxValor+umbral,umbral,diferencia+(umbral*2));
    // llamar a la funcion para generar las lineas y datos en el eje X
    generarPuntosGrafico(minValor-umbral,maxValor+umbral, contador);
}

/**
 * Funcion principal que permite dibujar los graficos
 */
void dibujarPantalla() {
    glClear(GL_COLOR_BUFFER_BIT);
    generarCuadro();
    generarLineas();
    generarTextosPrimarios();
    generarGrafica();
    generarPuntos(puntos);
    mostrarInfoPractica();
    glFlush();
}

