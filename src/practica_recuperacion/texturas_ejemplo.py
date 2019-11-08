# Ejecucion:
# python3 HolaOpenGL.py

from OpenGL.GLUT import *  # GL Utilities Toolkit
from OpenGL.GL import *
from OpenGL.GLU import *
import math
import random
import sys
from PIL import Image
# INVESTIGUEN COMO INSTALAR PIL
# les evito la fatiga, hagan esto:
# sudo apt-get install python3-pil
import numpy

global t
global R
global X
global Y
global PI
global AnchuraVentana
global AlturaVentana
global numVertices

# Initial values
AlturaVentana = 480
AnchuraVentana = 640

t = 0.0
R = 40.0
X = 50.0
Y = 50.0
PI = 3.14159265358979324

texture_id = 0


def printInteraction():
    print("Interaction:")
    print("Press +/- to increase/decrease the number of vertices on the circle.")
    print("Press [ESCAPE] to finish.")


def init():
    # red, green, blue, alpha from 0.0 to 1.0
    global numVertices  # Le dices al python que estas modicando una variable global y no una local de nombre numvertices
    glClearColor(1.0, 1.0, 1.0, 0.0)
    numVertices = 5
    texture_id = read_texture('mars.png')


# Keep the aspect ratio of the graphics window and
# anything we draw will look in proper proportion
# OpenGL set w and h values as the graphics window's size changes
def resize(w, h):
    if h == 0:
        h = 1
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity()


def keyInput(key, x, y):
    global numVertices  # Le dices al python que estas modicando una variable global y no una local de nombre numvertices
    if key == b'\053':  # ESCAPE
        numVertices = numVertices + 1
        glutPostRedisplay();

    if key == b'\055':  # +
        if (numVertices > 3):
            numVertices = numVertices - 1
        glutPostRedisplay();

    if key == b'\033':  # -
        sys.exit()


def displayMe():
    glClear(GL_COLOR_BUFFER_BIT)

    glColor3f(0.0, 0.0, 0.0)
    glPointSize(5)

    # Draw a line loop with vertices at equal angles apart on a circle
    # with center at (X, Y) and radius R, The vertices are colored randomly.
    glBegin(GL_LINE_LOOP);
    t = 0.0
    #	print ("T",t,"R:",R,"X:",X,"Y:",Y)

    for i in range(0, numVertices):
        glColor3ub(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255));
        X1 = X + R * math.cos(t);
        Y1 = Y + R * math.sin(t);
        glVertex3f(X1, Y1, 0.0);
        t += 2 * PI / numVertices
    glEnd();

    glColor3ub(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255));

    glBindTexture(GL_TEXTURE_2D, texture_id)  # This is what's missing
    glEnable(GL_TEXTURE_2D)
    glBindTexture(GL_TEXTURE_2D, texture_id)

    glBegin(GL_POLYGON)
    glTexCoord2f(0.0, 0.0)
    glVertex3f(30.0, 30.0, 1.0)
    glTexCoord2f(0.0, 1.0)
    glVertex3f(30.0, 60.0, 1.0)
    glTexCoord2f(1.0, 1.0)
    glVertex3f(60.0, 60.0, 1.0)
    glTexCoord2f(1.0, 0.0)
    glVertex3f(60.0, 30.0, 1.0)
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
    glutCreateWindow(b"Poligono Regular de N Lados en OpenGL Python")
    glutReshapeFunc(resize)
    glutDisplayFunc(displayMe)
    glutKeyboardFunc(keyInput)

    init()
    glutMainLoop()


main()