//
// Created by angel on 31/10/19.
//

#ifndef PRACTICAS_BASE_H
#define PRACTICAS_BASE_H

/**
 * Funcion para dibujar la tabla de juego
 */
void generarMesaDeJuego(){
    GLfloat filas[NUM_SQUARES][3] = {0};
    GLfloat columnas[NUM_SQUARES][3] = {0};

    for (int i = 0; i < NUM_SQUARES; ++i) {
        //
        filas[i][0] = -(float)SIZE/2;
        filas[i][1] = -(float)SIZE/2 + (float)(i)*((float)SIZE/NUM_SQUARES);
        filas[i][2] = 0;
        //
        columnas[i][0] = -(float)SIZE/2 + (float)(i)*((float)SIZE/NUM_SQUARES);
        columnas[i][1] = -(float)SIZE/2;
        columnas[i][2] = 0;
    }

    for (int j = 0; j < NUM_SQUARES; ++j) {
        glBegin(GL_LINES);
        glVertex3f(filas[j][0],filas[j][1],filas[j][2]);
        glVertex3f(filas[j][0]+SIZE,filas[j][1],filas[j][2]);
        glEnd();
    }

    for (int j = 0; j < NUM_SQUARES; ++j) {
        glBegin(GL_LINES);
        glVertex3f(columnas[j][0],columnas[j][1],columnas[j][2]);
        glVertex3f(columnas[j][0],columnas[j][1]+SIZE,columnas[j][2]);
        glEnd();
    }

}

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
 * Funcion para generar la estructura inicial de la pantalla
 * @param argc Numero de argumentos de la app
 * @param argv Array de los argumentos
 * @param titulo Cadena de texto del titulo
 */
void generarPantalla(int argc, char **argv, char* titulo) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(SIZE, SIZE);
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
    glOrtho(-((float)SIZE/2), (float)SIZE/2, -((float)SIZE/2), (float)SIZE/2, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/**
 * Funcion para iniciarlizar la configuracion del programa
 */
void iniciarConfiguracion() {
    glClearColor(1, 1, 1, 0.0);
    glutMainLoop();
}

/**
 * Funcion principal que permite dibujar los graficos
 */
void dibujarPantalla() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5,0.5,0.5);
    generarMesaDeJuego();
    glFlush();
}

#endif //PRACTICAS_BASE_H
