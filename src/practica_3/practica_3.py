# Practica 3:
# python3 practica_3
# Angel Armando Valay Martinez

from OpenGL.GLUT import *
from OpenGL.GL import *
from OpenGL.GLU import *
import math
import random
import sys
import array as arr

PI=3.14159265358979324

# Dimensiones de la pantalla
WidthWin = 600
HeightWin = 600

#zoom
zoom = 1.0

#pan
pan_x = 0.0
pan_y = 0.0

#dimensiones del fractal
dimen = 9

#timer
refreshMillis = 10

# Lista para guardar los puntos a dibujar
pointsStart = []

# Funcion para dibujar una circuferencia
def drawCircuference(radius, posX, posY):
    glBegin(GL_LINE_LOOP)
    t = 0.0
    for i in range(0, 60):
        X1 = posX + radius * math.cos(t)
        Y1 = posY + radius * math.sin(t)
        glVertex3f(X1, Y1, 0.0)
        t += 2 * PI / 60
    glEnd()
# FUncion para dibujar un circulo
def drawCircle(radius, posX, posY):
    t = 0.0
    glBegin(GL_POLYGON)
    for i in range(0, 60):
        X1 = posX + radius / 10 * math.cos(t)
        Y1 = posY + radius / 10 * math.sin(t)
        glVertex3f(X1, Y1, 0.0)
        t += 2 * PI / 60
    glEnd()
# FUncion para dibujar una linea
def drawLine(x1,y1,x2,y2):
    glBegin(GL_LINES)
    glVertex3f(x1, y1, 0)
    glVertex3f(x2, y2, 0)
    glEnd()

# Clase para generar las lineas
class Line:
    def __init__(self, x1, y1, x2, y2):
        self._x1 = x1
        self._y1 = y1
        self._x2 = x2
        self._y2 = y2

    def draw(self):
        glBegin(GL_LINES)
        glVertex3f(self._x1, self._y1, 0)
        glVertex3f(self._x2, self._y2, 0)
        glEnd()

    def draw_points(self):
        glPointSize(5)
        glBegin(GL_POINTS)
        glVertex3f(self._x1, self._y1, 0)
        glVertex3f(self._x2, self._y2, 0)
        glEnd()

    @property
    def x1(self):
        return self._x1

    @x1.setter
    def x1(self, val):
        self._x1 = val

    @property
    def y1(self):
        return self._y1

    @y1.setter
    def y1(self, val):
        self._y1 = val

    @property
    def x2(self):
        return self._x2

    @x2.setter
    def x2(self, val):
        self._x2 = val

    @property
    def y2(self):
        return self._y2

    @y2.setter
    def y2(self, val):
        self._y2 = val

#Clase para generar los puntos de partida
class PointStart:
    # position draw
    # 1. Up
    # 2. Right
    # 3. Down
    # 4. Left
    # 5 or other. Nothing
    def __init__(self, xS, yS, radius, position):
        self.xS = xS
        self.yS = yS
        self.radius = radius
        self.position = position

    def drawArea(self):
        # Circuferencia que engloba al elemento
        drawCircuference(self.radius, self.xS, self.yS)
        # Circulo en medio
        drawCircle(self.radius, self.xS, self.yS)
        # Lineas cruzadas
        drawLine(self.xS - self.radius, self.yS, self.xS + self.radius, self.yS)
        drawLine(self.xS, self.yS - self.radius, self.xS, self.yS + self.radius)
        # Dibujar pequenos circulos
        if (self.position == 1):
            # draw up
            drawCircle(self.radius / 2, self.xS, self.yS + (self.radius / 7 * 6))
            # print("Up")
        if (self.position == 2):
            # draw up
            drawCircle(self.radius / 2, self.xS + (self.radius / 7 * 6), self.yS)
            # print("Right")
        if (self.position == 3):
            # draw up
            drawCircle(self.radius / 2, self.xS, self.yS - (self.radius / 7 * 6))
            # print("Down")
        if (self.position == 4):
            # draw up
            drawCircle(self.radius / 2, self.xS - (self.radius / 7 * 6), self.yS)
            # print("Left")
        if (self.position==1 or self.position == 3):
            # dibujar la otra parte de circulos
            drawCircle(self.radius / 3, self.xS + (self.radius), self.yS - (self.radius / 10 * 8))
            drawCircle(self.radius / 3, self.xS - (self.radius), self.yS - (self.radius / 10 * 8))
            drawCircle(self.radius / 3, self.xS - (self.radius), self.yS + (self.radius / 10 * 8))
            drawCircle(self.radius / 3, self.xS + (self.radius), self.yS + (self.radius / 10 * 8))
            # parte 2
            drawCircle(self.radius / 3, self.xS + (self.radius/2), self.yS + (self.radius / 10 * 7.5))
            drawCircle(self.radius / 3, self.xS - (self.radius / 2), self.yS + (self.radius / 10 * 7.5))
            drawCircle(self.radius / 3, self.xS + (self.radius / 2), self.yS - (self.radius / 10 * 7.5))
            drawCircle(self.radius / 3, self.xS - (self.radius / 2), self.yS - (self.radius / 10 * 7.5))
        elif (self.position==2 or self.position == 4):
            # dibujar la otra parte de circulos
            drawCircle(self.radius / 3, self.xS + (self.radius / 10 * 8), self.yS - (self.radius))
            drawCircle(self.radius / 3, self.xS - (self.radius / 10 * 8), self.yS - (self.radius))
            drawCircle(self.radius / 3, self.xS - (self.radius / 10 * 8), self.yS + (self.radius))
            drawCircle(self.radius / 3, self.xS + (self.radius / 10 * 8), self.yS + (self.radius))
            # parte 2
            drawCircle(self.radius / 3, self.xS + (self.radius / 10 * 7.5), self.yS + (self.radius / 2))
            drawCircle(self.radius / 3, self.xS - (self.radius / 10 * 7.5), self.yS + (self.radius / 2))
            drawCircle(self.radius / 3, self.xS + (self.radius / 10 * 7.5), self.yS - (self.radius / 2))
            drawCircle(self.radius / 3, self.xS - (self.radius / 10 * 7.5), self.yS - (self.radius / 2))

def generatePoints(dim, len, posX, posY):
    # global dimen
    if (dim == dimen):
        pointsStart.append(PointStart(posX , posY, len, 5))
    if(dim > 0):
        if(dim%2 == 0):
            pointsStart.append(PointStart(posX + (len/2), posY, len/2, 2))
            pointsStart.append(PointStart(posX - (len/2), posY, len/2, 4))
            generatePoints(dim - 1, len / 2, posX - (len / 2), posY)
            generatePoints(dim - 1, len / 2, posX + (len / 2), posY)
        else:
            pointsStart.append(PointStart(posX, posY + (len / 2), len / 2, 1))
            pointsStart.append(PointStart(posX, posY - (len / 2), len / 2, 3))
            generatePoints(dim - 1, len / 2, posX, posY - (len / 2))
            generatePoints(dim - 1, len / 2, posX, posY + (len / 2))

#resetear los valores
def reset():
    global zoom, pan_x, pan_y
    zoom = 1.0
    pan_x = 0.0
    pan_y = 0.0


def timer(value):
    global refreshMillis, zoom, pan_x, pan_y
    zoom = zoom + 0.1
    pan_x = pan_x + (125 / (((1.0 - zoom) * 10)))
    pan_y = pan_y - (62.5 / (((1.0 - zoom) * 10)))
    if (zoom >= 4.0):
        reset()

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
    glOrtho(-1000.0, 1000.0, -1000, 1000.0, -1.0, 1.0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()

# Display
def displayMe():
    global zoom, pan_x, pan_y
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glColor3f(1.0, 1.0, 1.0)
    glLoadIdentity()
    glPushMatrix()
    glScalef(zoom, zoom, 1.0)
    glTranslatef(pan_x, pan_y, 0.0)
    for point in pointsStart:
        point.drawArea()
    glPopMatrix()
    glutSwapBuffers()


# Funcion para dibujar texto
def drawTextOnDisplay(string):
    for character in string:
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ord(character))

generatePoints(dimen, 2000, 0, 1000)

# FUncion principal
def main():
    printInteraction()
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
    glutInitWindowPosition(100, 100)
    glutInitWindowSize(HeightWin, WidthWin)
    glutCreateWindow("Fractal complejo | Practica 3")
    glutReshapeFunc(resize)
    glutDisplayFunc(displayMe)
    glutTimerFunc(0,timer,0)
    reset()
    glutMainLoop()


# EJecutando el main
main()
