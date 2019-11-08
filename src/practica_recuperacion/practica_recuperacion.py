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

# VAlores iniciales
AlturaVentana = 375
AnchuraVentana = 1000

# textura
texture_id = 0

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
    # anadir nombre de la figura original
    glColor3f(0, 0, 0)
    drawTextOnPosition2D(-180,-20,'Imagen original')

    # anadir linea vertical
    glBegin(GL_LINES)
    glVertex3f(0, -40, 0)
    glVertex3f(0, 220, 0)
    glEnd()

    # generar cuadro izquierdo
    glBindTexture(GL_TEXTURE_2D, texture_id)
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
    #generacion del orto
    glOrtho(-250, 250, -40, 200.0, -1.0, 1.0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()

def keyInput(key, x, y):
    """
    FUncion para el evento key
    :param key: tecla de entrada
    :param x: en que posicion x
    :param y: en que posicion y
    """
    if key == b'\053':  # ESCAPE
        glutPostRedisplay()

    if key == b'\055':  # +
        glutPostRedisplay()

    if key == b'\033':  # -
        sys.exit()

def displayMe():
    """
    FUncion para dibujar en pantalla
    """
    glClear(GL_COLOR_BUFFER_BIT)
    drawOriginalFigure()
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
    init()
    glutMainLoop()

main()
