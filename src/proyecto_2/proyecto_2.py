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
refreshMillis = 1000

# Se crea una malla del eje Y
wall1 = game.wall(3, 3, (-10, -10, 0), 'Y')
listPoints = wall1.getPoints()

# Se crea una malla del eje Z
wall2 = game.wall(3,10,(-10,-10,0),'Z')
listPoints2 = wall2.getPoints()

# Se crea una malla del eje X
wall3 = game.wall(10,3,(-10,-10,0),'X')
listPoints3 = wall3.getPoints()

# Se crea un cubo de prueba
fig1 = game.figure(10,3,10,3)

def timer(value):
    global refreshMillis
    # Si el juego ya empezo
    if showMessageStart == 1:
        # Refresca la pantalla
        fig1.moveY(-1)
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
        zoom_x = zoom_x + 1

    if key == b'\171':  # y
        zoom_y = zoom_y + 1

    if key == b'\172':  # z
        zoom_z = zoom_z + 1

    if key == b'\040': # space
        if showMessageStart == 0:
            showMessageStart = 1
        elif showMessageStart == 1:
            showMessageStart = 0

    if key == b'\062': # borrar es de prueba 2222
        fig1.moveZ(1)
    if key == b'\070': # borrar es de prueba 8888
        fig1.moveZ(-1)
    if key == b'\064': # borrar es de prueba 4444
        fig1.moveX(-1)
    if key == b'\066': # borrar es de prueba 6666
        fig1.moveX(1)

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
    # Agregar lookAt
    gluLookAt(zoom + zoom_x, zoom + zoom_y, zoom + zoom_z, 0.0, 5, 0.0, 0.0, 1.0, 0.0)
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
    glColor(0.2, 0.9, 0.4)
    # muestra la figura cubo x cubo
    for cube in fig1.cubes:
        # mostrar la cara del cubo cara x cara
        for face in range(1,6,1):
            # glPointSize(5)
            # dibuja el poligono
            glBegin(GL_POLYGON)
            # extrae los puntos
            for point in cube.faces(face):
                glVertex3fv(point)
            glEnd()
    glutSwapBuffers()

# Funcion principal
def main():
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