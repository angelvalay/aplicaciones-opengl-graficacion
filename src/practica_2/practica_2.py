# Practica 2:
# python3 practica_2
# Angel Armando Valay Martinez

from OpenGL.GLUT import *
from OpenGL.GL import *
from OpenGL.GLU import *
import math
import random
import sys

# Dimensiones de la pantalla
WidthWin = 480
HeightWin = 640

# Angulos y valores iniciales del diagrama
AngleAlpha = 45.00
AngleBeta = 45.00
NewtonForce = 20

# Fuerzas
F1x = 0
F1y = 0
F1 = 0

F2x = 0
F2y = 0
F2 = 0

Fx = 0
Fy = 0

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

# Clase para generar el triangulo
class Triangle:
	def __init__(self, hip, leg1, leg2):
		self._hip = hip
		self._leg1 = leg1
		self._leg2 = leg2

	def draw_color(self, red, green, blue):
		glColor3d(red, green, blue)
		self._hip.draw_points()
		self._leg1.draw_points()
		self._leg2.draw_points()
		self._hip.draw()
		self._leg1.draw()
		self._leg2.draw()

	@property
	def hip(self):
		return self._hip

	@property
	def leg1(self):
		return self._leg1

	@property
	def leg2(self):
		return self._leg2

# Clase para generar el cuadro
class Square:
	def __init__(self, x1, y1, x2, y2, x3, y3, x4, y4):
		self._x1 = x1
		self._x2 = x2
		self._x3 = x3
		self._x4 = x4
		self._y1 = y1
		self._y2 = y2
		self._y3 = y3
		self._y4 = y4

	def draw_color(self, red, green, blue):
		glColor3d(red, green, blue)
		glBegin(GL_POLYGON)
		glVertex3f(self._x1, self._y1, 0)
		glVertex3f(self._x2, self._y2, 0)
		glVertex3f(self._x3, self._y3, 0)
		glVertex3f(self._x4, self._y4, 0)
		glEnd()

	def draw_color_inline(self, red, green, blue):
		glColor3d(red, green, blue)
		# glColor3d(0.1, 0.5, 0.6)
		# glEnable(GL_LINE_STIPPLE)
		# glLineStipple(1, 0x00FF)
		glBegin(GL_LINES)
		glVertex3f(self._x1, self._y1, 0)
		glVertex3f(self._x2, self._y2, 0)
		glVertex3f(self._x3, self._y3, 0)
		glVertex3f(self._x4, self._y4, 0)
		glEnd()
		# glDisable(GL_LINE_STIPPLE)

class Arrow:
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

	def draw_color(self, red, green, blue):
		glColor3d(red, green, blue)
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

# Hipotenusa
hypotenuse = Line(-80, 80, 20, 80)
# Cateto 1
leg1 = Line(-80, 80, 20, 80)
# Cateto 2
leg2 = Line(-80, 80, 20, 80)
# Generar el triangulo
triangle = Triangle(hypotenuse, leg1, leg2)
# Generar cuadrado
square = Square(-10, 10, 10, 10, 10, -10, -10, -10)
# Generar cuadro de puntas
squareInline = Square(0, 0, 0, 0, 0, 0, 0, 0)

# Generar flecha ARRIBA
arrowUp = Arrow(0, 0, 0, 0)
arrowDown = Arrow(0, 0, 0, 0)
arrowLeft = Arrow(0, 0, 0, 0)
arrowRight = Arrow(0, 0, 0, 0)


def calculateForces():
	global F1x, F2x, F1y, F2y, NewtonForce, Fx, Fy, F1, F2
	####### CALCULO DE LAS FUERZAS A TRAVES DE LA LEY DE SENOS
	F1x = -NewtonForce / (math.tan(math.radians(AngleAlpha)) + math.tan(math.radians(AngleBeta)))
	# print(F1x)
	F2x = NewtonForce / (math.tan(math.radians(AngleAlpha)) + math.tan(math.radians(AngleBeta)))
	# print(F2x)
	F1y = (NewtonForce * math.tan(math.radians(AngleAlpha))) / (math.tan(math.radians(AngleAlpha)) + math.tan(math.radians(AngleBeta)))
	# print(F1y)
	F2y = (NewtonForce * math.tan(math.radians(AngleBeta))) / (math.tan(math.radians(AngleAlpha)) + math.tan(math.radians(AngleBeta)))
	# print(F2y)
	F1 = math.sqrt(F1x**2 + F1y**2)
	# print(F1)
	F2 = math.sqrt(F2x**2 + F2y**2)
	# print(F2)
	Fx = F1x + F2x
	Fy = F1y + F2y
	# print("FX " + str(Fx))
	# print("FY" + str(Fy))

#Dibujar textos en la pantalla
def drawText():
	glRasterPos3f(30.0, 50.0, 0.0)
	drawTextOnDisplay('Alpha -> '+ str(AngleAlpha))
	glRasterPos3f(30.0, 40.0, 0.0)
	drawTextOnDisplay('Beta -> '+ str(AngleBeta))
	glRasterPos3f(30.0, 30.0, 0.0)
	drawTextOnDisplay('W -> '+ str(NewtonForce))
	glRasterPos3f(30.0, 20.0, 0.0)
	drawTextOnDisplay('|F1| -> '+ str(round(F1, 2)) + " N")
	glRasterPos3f(30.0, 10.0, 0.0)
	drawTextOnDisplay('|F2| -> '+ str(round(F2, 2)) + " N")
	glRasterPos3f(30.0, -10.0, 0.0)
	drawTextOnDisplay('F   -> '+ str(round(Fx, 2)))
	glRasterPos3f(46.0, -20.0, 0.0)
	drawTextOnDisplay(str(round(Fy, 2)))
	glRasterPos3f(30.0, -40.0, 0.0)
	drawTextOnDisplay('F1 -> '+ str(round(F1x, 2)))
	glRasterPos3f(46.0, -50.0, 0.0)
	drawTextOnDisplay(str(round(F1y, 2)))
	glRasterPos3f(30.0, -70.0, 0.0)
	drawTextOnDisplay('F2 -> '+ str(round(F2x, 2)))
	glRasterPos3f(46.0, -80.0, 0.0)
	drawTextOnDisplay(str(round(F2y, 2)))

# DIbujar cuadrado
def drawSquare():
	global square
	posXSquare = triangle.leg1.x2
	posYSquare = triangle.leg1.y2
	# print(posXSquare)
	# print(posYSquare)
	square = Square(posXSquare -5 , posYSquare,
					posXSquare + 5, posYSquare,
					posXSquare + 5, posYSquare - 10,
					posXSquare -5, posYSquare - 10)

# Dibuja flechas
def drawArrows():
	global arrowDown, arrowLeft, arrowRight, arrowUp, squareInline, Fx, Fy
	posXSquare = triangle.leg1.x2
	posYSquare = triangle.leg1.y2
	squareInline = Square(posXSquare, posYSquare + NewtonForce,
						  posXSquare + F2x, posYSquare + F2y,
						  posXSquare, posYSquare,
						  posXSquare + F1x, posYSquare + F1y)
	squareInline.draw_color(0.7, 0.6, 0.9)
	arrowUp = Arrow(posXSquare, posYSquare, posXSquare + Fx, posYSquare + Fy)
	arrowUp.draw_color(0.1, 0.1, 0.4)
	arrowDown = Arrow(posXSquare, posYSquare, posXSquare, posYSquare - NewtonForce)
	arrowDown.draw_color(0.9, 0.1, 0.6)
	arrowLeft = Arrow(posXSquare, posYSquare, posXSquare + F1x, F1y + posYSquare)
	arrowLeft.draw_color(0.7, 0.6, 0.2)
	arrowRight = Arrow(posXSquare, posYSquare, posXSquare + F2x, F2y + posYSquare)
	arrowRight.draw_color(0.9, 0.1, 0.36)

# Dibujar triangulo principal
def drawTriangule():
	global AngleAlpha
	global AngleBeta
	angleC = 180 - (AngleAlpha + AngleBeta)

	# condicion para evitar error de division sobre zero
	if angleC <= 0:
		return void

	# print('a-> ', AngleAlpha)
	# print('b-> ', AngleBeta)
	# print('c-> ', angleC)
	# print('')

	# Calculo por ley de senos para la longitud
	lengthLeg1 = (100 * math.sin(math.radians(AngleBeta)))/math.sin(math.radians(angleC))
	lengthLeg2 = (100 * math.sin(math.radians(AngleAlpha)))/math.sin(math.radians(angleC))
	# print(lengthLeg1)
	# print(lengthLeg2)

	angleAux = 90 - AngleAlpha
	angleAux2 = 90 - AngleBeta

	# LOngitudes de los catetos del triangulo
	longX = lengthLeg1 * math.sin(math.radians(angleAux))
	longY = lengthLeg1 * math.sin(math.radians(AngleAlpha))
	longX2 = lengthLeg2 * math.sin(math.radians(angleAux2))
	longY2 = lengthLeg2 * math.sin(math.radians(AngleBeta))

	# Asignacion de logitudes al triangulo
	triangle.leg1.x1 = triangle.hip.x1
	triangle.leg1.y1 = triangle.hip.y1

	triangle.leg1.x2 = triangle.hip.x1 + longX
	triangle.leg1.y2 = triangle.hip.y1 - longY

	triangle.leg2.x1 = triangle.hip.x2
	triangle.leg2.y1 = triangle.hip.y2

	triangle.leg2.x2 = triangle.hip.x2 - longX2
	triangle.leg2.y2 = triangle.hip.y2 - longY2

	# Cada que los calculos para generar los catetos son ejecutados
	# Se calculan las fuerzas
	calculateForces()
	# Se dibuja el cuadrado
	drawSquare()
	# SE dibuja el texto
	drawText()
	# SE dibuja las flechas
	drawArrows()


# PAra mostrar las opciones
def printInteraction():
	print("Interaction:")
	print("Presiona +/- para incrementar/decrementar la fuerza W(Newtons) que se aplica.")
	print("Presiona [ESCAPE] para finalizar.")
	print("Presiona L/l para incrementar/decrementar el angulo aplha.")
	print("Presiona R/r para incrementar/decrementar el angulo beta")

# FUncion para iniciar
def init():
	glClearColor(1.0, 1.0, 1.0, 0.0)

#FUncion para redimensionar la pantalla
def resize(w, h): 
	if h == 0:
		h = 1
	glViewport(0, 0, w, h)
	glMatrixMode(GL_PROJECTION)
	glLoadIdentity()
	glOrtho(-100, 100.0, -100, 100.0, -1.0, 1.0)
	glMatrixMode(GL_MODELVIEW)
	glLoadIdentity()

#Evento key del teclado
def keyInput(key, x, y):

	global AngleAlpha
	global AngleBeta
	global NewtonForce

	if key == b'\053':  # +
		if NewtonForce < 100:
			NewtonForce = NewtonForce + 1
			drawTriangule()
		# Refresca la pantalla
		glutPostRedisplay()
		
	elif key == b'\055':  # -
		if NewtonForce > 0:
			NewtonForce = NewtonForce - 1
			drawTriangule()
		# Refresca la pantalla
		glutPostRedisplay()

	elif key == b'\114':  # L
		if AngleAlpha < 90:
			AngleAlpha = AngleAlpha + 1
			drawTriangule()
			# Refresca la pantalla
			glutPostRedisplay()

	elif key == b'\122':  # R
		if AngleBeta < 90:
			AngleBeta = AngleBeta + 1
			drawTriangule()
			# Refresca la pantalla
			glutPostRedisplay()

	elif key == b'\154':  # l
		if AngleAlpha > 0:
			AngleAlpha = AngleAlpha - 1
			drawTriangule()
			# Refresca la pantalla
			glutPostRedisplay()

	elif key == b'\162':  # r
		if AngleBeta > 0:
			AngleBeta = AngleBeta - 1
			drawTriangule()
			# Refresca la pantalla
			glutPostRedisplay()

	elif key == b'\033':  # ESCAPE
		sys.exit()

# DIsplay
def displayMe():
	glClear(GL_COLOR_BUFFER_BIT)
	glColor3f(0.0, 0.0, 0.0)
	drawTriangule()
	triangle.draw_color(0.0, 0.6, 0.4)
	square.draw_color(0.6, 0.9, 0.4)
	glColor3d(0,0,0)
	glRasterPos3f(-90.0, -70.0, 0.0)
	drawTextOnDisplay('Angel Armando Valay Martinez')
	glRasterPos3f(-90.0, -80.0, 0.0)
	drawTextOnDisplay('Practica 2 | Aplicación de vectores en física')
	glRasterPos3f(-90.0, -90.0, 0.0)
	drawTextOnDisplay('Introduccion a la Graficación por Computadora')
	glFlush()

# FUncion para dibujar texto
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
	glutCreateWindow("Aplicacion de vectores en fisica | Practica 2")
	glutReshapeFunc(resize)
	glutDisplayFunc(displayMe)
	glutKeyboardFunc(keyInput)
	init()
	glutMainLoop()

# EJecutando el main
main()
