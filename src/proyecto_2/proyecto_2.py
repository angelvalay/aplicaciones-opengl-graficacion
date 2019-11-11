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
import numpy

PI=3.14159265358979324

# Dimensiones de la pantalla
WidthWin = 600
HeightWin = 600

# variables globales
NEAR_Z =  1.0
FAR_Z = 400.0

# zoom por ejes
zoom = 60
zoom_x = 0
zoom_y = 0
zoom_z = 0

# isShowMessage?
showMessageStart = 0

# Timer
refreshMillis = 500

# Se crea una malla del eje Y
wall1 = game.Wall(3, 3, (-10, -10, 0), 'Y')
listPoints = wall1.getPoints()

# Se crea una malla del eje Z
wall2 = game.Wall(3,10,(-10,-10,0),'Z')
listPoints2 = wall2.getPoints()

# Se crea una malla del eje X
wall3 = game.Wall(10,3,(-10,-10,0),'X')
listPoints3 = wall3.getPoints()

# array de figuras
# este array guarda las figuras que se van generando para asi mantener todo las figuras
figures = []


def timer(value):
    global refreshMillis, figures, showMessageStart
    # Si el juego ya empezo
    if showMessageStart == 1:
        figure = figures[0]
        print('figura -> ', figure)
        for cube in figure.cubes:
            print(cube.getPointToArray())
        if figure.isValidateMove(0,-1,0):
            print('puede bajar')
            # Refresca la pantalla
            figure.moveY(-1)
            glutPostRedisplay()
        else:
            print('ya no se puede bajar')
            # figures=[]
            # Se crea una figura de prueba
            figures.insert(0,game.Figure(random.randint(0,3), 1, 10, 1))
            print(figures)
            showMessageStart = 0
            glutPostRedisplay()
    glutTimerFunc(refreshMillis, timer, 0)

# Para mostrar las opciones
def printInteraction():
    print("Interaction:")
    print("Presiona [ESCAPE] para finalizar.")

# Funcion para iniciar
def init():
    glClearColor(0.0, 0.0, 0.0, 0.0)

# Funcion para redimensionar la pantalla
def resize(w, h):
    if h == 0:
        h = 1
    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(10.0, w / h, NEAR_Z, FAR_Z)
    glMatrixMode(GL_MODELVIEW)

# Funcion para dibujar texto
def drawTextOnDisplay(string):
    for character in string:
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ord(character))

# FUncion para el keyinput
def keyInput(key, x, y):
    global zoom, zoom_x, zoom_y, zoom_z, showMessageStart
    if key == b'\053':  # ESCAPE
        zoom = zoom  - 1

    if key == b'\055':  # +
        zoom = zoom + 1

    if key == b'\033':  # -
        zoom = zoom - 1

    if key == b'\170':  # x
        zoom_x = zoom_x + 10

    if key == b'\171':  # y
        zoom_y = zoom_y + 10

    if key == b'\172':  # z
        zoom_z = zoom_z + 10

    if key == b'\040': # space
        if showMessageStart == 0:
            showMessageStart = 1
        elif showMessageStart == 1:
            showMessageStart = 0

    if key == b'\062': # borrar es de prueba 2222
        if figures[-1].isValidateMove(0, 0, 1):
            figures[-1].moveZ(1)
    if key == b'\070': # borrar es de prueba 8888
        if figures[-1].isValidateMove(0, 0, -1):
            figures[-1].moveZ(-1)
    if key == b'\064': # borrar es de prueba 4444
        if figures[-1].isValidateMove(-1, 0, 0):
            figures[-1].moveX(-1)
    if key == b'\066': # borrar es de prueba 6666
        if figures[-1].isValidateMove(1, 0, 0):
            figures[-1].moveX(1)

    glutPostRedisplay()

# Funcion para mostrar los datos
def displayText():
    glColor(1, 1, 1)
    glRasterPos3f(-10.0, 10.0, 0)
    drawTextOnDisplay('Tetris 3D')
    glRasterPos3f(-10.0, 9.0, 0)
    drawTextOnDisplay('Tiempo: 00:00')
    # si aun no empieza o esta en pausa
    if showMessageStart == 0:
        glRasterPos3f(-10.0, 8.0, 0)
        drawTextOnDisplay('Presionar SPACE para empezar o reanudar')

# Display
def displayMe():
    global listPoints, zoom, zoom_x, zoom_y, zoom_z
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    gluLookAt(zoom, zoom, zoom, 0.0, 5, 0.0, 0.0, 1.0, 0.0)
    glRotatef(zoom_x, 1.0, 0.0, 0.0)
    glRotatef(zoom_y, 0.0, 1.0, 0.0)
    glRotatef(zoom_z, 0.0, 0.0, 1.0)
    # Agregar lookAt
    # Mostrar texto
    displayText()
    # Dibuja la primera malla
    glBegin(GL_LINES)
    for item in listPoints:
        glVertex3fv(item)
    glEnd()
    glColor(0.5,0.6,0.7)
    # Dibuja la segunda malla
    glBegin(GL_LINES)
    for item in listPoints2:
        glVertex3fv(item)
    glEnd()
    glColor(0.8, 0.1, 0.7)
    # Dibuja la tercera malla
    glBegin(GL_LINES)
    for item in listPoints3:
        glVertex3fv(item)
    glEnd()
    # hago un translei para mover las figuras una mitad del cubo hacia el inferior para que
    # coloquen bien
    glTranslatef(game.UNIT_CUBE/2,game.UNIT_CUBE/2,game.UNIT_CUBE/2)
    # se imprimen las figuras
    for figure in  figures:
        # muestra la figura cubo x cubo
        glColor(0.6, 0.6, 0.6)
        for cube in figure.cubes:
            # mostrar la cara del cubo cara x cara
            for face in range(1,6,1):
                # glPointSize(5)
                # dibuja el poligono
                glBegin(GL_POLYGON)
                # extrae los puntos
                for point in cube.Faces(face):
                    glVertex3fv(point)
                glEnd()
    glutSwapBuffers()

# Funcion principal
def main():
    # se anade la figura de prueba a la lista
    figures.append(game.Figure(random.randint(0, 3), 1, 10, 1))
    print(figures)
    printInteraction()
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
    glutInitWindowPosition(100, 100)
    glutInitWindowSize(HeightWin, WidthWin)
    glutCreateWindow("Juego 2 | Tetris 3D")
    glutReshapeFunc(resize)
    glutDisplayFunc(displayMe)
    glutKeyboardFunc(keyInput)
    glutTimerFunc(0,timer,0)
    glutMainLoop()

# Ejecutando el main
main()
