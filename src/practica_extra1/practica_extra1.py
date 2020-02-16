# Practica NO 3:
# Nombre completo

from OpenGL.GLUT import *
from OpenGL.GL import *
from OpenGL.GLU import *
import numpy
import math

PI=3.14159265358979324

#bandera de animacion
OPENIT=False

MAX_RADIUS = 80
MAX_DISTANCE = MAX_RADIUS*PI*2

AUX_DISTANCE = 0.0

POS_CIRC_X = 120
POS_CIRC_Y = 100

#contador para los circulos
COUNT_CIRCLES = 2

# arreglos para guardar los parametros de cada circulo mostrado
# en la parte inferior
AUX_DISTANCES = []
MAX_DISTANCES = []
MAX_RADIOS = []
GRADES = []

# Dimensiones de la pantalla
WidthWin = 400
HeightWin = 800

#timer
refreshMillis = 100


def setMaxDistances():
    """
    Funcion para configurar los arreglos y las maximas distancias recorridas
    para cada circuferencia
    """
    global MAX_DISTANCES,AUX_DISTANCES, MAX_RADIOS,GRADES
    AUX_DISTANCES = []
    MAX_DISTANCES = []
    MAX_RADIOS = []
    GRADES = []
    # aqui se anaden los valores iniciales
    for i in range(1, COUNT_CIRCLES+1):
        _radius = MAX_RADIUS / COUNT_CIRCLES * i
        MAX_RADIOS.append(_radius)
        MAX_DISTANCES.append(_radius*PI*2)
        AUX_DISTANCES.append(0.0)
        GRADES.append(0.0)

# Funcion para dibujar un circulo
def drawCircle(radius, posX, posY, cantGrades):
    # max 360
    glBegin(GL_LINE_STRIP)
    for i in range(cantGrades):
        angle = 2 * PI * i / 360
        y = math.cos(angle) * radius
        x = math.sin(angle) * radius
        glVertex2d(x + posX, y + posY)
    glEnd()

# Funcion para dibujar una linea
def drawLine(x1,y1,x2,y2):
    glBegin(GL_LINES)
    glVertex3f(x1, y1, 0)
    glVertex3f(x2, y2, 0)
    glEnd()

# Funcion para dibujar los circulos de la parte superior
def drawCircleTop(cant_circles, posX, poxY, radius, cant_grades):
    # Dibuja los circulos de en medio de acuerdo al total de circulos a dibujar
    # Para que el radio fuera equitativo se dividio
    # entre no total de circulos por el contador
    for i in range(1, cant_circles + 1):
        drawCircle(radius / cant_circles * i, posX, poxY, cant_grades )

# Funcion para dibujar los circulos de la parte inferior
def drawCirclesBottom(posX, posY):
    global OPENIT
    # Dibuja los circulos de en medio de acuerdo al total de circulos a dibujar
    for i in range(1, COUNT_CIRCLES + 1):
        # de acuerdo al radio se obtiene los grados con una operacion de los radianes
        GRADES[i-1] = (AUX_DISTANCES[i-1] * 180 / PI) / MAX_RADIOS[i-1]
        # Si los grados superan a los 360 se establece que el limite maximo sea 360
        if GRADES[i-1] >=360:
            GRADES[i-1] = 360
        else:
            drawCircle(MAX_RADIOS[i-1], posX + AUX_DISTANCES[i-1], posY, 360  - int(GRADES[i-1]))
        # SI los la longitud de los grados superan al radio se reinicia
        if (GRADES[i-1] >= 360 and i == COUNT_CIRCLES):
            OPENIT = False
        #DIbujar linea
        drawLine(posX, posY + MAX_RADIOS[i - 1] - (MAX_RADIUS / COUNT_CIRCLES), posX + AUX_DISTANCES[i - 1], posY + MAX_RADIOS[i - 1] - (MAX_RADIUS / COUNT_CIRCLES))
        drawLine(posX, posY + MAX_RADIOS[i-1], posX + AUX_DISTANCES[i-1], posY + MAX_RADIOS [i-1])
        drawLine(posX + AUX_DISTANCES[i - 1], posY + MAX_RADIOS[i - 1] - (MAX_RADIUS / COUNT_CIRCLES), posX + AUX_DISTANCES[i-1], posY + MAX_RADIOS [i-1])

# FUncion para el timer
def timer(value):
    global refreshMillis, OPENIT, AUX_DISTANCES
    # SI openit esta en true
    # se realiza la animacion
    if OPENIT == True:
        #se recorre el arreglo de cada una de las distancias
        #y se actualiza los valores de las distancias recorridas
        for indice in range(len(AUX_DISTANCES)):
            if not GRADES[indice] >=360:
                AUX_DISTANCES[indice] = AUX_DISTANCES[indice] + 2
    # Refresca la pantalla
    glutPostRedisplay()
    refreshMillis = refreshMillis - 1
    if refreshMillis <= 10:
        refreshMillis  = 1
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
    global COUNT_CIRCLES, OPENIT, AUX_DISTANCES
    if key == b'\053':  # +
        if COUNT_CIRCLES > 10:
            COUNT_CIRCLES = 10
        COUNT_CIRCLES = COUNT_CIRCLES + 1
        setMaxDistances()
        # Refresca la pantalla
        glutPostRedisplay()

    elif key == b'\055':  # -
        COUNT_CIRCLES = COUNT_CIRCLES - 1
        if COUNT_CIRCLES <= 1:
            COUNT_CIRCLES = 2
        setMaxDistances()
        # Refresca la pantalla
        glutPostRedisplay()
    elif key == b'\040':
        OPENIT = not OPENIT
        for indice in range(len(AUX_DISTANCES)):
            AUX_DISTANCES[indice] = 0
    elif key == b'\033':  # ESCAPE
        sys.exit()

# Display
def displayMe():
    global COUNT_CIRCLES
    glClear(GL_COLOR_BUFFER_BIT)
    glColor3f(1.0, 0.0, 0.0)
    # Drawing circle base 1 (top)
    drawCircle(MAX_RADIUS, POS_CIRC_X, POS_CIRC_Y, 360)
    # Drawing cicles bottom
    drawCircleTop(COUNT_CIRCLES, POS_CIRC_X, POS_CIRC_Y, MAX_RADIUS,360)
    glColor3f(0.0, 0.0, 0.0)
    #Dibujar la linea que inicia en el centro del circulo y termina en la circuferencia
    drawLine(POS_CIRC_X, POS_CIRC_Y, POS_CIRC_X, POS_CIRC_Y + MAX_RADIUS)
    # Dibujar la linea que inicia en el centro del circulo y termina en la circuferencia
    drawLine(POS_CIRC_X, POS_CIRC_Y + 180 , POS_CIRC_X, POS_CIRC_Y + MAX_RADIUS +180)
    # print(str(AUX_DISTANCE))
    #Dibujar textos del circulo superior
    drawingTextBase1()
    #Dibujar los textos de parte inferior
    drawingTextBottom()
    #Dibujar los textos de presentacion
    drawingTextMain()
    #Dibujar los circulos de abajo
    drawCirclesBottom(POS_CIRC_X, POS_CIRC_Y + 180)

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

#DIbujar los textos de la parte inferior
def drawingTextBottom():
    glColor3d(0, 0, 0)
    glRasterPos3f(POS_CIRC_X -10 , POS_CIRC_Y + 180 + (MAX_RADIUS/2), 0.0)
    drawTextOnDisplay('r')
    glRasterPos3f(POS_CIRC_X + (MAX_DISTANCES[-1]/2), POS_CIRC_Y + 200 + MAX_RADIUS, 0.0)
    drawTextOnDisplay('2*PI*r')

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
    setMaxDistances()
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
