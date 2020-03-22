# Ejecucion:
# python3 practica_4

from OpenGL.GLUT import *  # GL Utilities Toolkit
from OpenGL.GL import *
from OpenGL.GLU import *
import math
import random
import sys

# Ancho y largo de la ventana
AlturaVentana = 500
AnchuraVentana = 500

NEAR_Z = 1.0 # Que tan cerca esta
FAR_Z = 5000.0 #Que tan lejos esta

Xangle = 30.0
Yangle = 330.0
Zangle = 0.0

def printInteraction():
    """
    Menu de informacion que es visible para la interaccion con el programa
    """
    print("Interaction:")
    print("Press [SPACE] to move selected object.")
    print("Press [ARROW] LEFT/RIGHT/TOP/BOTTOM to move object.")
    print("Press [ESCAPE] to finish.")
    print("From to: Angel Armando Valay Martinez.")
    print("Practica de recuperacion | Rompecabezas.")

def init():
    """
    FUncion para inicializar variables, se ejecuta cuando la aplicacion se inicia
    """
    # red, green, blue, alpha from 0.0 to 1.0
    glClearColor(1.0, 1.0, 1.0, 0.0)

def resize(w, h):
    """
    FUncion para capturar el evento de la redimension de pantalla
    :param w: nueva anchura
    :param h: nueva altura
    """
    if h == 0:
        h = 1
    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(60.0, w / h, 1.0, 50.0)
    glMatrixMode(GL_MODELVIEW)

def displayMe():
    """
    FUncion para dibujar en pantalla
    """
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()
    gluLookAt(0.0, 3.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)

    glRotatef(Zangle, 0.0, 0.0, 1.0)
    glRotatef(Yangle, 0.0, 1.0, 0.0)
    glRotatef(Xangle, 1.0, 0.0, 0.0)

    glMapGrid2f(20, 1.0, 0.0, 20, 0.0, 1.0)
    glEvalMesh2(GL_LINE, 0, 20, 0, 20)
    glutSwapBuffers()


def main():
    """
    FUncion main
    """
    printInteraction()
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH)
    glutInitWindowPosition(100, 100)
    glutInitWindowSize(AnchuraVentana, AlturaVentana)
    glutCreateWindow(b"Practica 4 | Construccion de una bocina en 3D")
    glutReshapeFunc(resize)
    glutDisplayFunc(displayMe)
    init()
    glutMainLoop()


if __name__ == "__main__":
    main()
