# Practica NO 3:
# Nombre completo

from OpenGL.GLUT import *
from OpenGL.GL import *
from OpenGL.GLU import *
import numpy
import math

PI=3.14159265358979324

MAX_RADIUS = 80

POS_CIRC_X = 120
POS_CIRC_Y = 100

COUNT_CIRCLES = 2

# Dimensiones de la pantalla
WidthWin = 400
HeightWin = 800

#timer
refreshMillis = 10

# Funcion para dibujar un circulo
def drawCircle(radius, posX, posY, cantGrades):
    # max 360
    glBegin(GL_LINE_STRIP)
    for i in range(cantGrades):
        angle = 2 * PI * i / 360
        x = math.cos(angle) * radius
        y = math.sin(angle) * radius
        glVertex2d(x + posX, y + posY)
    glEnd()


# Funcion para dibujar una linea
def drawLine(x1,y1,x2,y2):
    glBegin(GL_LINES)
    glVertex3f(x1, y1, 0)
    glVertex3f(x2, y2, 0)
    glEnd()


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
    glClearColor(1.0, 1.0, 1.0, 0.0)


# FUncion para redimensionar la pantalla
def resize(w, h):
    if h == 0:
        h = 1
    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(0.0, HeightWin, WidthWin, 0.0, 0.0, 1.0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()


# Evento key del teclado
def keyInput(key, x, y):
    global COUNT_CIRCLES
    if key == b'\053':  # +
        if COUNT_CIRCLES > 10:
            COUNT_CIRCLES = 10
        COUNT_CIRCLES = COUNT_CIRCLES + 1
        # Refresca la pantalla
        glutPostRedisplay()

    elif key == b'\055':  # -
        COUNT_CIRCLES = COUNT_CIRCLES - 1
        if COUNT_CIRCLES <= 1:
            COUNT_CIRCLES = 2
        # Refresca la pantalla
        glutPostRedisplay()

    elif key == b'\033':  # ESCAPE
        sys.exit()

# Display
def displayMe():
    global COUNT_CIRCLES
    glClear(GL_COLOR_BUFFER_BIT)
    glColor3f(1.0, 0.0, 0.0)
    # Drawing circle base 1 (top)
    drawCircle(MAX_RADIUS, POS_CIRC_X, POS_CIRC_Y, 360)
    # Dibuja los circulos de en medio de acuerdo al total de circulos a dibujar
    # Para que el radio fuera equitativo se dividio
    # entre no total de circulos por el contador
    for i in range(1, COUNT_CIRCLES+1):
        drawCircle(MAX_RADIUS/COUNT_CIRCLES*i,POS_CIRC_X,POS_CIRC_Y,360)
    glColor3f(0.0,0.0,0.0)
    #Dibujar la linea que inicia en el centro del circulo y termina en la circuferencia
    drawLine(POS_CIRC_X, POS_CIRC_Y, POS_CIRC_X, POS_CIRC_Y + MAX_RADIUS)
    #Dibujar textos del circulo superior
    drawingTextBase1()
    #Dibujar los textos de presentacion
    drawingTextMain()
    glFlush()

#DIubujar los texto del circulo superior
def drawingTextBase1():
    glColor3d(0, 0, 0)
    glRasterPos3f(POS_CIRC_X + MAX_RADIUS, POS_CIRC_Y+MAX_RADIUS, 0.0)
    drawTextOnDisplay('radius r')
    glRasterPos3f(POS_CIRC_X + MAX_RADIUS, POS_CIRC_Y - MAX_RADIUS/2, 0.0)
    drawTextOnDisplay('circuference c=2*PI*r')
    glRasterPos3f(POS_CIRC_X + MAX_RADIUS + 100, POS_CIRC_Y + MAX_RADIUS, 0.0)
    drawTextOnDisplay('n=' + str(COUNT_CIRCLES))

#DIbujar textos de presentacion
def drawingTextMain():
    glColor3d(0, 0, 0)
    glRasterPos3f(400.0, 60.0, 0.0)
    drawTextOnDisplay('Nombre completo')
    glRasterPos3f(400.0, 80.0, 0.0)
    drawTextOnDisplay('Calculus Proof for Area of Circle | Practica 3')
    glRasterPos3f(400.0, 100.0, 0.0)
    drawTextOnDisplay('Introduccion a la Graficación por Computadora')

# Funcion para dibujar texto
def drawTextOnDisplay(string):
    for character in string:
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ord(character))


# FUncion principal
def main():
    printInteraction()
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
    glutInitWindowPosition(100, 100)
    glutInitWindowSize(HeightWin, WidthWin)
    glutCreateWindow("Calculus Proof for Area of Circle | Practica 3")
    glutReshapeFunc(resize)
    glutDisplayFunc(displayMe)
    glutTimerFunc(0,timer,0)
    glutKeyboardFunc(keyInput)
    init()
    glutMainLoop()


# EJecutando el main
main()
