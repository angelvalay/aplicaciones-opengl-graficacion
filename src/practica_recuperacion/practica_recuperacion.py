# Ejecucion:
# python3 practica_recuperacion

from OpenGL.GLUT import *  # GL Utilities Toolkit
from OpenGL.GL import *
from OpenGL.GLU import *
import math
import random
import sys
from PIL import Image
import numpy
from enum import Enum

# Valores iniciales
AlturaVentana = 375
AnchuraVentana = 1000

# textura
texture_id = 0

WIDTH_FIG = 200
HEIGHT_FIG = 160

# dimensiones de las piezas
SIZE_FIG_WIDTH = WIDTH_FIG/5
SIZE_FIG_HEIGHT = HEIGHT_FIG/4

pieces = []

selected = 0

class Orientation(Enum):
    VERTICAL = 1
    HORIZONTAL = 2

class Position(Enum):
    TOP = 1
    BOTTOM = 2
    LEFT = 3
    RIGHT = 4

class Point:
    x = 0
    y = 0

    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __repr__(self):
        return str(self.x) + ' ' + str(self.y)

    def getX(self):
        return self.x

    def getY(self):
        return self.y

    def getPoint(self):
        return [self.x, self.y, 0]

    def setTranslate(self,x,y):
        self.x+= x
        self.y+= y

class Pieze:
    orientation = 0
    position = 0
    points = []
    pointsForTexture = []
    pointStart = Point(0,0)
    translateX = 0
    translateY = 0
    setCurve = []
    def __init__(self, x, y, left, top, right, bottom):
        self.pointStart = Point(x, y)
        self.points = []
        self.pointsForTexture= []
        self.translateX = 0
        self.translateY = 0
        self.setCurve[:] = []
        # -1 -> Lineal
        # 0 -> to Down (hacia dentro)
        # 1 -> to Up (hacia fuera)
        self.setCurve= [left,top,right,bottom]

    def generatePoints(self):
        self.points[:] = []
        self.pointsForTexture[:] = []
        for r in range(1,5):
            if r == 1 or r == 3 :
                for n in numpy.arange(0, SIZE_FIG_HEIGHT-0.5,0.5):
                    if r == 1: #LEFT
                        if self.setCurve[r-1] == -1:
                            self.points.append(Point(self.pointStart.getX(),
                                                     self.pointStart.getY() + n))
                            self.pointsForTexture.append(Point(self.pointStart.getX()/WIDTH_FIG,
                                                        (self.pointStart.getY() + n)/HEIGHT_FIG))
                        elif self.setCurve[r-1] == 0: # curva hacia derecha
                            if (n/SIZE_FIG_HEIGHT)>0.28 and (n/SIZE_FIG_HEIGHT)<0.73:
                                #glVertex2d(getXInside((n/SIZE_FIG_HEIGHT)) * SIZE_FIG_WIDTH, (n/SIZE_FIG_HEIGHT) * SIZE_FIG_HEIGHT)
                                self.points.append(Point((self.pointStart.getX() + getXInside(n/SIZE_FIG_HEIGHT)*SIZE_FIG_WIDTH),
                                                         self.pointStart.getY() + n))
                                self.pointsForTexture.append(Point(((self.pointStart.getX() + getXInside(n/SIZE_FIG_HEIGHT)*SIZE_FIG_WIDTH) / WIDTH_FIG),
                                                                   (self.pointStart.getY() + n) / HEIGHT_FIG))
                            else:
                                self.points.append(Point(self.pointStart.getX(),
                                                         self.pointStart.getY() + n))
                                self.pointsForTexture.append(Point(self.pointStart.getX() / WIDTH_FIG,
                                                                   (self.pointStart.getY() + n) / HEIGHT_FIG))
                        elif self.setCurve[r - 1] == 1: #curva hacia izquierda
                            if (n / SIZE_FIG_HEIGHT) > 0.28 and (n / SIZE_FIG_HEIGHT) < 0.73:
                                self.points.append(
                                    Point((self.pointStart.getX() + getXOutside(n / SIZE_FIG_HEIGHT) * SIZE_FIG_WIDTH),
                                          self.pointStart.getY() + n))
                                self.pointsForTexture.append(Point(((self.pointStart.getX() + getXOutside(
                                    n / SIZE_FIG_HEIGHT) * SIZE_FIG_WIDTH) / WIDTH_FIG),
                                                                   (self.pointStart.getY() + n) / HEIGHT_FIG))
                            else:
                                self.points.append(Point(self.pointStart.getX(),
                                                         self.pointStart.getY() + n))
                                self.pointsForTexture.append(Point(self.pointStart.getX() / WIDTH_FIG,
                                                                   (self.pointStart.getY() + n) / HEIGHT_FIG))
                    elif r == 3: #RIGHT
                        if self.setCurve[r - 1] == -1:
                            self.points.append(Point(self.pointStart.getX() + SIZE_FIG_WIDTH,
                                                     (self.pointStart.getY() + SIZE_FIG_HEIGHT) - n))
                            self.pointsForTexture.append(Point((self.pointStart.getX() + SIZE_FIG_WIDTH)/WIDTH_FIG,
                                                     ((self.pointStart.getY()+ SIZE_FIG_HEIGHT) - n)/HEIGHT_FIG))
                        elif self.setCurve[r - 1] == 0:
                            if (n / SIZE_FIG_HEIGHT) > 0.28 and (n / SIZE_FIG_HEIGHT) < 0.73:
                                self.points.append(
                                    Point(self.pointStart.getX() + SIZE_FIG_WIDTH + getXOutside(n / SIZE_FIG_HEIGHT) * SIZE_FIG_WIDTH,
                                                         (self.pointStart.getY() + SIZE_FIG_HEIGHT) - n))
                                self.pointsForTexture.append(Point((self.pointStart.getX() + SIZE_FIG_WIDTH)/WIDTH_FIG,
                                                         ((self.pointStart.getY()+ SIZE_FIG_HEIGHT) - n)/HEIGHT_FIG))
                            else:
                                self.points.append(Point(self.pointStart.getX() + SIZE_FIG_WIDTH,
                                                         (self.pointStart.getY() + SIZE_FIG_HEIGHT) - n))
                                self.pointsForTexture.append(
                                    Point((self.pointStart.getX() + SIZE_FIG_WIDTH) / WIDTH_FIG,
                                          ((self.pointStart.getY() + SIZE_FIG_HEIGHT) - n) / HEIGHT_FIG))
                        if self.setCurve[r - 1] == 1:
                            if (n / SIZE_FIG_HEIGHT) > 0.28 and (n / SIZE_FIG_HEIGHT) < 0.73:
                                self.points.append(
                                    Point(self.pointStart.getX() + SIZE_FIG_WIDTH + getXInside(n / SIZE_FIG_HEIGHT) * SIZE_FIG_WIDTH,
                                          (self.pointStart.getY() + SIZE_FIG_HEIGHT) - n))
                                self.pointsForTexture.append(
                                    Point((self.pointStart.getX() + SIZE_FIG_WIDTH) / WIDTH_FIG,
                                          ((self.pointStart.getY() + SIZE_FIG_HEIGHT) - n) / HEIGHT_FIG))
                            else:
                                self.points.append(Point(self.pointStart.getX() + SIZE_FIG_WIDTH,
                                                         (self.pointStart.getY() + SIZE_FIG_HEIGHT) - n))
                                self.pointsForTexture.append(
                                    Point((self.pointStart.getX() + SIZE_FIG_WIDTH) / WIDTH_FIG,
                                          ((self.pointStart.getY() + SIZE_FIG_HEIGHT) - n) / HEIGHT_FIG))
            else:
                for n in numpy.arange(0,SIZE_FIG_WIDTH-0.5,0.5):
                    if r == 2: #TOP
                        if self.setCurve[r - 1] == -1:
                            self.points.append(Point(self.pointStart.getX() + n,
                                                     self.pointStart.getY() + SIZE_FIG_HEIGHT))
                            self.pointsForTexture.append(Point((self.pointStart.getX() + n) / WIDTH_FIG,
                                                               (self.pointStart.getY() + SIZE_FIG_HEIGHT) / HEIGHT_FIG))
                        if self.setCurve[r - 1] == 0:
                            if (n / SIZE_FIG_WIDTH) > 0.28 and (n / SIZE_FIG_WIDTH) < 0.73:
                                self.points.append(Point(self.pointStart.getX() + n,
                                                         self.pointStart.getY() + getYOutside(n/SIZE_FIG_WIDTH)*SIZE_FIG_HEIGHT + SIZE_FIG_HEIGHT))
                                self.pointsForTexture.append(Point((self.pointStart.getX() + n) / WIDTH_FIG,
                                                                   (self.pointStart.getY() + SIZE_FIG_HEIGHT + getYOutside(n/SIZE_FIG_WIDTH)*SIZE_FIG_HEIGHT) / HEIGHT_FIG))
                            else:
                                self.points.append(Point(self.pointStart.getX() + n,
                                                         self.pointStart.getY() + SIZE_FIG_HEIGHT))
                                self.pointsForTexture.append(Point((self.pointStart.getX() + n) / WIDTH_FIG,
                                                                   (self.pointStart.getY() + SIZE_FIG_HEIGHT) / HEIGHT_FIG))
                        if self.setCurve[r - 1] == 1:
                            if (n / SIZE_FIG_WIDTH) > 0.28 and (n / SIZE_FIG_WIDTH) < 0.73:
                                self.points.append(Point(self.pointStart.getX() + n,
                                                         self.pointStart.getY() + getYInside(n / SIZE_FIG_WIDTH) * SIZE_FIG_HEIGHT + SIZE_FIG_HEIGHT))
                                self.pointsForTexture.append(Point((self.pointStart.getX() + n) / WIDTH_FIG,
                                                                   (self.pointStart.getY() + SIZE_FIG_HEIGHT + getYInside(
                                                                           n / SIZE_FIG_WIDTH) * SIZE_FIG_HEIGHT) / HEIGHT_FIG))
                            else:
                                self.points.append(Point(self.pointStart.getX() + n,
                                                         self.pointStart.getY() + SIZE_FIG_HEIGHT))
                                self.pointsForTexture.append(Point((self.pointStart.getX() + n) / WIDTH_FIG,
                                                                   (self.pointStart.getY() + SIZE_FIG_HEIGHT) / HEIGHT_FIG))
                    elif r == 4: # BOTTOM
                        if self.setCurve[r - 1] == -1:
                            self.points.append(Point((self.pointStart.getX() + SIZE_FIG_WIDTH) - n,
                                                     self.pointStart.getY()))
                            self.pointsForTexture.append(Point(((self.pointStart.getX() + SIZE_FIG_WIDTH) - n) / WIDTH_FIG,
                                                               (self.pointStart.getY()) / HEIGHT_FIG))
                        if self.setCurve[r - 1] == 0:
                            if (n / SIZE_FIG_WIDTH) > 0.28 and (n / SIZE_FIG_WIDTH) < 0.73:
                                self.points.append(Point((self.pointStart.getX() + SIZE_FIG_WIDTH) - n,
                                                         self.pointStart.getY()  + getYInside(n/SIZE_FIG_WIDTH)*SIZE_FIG_HEIGHT))
                                self.pointsForTexture.append(Point(((self.pointStart.getX() + SIZE_FIG_WIDTH) - n) / WIDTH_FIG,
                                                                   (self.pointStart.getY() + getYInside(n/SIZE_FIG_WIDTH)*SIZE_FIG_HEIGHT) / HEIGHT_FIG))
                            else:
                                self.points.append(Point((self.pointStart.getX() + SIZE_FIG_WIDTH) - n,
                                                         self.pointStart.getY()))
                                self.pointsForTexture.append(
                                    Point(((self.pointStart.getX() + SIZE_FIG_WIDTH) - n) / WIDTH_FIG,
                                          (self.pointStart.getY()) / HEIGHT_FIG))
                        if self.setCurve[r - 1] == 1:
                            if (n / SIZE_FIG_WIDTH) > 0.28 and (n / SIZE_FIG_WIDTH) < 0.73:
                                self.points.append(Point((self.pointStart.getX() + SIZE_FIG_WIDTH) - n,
                                                         self.pointStart.getY() +  getYOutside(n/SIZE_FIG_WIDTH)*SIZE_FIG_HEIGHT))
                                self.pointsForTexture.append(Point(((self.pointStart.getX() + SIZE_FIG_WIDTH) - n) / WIDTH_FIG,
                                                                    (self.pointStart.getY() + getYOutside(n/SIZE_FIG_WIDTH)*SIZE_FIG_HEIGHT) / HEIGHT_FIG))
                            else:
                                self.points.append(Point((self.pointStart.getX() + SIZE_FIG_WIDTH) - n,
                                                         self.pointStart.getY()))
                                self.pointsForTexture.append(
                                    Point(((self.pointStart.getX() + SIZE_FIG_WIDTH) - n) / WIDTH_FIG,
                                          (self.pointStart.getY()) / HEIGHT_FIG))


    def getPoints(self):
        return self.points

    def setPositionCurve(self, left, top, right, bottom):
        self.setCurve[:] = []
        self.setCurve = [left, top, right, bottom]

    def printPosition(self):
        print(self.setCurve)

    def getPointForTexture(self, index):
        return self.pointsForTexture[index]

    def translate(self,x,y):
        self.translateX = self.translateX + x
        self.translateY = self.translateY + y
        # self.points[:] = []
        # self.pointsForTexture[:] = []
        for point in self.points:
            point.setTranslate(x, y)
    def __repr__(self):
        return str(self.pointStart.x)+ ' '+ str(self.pointStart.y)

def getYOutside(x):
    """
    Funcion para generar una parabola con el embone hacia abajo \/
    :param x: valor de x
    :return: valor de y
    """
    return 5*(x**2) - 5*x + 1

def getYInside(x):
    """
    Funcion para generar una parabola con el embone hacia arriba ^
    :param x: valor de x
    :return: valor de y
    """
    return -5*(x**2) + 5*x - 1

def getXInside(y):
    """
    Funcion para generar una parabola con el embone hacia la derecha >
    :param y: valor de y
    :return: valor de x
    """
    return -5*(y**2) + 5*y - 1

def getXOutside(y):
    """
    Funcion para generar una parabola con el embone hacia la izquierda <
    :param y: valor de y
    :return: valor de x
    """
    return 5*(y**2) - 5*y + 1

def buildPieces():
    global pieces
    pieces.append(Pieze(0, 0, -1, 0, 1, -1))
    pieces.append(Pieze(SIZE_FIG_HEIGHT, 0, 0, 1, 0, -1))
    pieces.append(Pieze(SIZE_FIG_HEIGHT * 2, 0, 1, 0, 1, -1))
    pieces.append(Pieze(SIZE_FIG_HEIGHT * 3, 0, 0, 1, 0, -1))
    pieces.append(Pieze(SIZE_FIG_HEIGHT * 4, 0, 1, 0, -1, -1))

    pieces.append(Pieze(0, SIZE_FIG_WIDTH, -1, 1, 0, 1))
    pieces.append(Pieze(SIZE_FIG_HEIGHT, SIZE_FIG_WIDTH, 1, 0, 1, 0))
    pieces.append(Pieze(SIZE_FIG_HEIGHT * 2, SIZE_FIG_WIDTH, 0, 1, 0, 1))
    pieces.append(Pieze(SIZE_FIG_HEIGHT * 3, SIZE_FIG_WIDTH, 1, 0, 1, 0))
    pieces.append(Pieze(SIZE_FIG_HEIGHT * 4, SIZE_FIG_WIDTH, 0, 1, -1, 1))

    pieces.append(Pieze(0, SIZE_FIG_WIDTH*2, -1, 0, 1, 0))
    pieces.append(Pieze(SIZE_FIG_HEIGHT, SIZE_FIG_WIDTH*2, 0, 1, 0, 1))
    pieces.append(Pieze(SIZE_FIG_HEIGHT * 2, SIZE_FIG_WIDTH*2, 1, 0, 1, 0))
    pieces.append(Pieze(SIZE_FIG_HEIGHT * 3, SIZE_FIG_WIDTH*2, 0, 1, 0, 1))
    pieces.append(Pieze(SIZE_FIG_HEIGHT * 4, SIZE_FIG_WIDTH*2, 1, 0, -1, 0))

    pieces.append(Pieze(0, SIZE_FIG_WIDTH * 3, -1, -1, 1, 1))
    pieces.append(Pieze(SIZE_FIG_HEIGHT, SIZE_FIG_WIDTH * 3, 0, -1, 0, 0))
    pieces.append(Pieze(SIZE_FIG_HEIGHT * 2, SIZE_FIG_WIDTH * 3, 1, -1, 1, 1))
    pieces.append(Pieze(SIZE_FIG_HEIGHT * 3, SIZE_FIG_WIDTH * 3, 0, -1, 0, 0))
    pieces.append(Pieze(SIZE_FIG_HEIGHT * 4, SIZE_FIG_WIDTH * 3, 1, -1, -1, 1))
    for piece in pieces:
        piece.generatePoints()
        piece.translate(random.randint(-70,70),random.randint(-70,70))


def drawTextOnPosition2D(x, y, text):
    """
    Funcion para dibujar texto en 2d
    :param x: posicion en x del texto
    :param y: posicion en y del texto
    :param text: texto a dibujar
    """
    glRasterPos3f(x, y, 0.0)
    drawTextOnDisplay(text)


def drawOriginalFigure():
    """
    FUncion para dibujar la figura original
    """

    # anadir linea vertical
    glBegin(GL_LINES)
    glVertex3f(0, -40, 0)
    glVertex3f(0, 220, 0)
    glEnd()

    # generar cuadro izquierdo
    glEnable(GL_TEXTURE_2D)
    glBindTexture(GL_TEXTURE_2D, texture_id)

    # anadir imagen original
    glBegin(GL_POLYGON)
    glTexCoord2f(1.0, 1.0)
    glVertex3f(-220, 0, 0)
    glTexCoord2f(1.0, 0.0)
    glVertex3f(-220, 160, 0)
    glTexCoord2f(0.0, 0.0)
    glVertex3f(-20, 160, 0)
    glTexCoord2f(0.0, 1.0)
    glVertex3f(-20, 0, 0)
    glEnd()
    glDisable(GL_TEXTURE_2D)

def drawPiecesFigure():
    global pieces
    # anadir imagen original
    glEnable(GL_TEXTURE_2D)
    glBindTexture(GL_TEXTURE_2D, texture_id)
    #aqui pinto las texturas en la pantalla
    for piece in pieces:
        #si la pieza que se intenta dibujar es la seleccionada
        # no se dibuja al inicio
        if piece != pieces[selected]:
            glBegin(GL_POLYGON)
            p = piece.getPoints()
            for i in range(0,p.__len__()):
                glTexCoord2f(1-piece.getPointForTexture(i).getX(), (1-piece.getPointForTexture(i).getY()))
                glVertex3f(p[i].getX(), p[i].getY(),0)
            glEnd()
    glDisable(GL_TEXTURE_2D)
    # aqui pinto los bordes de cada pieza en la pantalla
    for piece in pieces:
        # si la pieza que se intenta dibujar es la seleccionada
        if piece != pieces[selected]:
            glBegin(GL_LINES)
            p = piece.getPoints()
            for i in range(0, p.__len__()):
                glVertex3f(p[i].getX(), p[i].getY(), 0)
            glEnd()

    #dibuja la textura
    glEnable(GL_TEXTURE_2D)
    glBindTexture(GL_TEXTURE_2D, texture_id)
    #dibuja la textura del objecto seleccionado
    glBegin(GL_POLYGON)
    p = pieces[selected].getPoints()
    for i in range(0, p.__len__()):
        glTexCoord3f(1 -pieces[selected].getPointForTexture(i).getX(),
                     (1 - pieces[selected].getPointForTexture(i).getY()),0)
        glVertex3f(p[i].getX(), p[i].getY(), 0)
    glEnd()
    glDisable(GL_TEXTURE_2D)

    # dibuja la linea que sobresale de la pieza seleccionada
    glPointSize(4)
    glBegin(GL_POINTS)
    p = pieces[selected].getPoints()
    for i in range(0, p.__len__()):
        glVertex3f(p[i].getX(), p[i].getY(), 0)
    glEnd()

def drawMenu():
    """
    Funcion para dibujar el texto en la pantalla(MENU)
    """
    glColor3f(0, 0, 0)
    drawTextOnPosition2D(-180, -20, 'Imagen original')
    drawTextOnPosition2D(-240, 180, 'ESPACIO para cambiar la figura')
    drawTextOnPosition2D(-240, 170, 'FLECHAS para mover la figura')
    drawTextOnPosition2D(100, -20, 'Rompecabezas')

def drawTextOnDisplay(string):
    """
    Funcion para dibujar texto en pantalla
    :param string: Cadena de texto a dibujar
    """
    for character in string:
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ord(character))


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
    texture_id = readTexture('garfield.jpeg')


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
    # generacion del orto
    glOrtho(-250, 250, -40, 200.0, -1.0, 1.0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()


def keyInput(key, x, y):
    global selected, pieces

    """
    FUncion para el evento key
    :param key: tecla de entrada
    :param x: en que posicion x
    :param y: en que posicion y
    """
    if key == b'\040':  # -
        selected +=1
        if selected>19:
            selected =0
        glutPostRedisplay()

    if key == b'\055':  # +
        glutPostRedisplay()


    if key == b'\033':  # ESCAPE
        sys.exit()

def specialKeyInput(key, x, y):
    """
    Funcion para anadir evento a la entrada de teclado con caracteres especiales
    :param key: boton presionado
    :param x: posicion x
    :param y: posicion y
    """
    global selected, pieces
    if key == GLUT_KEY_LEFT:  # <-
        pieces[selected].translate(-2, 0)
        glutPostRedisplay()

    if key == GLUT_KEY_RIGHT:  # ->
        pieces[selected].translate(2, 0)
        glutPostRedisplay()

    if key == GLUT_KEY_UP:  # ^
        pieces[selected].translate(0, 2)
        glutPostRedisplay()

    if key == GLUT_KEY_DOWN:  # ^
        pieces[selected].translate(0, -2)
        glutPostRedisplay()

def displayMe():
    """
    FUncion para dibujar en pantalla
    """
    glClear(GL_COLOR_BUFFER_BIT)
    drawMenu()
    drawOriginalFigure()
    drawPiecesFigure()
    glutSwapBuffers()


def readTexture(filename):
    """
    FUncion para generar la textura
    :param filename: DIreccion del archivo
    :return: el id de la textura
    """
    img = Image.open(filename)
    # img = img.convert("RGB")
    img_data = numpy.array(list(img.getdata()), numpy.int8)
    texture_id = glGenTextures(1)
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST)
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL)
    # glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.size[0], img.size[1], 0, GL_RGB, GL_UNSIGNED_BYTE, img_data)
    format = GL_RGB if img.mode == "RGB" else GL_RGBA
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.size[0], img.size[1], 0, format, GL_UNSIGNED_BYTE, img_data)
    return texture_id


def main():
    """
    FUncion main
    """
    printInteraction()
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
    glutInitWindowPosition(100, 100)
    glutInitWindowSize(AnchuraVentana, AlturaVentana)
    glutCreateWindow(b"Practica de recuperacion | Rompecabezas con texturas")
    glutReshapeFunc(resize)
    glutDisplayFunc(displayMe)
    glutKeyboardFunc(keyInput)
    glutSpecialFunc(specialKeyInput)
    init()
    glutMainLoop()


if __name__ == "__main__":
    buildPieces()
    main()
