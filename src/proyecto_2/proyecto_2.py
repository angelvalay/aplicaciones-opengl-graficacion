# Proyecto 2:
# python3 proyecto_2
# Angel Armando Valay Martinez

from OpenGL.GLUT import *
from OpenGL.GL import *
from OpenGL.GLU import *
import math
import random
import sys
import array as arr
import game

PI=3.14159265358979324

# Dimensiones de la pantalla
WidthWin = 600
HeightWin = 600

NEAR_Z = 1
FAR_Z = 200

# Timer
refreshMillis = 10

wall1 = game.wall(20, 10, (-10, -10, 0), 'Z')

listPoints = wall1.getPoints()


def timer(value):
    global refreshMillis
    # Refresca la pantalla
    glutPostRedisplay()
    glutTimerFunc(refreshMillis, timer, 0)

# Para mostrar las opciones
def printInteraction():
    print("Interaction:")
    print("Presiona [ESCAPE] para finalizar.")

# FUncion para iniciar
def init():
    glClearColor(0.0, 0.0, 0.0, 0.0)

# FUncion para redimensionar la pantalla
def resize(w, h):
    if h == 0:
        h = 1
    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(0, w/h, NEAR_Z, FAR_Z)
    glMatrixMode(GL_MODELVIEW)


# Funcion para dibujar texto
def drawTextOnDisplay(string):
    for character in string:
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ord(character))


# Display
def displayMe():
    global listPoints
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glColor3f(1.0, 1.0, 1.0)
    # glLoadIdentity()
    glPointSize(5)
    glBegin(GL_POINTS)
    for item in listPoints:
        # falta dibujar los puntos de las celdas que van en los costados
        # print(item)
        glVertex3fv(item)
    glEnd()
    glutSwapBuffers()


# FUncion principal
def main():
    printInteraction()
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
    glutInitWindowPosition(100, 100)
    glutInitWindowSize(HeightWin, WidthWin)
    glutCreateWindow("Juego 2")
    glutReshapeFunc(resize)
    glutDisplayFunc(displayMe)
    glutTimerFunc(0,timer,0)
    glutMainLoop()


# EJecutando el main
main()
