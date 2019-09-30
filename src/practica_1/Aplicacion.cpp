//
// Created by angel on 27/09/19.
//

#define AlturaVentana 700
#define AnchuraVentana 1000

#define UMBRAL 0.00000001

double colVen = AnchuraVentana / (24);
double filaVen = AlturaVentana /(16);


// Routine to draw a stroke character string.
void escribirTexto(void *font, char *string)
{
    char *c;
    for (c = string; *c != '\0'; c++) glutStrokeCharacter(font, *c);
}
void writeBitmapString(void *font, char *string)
{
    char *c;
    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void generarPantalla(int argc, char **argv, char* titulo) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(AnchuraVentana, AlturaVentana);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(titulo);
}
void redimensionarPantalla(int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, AnchuraVentana, 0.0, AlturaVentana, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void onKeyInput(unsigned char key, int x, int y) {
    switch(key)
    {
        default:
            break;
    }
}
void activarFunciones() {
    glClearColor(COLOR_BLANCO.Rojo, COLOR_BLANCO.Verde, COLOR_BLANCO.Azul, 0.0);
    glutMainLoop();
}

/**
 * FUNCIONES PARA LA PRACTICA
 */
void generarPuntos(std::vector<Punto> puntos){
    glColor3f(COLOR_ROJO.Rojo, COLOR_ROJO.Verde, COLOR_ROJO.Azul);
    glPointSize(5);
    glBegin(GL_POINTS);
        for (auto i = puntos.begin(); i != puntos.end(); ++i){
            cout<<(*i).x <<" "<<(*i).y<< " "<<(*i).z << " "<<endl;
            glVertex3f((*i).x, (*i).y, (*i).z);
        }
    glEnd();
}

void generarCuadro(){
    glColor3f(0.7, 0.7, 0.7);
    //cuadro de la grafica
    glBegin(GL_POLYGON);
        glVertex3f(3*colVen, 3*filaVen, 0.0);
        glVertex3f(24*colVen, 3*filaVen, 0.0);
        glVertex3f(24*colVen, 16*filaVen, 0.0);
        glVertex3f(3*colVen, 16*filaVen, 0.0);
    glEnd();
}

void generarLineas(){
    glColor3f(0.5, 0.5, 0.5);
//    glPointSize(100.0);
//    glBegin(GL_LINES);
//     glBegin(GL_LINE_STRIP);

    glBegin(GL_LINE_LOOP);
        glVertex3f(3*colVen, 3*filaVen, 0.0);
        glVertex3f(24*colVen, 3*filaVen, 0.0);
        glVertex3f(24*colVen, 16*filaVen, 0.0);
        glVertex3f(3*colVen, 16*filaVen, 0.0);
    glEnd();

}

void generarLineasYGrafico(double min, double max, double umbral, double dif){
    double difFila = 13/dif;
    double contFila = 0;
//    cout<<difCol*filaVen<<" "<<dif<<endl;
    glColor3f(0.5, 0.5, 0.5);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
    glBegin(GL_LINES);
        for (double i = min; i < max;) {
            if(fmod(i,umbral) == 0) {
//                cout<<"\t"<<i<<"\t";
//                cout<<contCol<<" "<<contCol*difCol<<endl;
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
    for (double i = min; i < max;) {
        if(fmod(i,umbral) == 0) {
//                cout<<"\t"<<i<<"\t";
//                cout<<contCol<<" "<<contCol*difCol<<endl;
            glRasterPos3f(2*colVen, 3*filaVen + (contFila*difFila*filaVen), 0.0);
            char* string = const_cast<char *>(to_string((int)i).c_str());
            writeBitmapString(GLUT_BITMAP_8_BY_13, string);
        }
        i+=1;
        contFila++;
    }
}

void generarPuntosGrafico(double min, double max){
//    cout<<datos.size()<<endl;
    double difFila = 13/(max-min);
    double contFila = 0;
    double difCol = 21/(datos.size());
    cout<<difCol*colVen<<" "<<datos.size()+1<<endl;
    int contCol = 1;
    glColor3f(0.0, 0.0, 0.0);
    for(Dato& val:datos){
        cout<<contCol<<endl;
        glRasterPos3f(3*colVen + (contCol*difCol*colVen), 2.5*filaVen , 0.0);
        char* string = const_cast<char *>(val.nombre.c_str());
        writeBitmapString(GLUT_BITMAP_8_BY_13, string);
        contCol++;
    }
    contCol = 1;
    glColor3f(COLOR_ROJO.Rojo, COLOR_ROJO.Verde, COLOR_ROJO.Azul);
    glBegin(GL_LINE_STRIP);
    for (auto & dato : datos){
        contFila = 0;
        for (double j = min; j < max;) {
            if(j == dato.valor){
                glVertex3f(3*colVen + (contCol*difCol*colVen), 3*filaVen + (contFila*difFila*filaVen), 0.0);
//                glVertex3f(3*colVen + (contCol*difCol*colVen), 5*filaVen, 0.0);
            }
            contFila ++;
            j+=1;
        }

        contCol++;

    }
    glEnd();
}

void generarTextosPrimarios(){
    glColor3f(0.0, 0.0, 0.0);
    //Texto Y
    glPushMatrix();
        glTranslatef(colVen, 7*filaVen, 0.0);
        glRotatef(90.0, 0.0, 0.0, 1.0);
        glScalef(10/colVen, 10/filaVen, 0.001);
        escribirTexto(GLUT_STROKE_ROMAN, "TITULO Y");
    glPopMatrix();
    //Texto X
    glPushMatrix();
    glTranslatef(7*colVen, filaVen, 0.0);
    glRotatef(0.0, 0.0, 0.0, 1.0);
    glScalef(10/colVen, 10/filaVen, 0.001);
    escribirTexto(GLUT_STROKE_ROMAN, "TITULO X");
    glPopMatrix();
}

//Para agregar los textos de acuerdo a los datos que hay.
void generarDescripcionGrafica(){
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
    diferencia = maxValor - minValor;
    diferencia = (diferencia<0)?((-1)*diferencia):diferencia;
//    cout<<" "<<minValor <<" "<<maxValor <<" "<<diferencia<<" "<<contador<<endl;
    double umbral = UMBRAL;
    long int dec = 0;
    do{
        dec = diferencia / umbral;
        if((dec/10) <= 1)
            break;
        umbral*=10;
    }while(true);

    generarLineasYGrafico(minValor-umbral,
            maxValor+umbral,umbral,diferencia+(umbral*2));
    generarPuntosGrafico(minValor-umbral,maxValor+umbral);
}

void dibujarPantalla() {
    glClear(GL_COLOR_BUFFER_BIT);

    generarCuadro();
    generarLineas();
    generarTextosPrimarios();
    generarDescripcionGrafica();

    glFlush();
}

