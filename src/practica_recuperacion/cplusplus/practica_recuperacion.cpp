//
// Created by angel on 10/11/19.
//
// LIBRERIAS DEL OPEN GL Y DE ESTANDAR
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Point.cpp"
#include "Piece.cpp"
#include "getbmp.h"
float AlturaVentana = 375;
float AnchuraVentana = 1000;
#include "App.cpp"

// Globals.
static unsigned int texture[2]; // Array of texture ids.
static unsigned char chessboard[64][64][4]; // Storage for chessboard image.
static float angle = 0.0; // Angle to rotate textured square.
static int id = 0; // Currently displayed texture id.

/*
 *
 *
 * FUNCIONES DE LAS TEXTURAS
 *
 *
 */
// Load external textures.
void loadExternalTextures()
{
    // Local storage for bmp image data.
    BitMapFile *image[1];

    // Load the image.
    image[0] = getbmp("/home/angel/PycharmProjects/IntroGraficacion/upv.bmp");

    // Create texture object texture[0].
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    // Specify image data for currently active texture object.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->sizeX, image[0]->sizeY, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);

    // Set texture parameters for wrapping.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture parameters for filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}


// Routine to load a program-generated image as a texture.
void loadProceduralTextures()
{
    // Create texture object texture[1].
    glBindTexture(GL_TEXTURE_2D, texture[1]);

    // Specify image data for currently active texture object.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, chessboard);

    // Set texture parameters for wrapping.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture parameters for filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}


// Create 64 x 64 RGBA image of a chessboard.
void createChessboard(void)
{
    int i, j;
    for (i = 0; i < 64; i++)
        for (j = 0; j < 64; j++)
            if ( ( ((i/8)%2) && ((j/8)%2) ) || ( !((i/8)%2) && !((j/8)%2) ) )
            {
                chessboard[i][j][0] = 0x00;
                chessboard[i][j][1] = 0x00;
                chessboard[i][j][2] = 0x00;
                chessboard[i][j][3] = 0xFF;
            }
            else
            {
                chessboard[i][j][0] = 0xFF;
                chessboard[i][j][1] = 0xFF;
                chessboard[i][j][2] = 0xFF;
                chessboard[i][j][3] = 0xFF;
            }
}

// Initialization routine.
void setup(void) {
    glClearColor(0.8, 0.8, 0.8, 0.0);

    // Create texture ids.
    glGenTextures(2, texture);

    // Load external texture.
    loadExternalTextures();

    // Generate procedural texture.
    createChessboard();

    // Load procedural texture.
    loadProceduralTextures();

    // Specify how texture values combine with current surface color values.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // Turn on OpenGL texturing.
    glEnable(GL_TEXTURE_2D);
}
/*
 *
 *
 * FUNCIONES DE LA APLICACION
 *
 *
 */

std::vector<Piece> pieces;

void buildPieces(){
    for (float y = HEIGHT_FIG; y <=SIZE_FIG_HEIGHT ; y+=1.0) {
        for (float x = WIDTH_FIG; x < SIZE_FIG_WIDTH; x+=1.0) {
            pieces.emplace_back(Point(x,y));
        }
    }
}

void drawFiguraPrincipal(){
    glColor3f(0,0,0);
    //anadir finea  vertical
    glBegin(GL_LINES);
    glVertex3f(0, -40, 0);
    glVertex3f(0, 220, 0);
    glEnd();
    // generar cuadro izquierdo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    // anadir imagen original
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-220, 0, 0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-220, 160, 0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-20, 160, 0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-20, 0, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void drawPiecesFigure(){
//# anadir nombre de la figura original
//# generar cuadro derecho
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
//# anadir imagen original
    glBegin(GL_POLYGON);
    for(const Piece& piece: pieces){
        std::cout<<"hola"<<std::endl;
        const vector<Point>& points = piece.getPoints();
        const vector<Point>& pointsTexture = piece.getPointsTexture();
        for (int i = 0; i<points.size();i++){
            glTexCoord2f(pointsTexture.at(i).getPunto()[0], pointsTexture.at(i).getPunto()[1]);
            glVertex2f(points.at(i).getPunto()[0], points.at(i).getPunto()[1]);
        }
    }
    glEnd();
 glDisable(GL_TEXTURE_2D);
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
    glRasterPos3f(-180, -20, 0.0);
    escribirTextoBitMap(GLUT_BITMAP_8_BY_13, "Figura actual");
    glRasterPos3f(100, -20, 0.0);
    escribirTextoBitMap(GLUT_BITMAP_8_BY_13, "Rompecabezas");

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
    glOrtho(-250, 250, -40,200.00, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
/**
 * Funcion para iniciarlizar la configuracion del programa
 */
void iniciarConfiguracion() {
    glClearColor(1, 1, 1, 0);
    glutMainLoop();
}


/**
 * Funcion principal que permite dibujar los graficos
 */
void dibujarPantalla() {
    glClear(GL_COLOR_BUFFER_BIT);
    mostrarInfoPractica();
    drawFiguraPrincipal();
    drawPiecesFigure();
    glFlush();
}

int main(int argc, char **argv)
{
    buildPieces();
    // Para generar las configuraciones iniciales de la ventana
    generarPantalla(argc, argv,"Practica 1 | Grafica lineal");
    // Funcion para dibujar en pantalla los graficos necesarios
    glutDisplayFunc(dibujarPantalla);
    // Funcion para redimensionar la pantalla
    glutReshapeFunc(redimensionarPantalla);
    // Funcion para iniciar la configuracion
    setup();
    iniciarConfiguracion();
    return 0;
}
