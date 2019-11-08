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

# Initial values
AlturaVentana = 375
AnchuraVentana = 1000

texture_id = 0


# FUncion para dibujar texto
def drawTextOnDisplay(string):
    for character in string:
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ord(character))


def printInteraction():
    print("Interaction:")
    print("Press +/- to increase/decrease the number of vertices on the circle.")
    print("Press [ESCAPE] to finish.")


def init():
    # red, green, blue, alpha from 0.0 to 1.0
    global numVertices  # Le dices al python que estas modicando una variable global y no una local de nombre numvertices
    glClearColor(1.0, 1.0, 1.0, 0.0)
    texture_id = read_texture('garfield.jpeg')


# Keep the aspect ratio of the graphics window and
# anything we draw will look in proper proportion
# OpenGL set w and h values as the graphics window's size changes
def resize(w, h):
    if h == 0:
        h = 1
    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(-250, 250, -40, 200.0, -1.0, 1.0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()


def keyInput(key, x, y):
    global numVertices  # Le dices al python que estas modicando una variable global y no una local de nombre numvertices
    if key == b'\053':  # ESCAPE
        glutPostRedisplay()

    if key == b'\055':  # +
        glutPostRedisplay()

    if key == b'\033':  # -
        sys.exit()


def displayMe():
    glClear(GL_COLOR_BUFFER_BIT)
    # division vertical
    glColor3f(0, 0, 0)
    #anadir texto
    glRasterPos3f(-180.0, -20.0, 0.0)
    drawTextOnDisplay('Imagen original')

    #anadir linea vertical
    glBegin(GL_LINES)
    glVertex3f(0, -40, 0)
    glVertex3f(0, 220, 0)
    glEnd()

    # genera cuadro izquierdo
    glBindTexture(GL_TEXTURE_2D, texture_id)  # This is what's missing
    glEnable(GL_TEXTURE_2D)
    glBindTexture(GL_TEXTURE_2D, texture_id)

    #anadir imagen original
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

    glFlush()


def read_texture(filename):
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
