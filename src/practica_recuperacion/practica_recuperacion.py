# Ejecucion:
# python3 practica_recuperacion nombre_archivo

from OpenGL.GLUT import *  # GL Utilities Toolkit
from OpenGL.GL import *
from OpenGL.GLU import *
import math
import random
import sys
from PIL import Image
import numpy
from enum import Enum

# VAlores iniciales
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


class Pieze:
    orientation = 0
    position = 0
    points = []
    pointsForTexture = []
    pointStart = Point(0,0)
    translateX = 0
    translateY = 0
    setCurve = []
    def __init__(self, x, y):
        self.pointStart = Point(x, y)
        self.points = []
        self.pointsForTexture= []
        self.translateX = 0
        self.translateY = 0
        self.setCurve[:] = []
        # -1 -> Lineal
        # 0 -> to Down (hacia dentro)
        # 1 -> to Up (hacia fuera)
        self.setCurve= [-1,-1,-1,-1]

    def generatePoints(self):
        for r in range(1,5):
            if r == 1 or r == 3 :
                for n in numpy.arange(0, SIZE_FIG_HEIGHT + 1,1):
                    if r == 1: #LEFT
                        self.points.append(Point(self.pointStart.getX(),
                                                 self.pointStart.getY() + n))
                        self.pointsForTexture.append(Point(self.pointStart.getX()/WIDTH_FIG,
                                                    (self.pointStart.getY() + n)/HEIGHT_FIG))
                    elif r == 3: #RIGHT
                        self.points.append(Point(self.pointStart.getX() + SIZE_FIG_WIDTH,
                                                 (self.pointStart.getY() + SIZE_FIG_HEIGHT) - n))
                        self.pointsForTexture.append(Point((self.pointStart.getX() + SIZE_FIG_WIDTH)/WIDTH_FIG,
                                                 ((self.pointStart.getY()+ SIZE_FIG_HEIGHT) - n)/HEIGHT_FIG))
            else:
                for n in numpy.arange(0,SIZE_FIG_WIDTH+1,1):
                    if r == 2: #TOP
                        self.points.append(Point(self.pointStart.getX() + n,
                                                 self.pointStart.getY() + SIZE_FIG_HEIGHT))
                        self.pointsForTexture.append(Point((self.pointStart.getX() + n) / WIDTH_FIG,
                                                           (self.pointStart.getY() + SIZE_FIG_HEIGHT) / HEIGHT_FIG))
                    elif r == 4: # BOTTOM
                        self.points.append(Point((self.pointStart.getX() + SIZE_FIG_WIDTH) - n,
                                                 self.pointStart.getY()))
                        self.pointsForTexture.append(Point(((self.pointStart.getX() + SIZE_FIG_WIDTH) - n) / WIDTH_FIG,
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
        self.points[:] = []
        self.pointsForTexture[:] = []
        for r in range(1, 5):
            if r == 1 or r == 3:
                for n in numpy.arange(0, SIZE_FIG_HEIGHT + 1, 1):
                    if r == 1:
                        self.points.append(Point(self.pointStart.getX() + self.translateX,
                                                 self.pointStart.getY() + n + self.translateY))
                        self.pointsForTexture.append(Point(self.pointStart.getX() / WIDTH_FIG,
                                                           (self.pointStart.getY() + n) / HEIGHT_FIG))
                    elif r == 3:
                        self.points.append(Point(self.pointStart.getX() + SIZE_FIG_WIDTH + self.translateX,
                                                 (self.pointStart.getY() + SIZE_FIG_HEIGHT + self.translateY) - n))
                        self.pointsForTexture.append(Point((self.pointStart.getX() + SIZE_FIG_WIDTH) / WIDTH_FIG,
                                                           ((
                                                                        self.pointStart.getY() + SIZE_FIG_HEIGHT) - n) / HEIGHT_FIG))
            else:
                for n in numpy.arange(0, SIZE_FIG_WIDTH + 1, 1):
                    if r == 2:
                        self.points.append(Point(self.pointStart.getX() + n + self.translateX,
                                                 self.pointStart.getY() + SIZE_FIG_HEIGHT + self.translateY))
                        self.pointsForTexture.append(Point((self.pointStart.getX() + n) / WIDTH_FIG,
                                                           (self.pointStart.getY() + SIZE_FIG_HEIGHT) / HEIGHT_FIG))
                    elif r == 4:
                        self.pointsForTexture.append(Point(((self.pointStart.getX() + self.translateX + SIZE_FIG_WIDTH) - n) / WIDTH_FIG,
                                                           (self.pointStart.getY()+self.translateY) / HEIGHT_FIG))
                        self.pointsForTexture.append(Point(((self.pointStart.getX() + SIZE_FIG_WIDTH) - n) / WIDTH_FIG,
                                                           (self.pointStart.getY() + SIZE_FIG_HEIGHT) / HEIGHT_FIG))

        # print('des ', len(self.points))
        # print('des ', len(self.pointsForTexture))
    def __repr__(self):
        return str(self.pointStart.x)+ ' '+ str(self.pointStart.y)

def buildPieces():
    global pieces
    figY = 0
    for y in numpy.arange(0, HEIGHT_FIG, SIZE_FIG_HEIGHT):
        figX = 0
        for x in numpy.arange(0, WIDTH_FIG, SIZE_FIG_WIDTH):
            piece = Pieze(x,y)
            piece.generatePoints()
            # piece.translate(0, 0)
            pieces.append(piece)
            print(str(figX),' ', str(figY))
            if x == 0 and y == x:
                print('')
            figX += 1
        figY += 1


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
    # dibuja la textura del objecto seleccionado
    glBegin(GL_POLYGON)
    p = pieces[selected].getPoints()
    for i in range(0, p.__len__()):
        glTexCoord2f(1 - pieces[selected].getPointForTexture(i).getX(), (1 - pieces[selected].getPointForTexture(i).getY()))
        glVertex3f(p[i].getX(), p[i].getY(), 0)
    glEnd()
    glDisable(GL_TEXTURE_2D)
    # dibuja la linea que sobresale de la pieza
    glBegin(GL_LINE_LOOP)
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
    drawTextOnPosition2D(-240, 180, 'SPACE para cambiar la figura')
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
    print("Press ARROW LEFT/RIGHT/TOP/BOTTOM to finish.")
    print("Press [ESCAPE] to finish.")


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
    glFlush()


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
