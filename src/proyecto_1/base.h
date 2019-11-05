//
//

#ifndef PRACTICAS_BASE_H
#define PRACTICAS_BASE_H

static std::vector<Pieza> piezas;
/**
 * FUncion para dectectar el mouse
 */
int moving;

int startx;

int starty;

/* ARGSUSED2 */
static void
mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            moving = 1;
            startx = x;
            starty = y;
            std::cout<<200-startx<<" "<<220-starty<<std::endl;
            for (auto & pieza : piezas) {
                if (pieza.estaDentro(200-startx,220-starty))
                    std::cout<<"dentro "<<pieza.getNum()<<std::endl;
            }
        }
        if (state == GLUT_UP) {
            moving = 0;
        }
    }
}

/* ARGSUSED1 */
static void
motion(int x, int y)
{
    if (moving) {
        startx = x;
        starty = y;
//        std::cout<<200-startx<<" "<<220-starty<<std::endl;
//        glutPostRedisplay();
    }
}

void obtenerPiezas(){
    int posPuntos[12][2]={
            {0,0},
            {1,0},
            {0,3},
            {1,3},
            {3,1},
            {3,2},
            {0,1},
            {0,2},
            {2,4},
            {2,5},
            {4,1},
            {5,1}
    };
    piezas.push_back(Pieza(posPuntos[0],posPuntos[1],1));
    piezas.push_back(Pieza(posPuntos[2],posPuntos[3],2));
    piezas.push_back(Pieza(posPuntos[4],posPuntos[5],3));
    piezas.push_back(Pieza(posPuntos[6],posPuntos[7],4));
    piezas.push_back(Pieza(posPuntos[8],posPuntos[9],5));
    piezas.push_back(Pieza(posPuntos[10],posPuntos[11],6));
    for(auto & pieza : piezas){
        pieza.dibujar();
    }
}

/**
 * Funcion para dibujar la tabla de juego
 */
void generarMesaDeJuego(){
    GLfloat filas[NUM_SQUARES+1][3] = {0};
    GLfloat columnas[NUM_SQUARES+1][3] = {0};

    for (int i = 0; i < NUM_SQUARES+1; ++i) {
        //
        filas[i][0] = -(float)SIZE/2;
        filas[i][1] = -(float)SIZE/2 + (float)(i)*((float)SIZE/NUM_SQUARES);
        filas[i][2] = 0;
        //
        columnas[i][0] = -(float)SIZE/2 + (float)(i)*((float)SIZE/NUM_SQUARES);
        columnas[i][1] = -(float)SIZE/2;
        columnas[i][2] = 0;
    }
    for (int j = 0; j < NUM_SQUARES+1; ++j) {
        glBegin(GL_LINES);
        glVertex3f(filas[j][0],filas[j][1],filas[j][2]);
        glVertex3f(filas[j][0]+SIZE,filas[j][1],filas[j][2]);
        glEnd();
    }

    for (int j = 0; j < NUM_SQUARES+1; ++j) {
        glBegin(GL_LINES);
        glVertex3f(columnas[j][0],columnas[j][1],columnas[j][2]);
        glVertex3f(columnas[j][0],columnas[j][1]+SIZE,columnas[j][2]);
        glEnd();
    }
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

/**
 * Funcion para generar la estructura inicial de la pantalla
 * @param argc Numero de argumentos de la app
 * @param argv Array de los argumentos
 * @param titulo Cadena de texto del titulo
 */
void generarPantalla(int argc, char **argv, char* titulo) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(SIZE, SIZE+20);
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
    glOrtho(-((float)SIZE/2)-20, (float)SIZE/2+20, -((float)SIZE/2)-20, (float)SIZE/2+40, -1.0, 1.0);
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

void mostrarTimer(){
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos3f(-SIZE/2, SIZE/2+20, 0.0);
    escribirTextoBitMap(GLUT_BITMAP_8_BY_13, "TIMER 00:00");
}

/**
 * Funcion principal que permite dibujar los graficos
 */
void dibujarPantalla() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.2,0.2,0.5);
    generarMesaDeJuego();
    obtenerPiezas();
    mostrarTimer();
    glFlush();
}

#endif //PRACTICAS_BASE_H
