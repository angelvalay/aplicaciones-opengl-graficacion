import numpy as np
UNIT_CUBE = 1
#types of figures
FIG_LINEAL = 0 # |
FIG_L = 1 # L
FIG_S = 2 # S
FIG_CUBE = 3 # []
class wall:
    width = 1 # anchura de la malla
    height = 1 # altura de la malla
    axis = 'X' # eje donde se hara la malla
    start_point = (0,0,0) #punto de comienzo

    def __init__(self, width, height, start_point, axis):
        """
        Constructor para inicializar una malla
        :param width: Anchura de la malla
        :param height: Altura de la malla
        :param start_point: Una tupla de 3 valores (x,y,z)
        :param axis: Un caracter para determinar que eje
        """
        self.width = width
        self.height = height
        self.start_point = start_point
        self.axis = axis

    def getPoints(self):
        """
        Funcion para crear los puntos necesarios para crear la malla
        :return: Una lista de un array de longitud 3
        """
        # se inicializa el arreglo
        points = []
        # este ciclo me permite crear los puntos sobre la anchura
        for x in range (0,self.width + 1, UNIT_CUBE):
            y = self.height
            if self.axis == 'X':
                # se agrega de un lado
                points.append([0,x,y])
                # se agrega del otro extremo
                points.append([0,x,0])
            elif self.axis == 'Y':
                # se agrega de un lado
                points.append([x,0,y])
                # se agrega del otro extremo
                points.append([x,0,0])
            elif self.axis == 'Z':
                # se agrega de un lado
                points.append([x,y,0])
                # se agrega del otro extremo
                points.append([x,0,0])
        # este ciclo me permite crear los puntos sobre la altura
        for y in range(0, self.height + 1, UNIT_CUBE):
            x = self.width
            if self.axis == 'X':
                # se agrega de un lado
                points.append([0, x, y])
                # se agrega del otro extremo
                points.append([0, 0, y])
            elif self.axis == 'Y':
                # se agrega de un lado
                points.append([x, 0, y])
                # se agrega del otro extremo
                points.append([0, 0, y])
            elif self.axis == 'Z':
                # se agrega de un lado
                points.append([x, y, 0])
                # se agrega del otro extremo
                points.append([0, y, 0])
        return points

class cube:
    _centerX = 0
    _centerY = 0
    _centerZ = 0
    _pointsCube = []

    def __init__(self, centerX, centerY, centerZ):
        # print(centerX, ' ',centerY,' ', centerZ)
        self._centerX = centerX
        self._centerY = centerY
        self._centerZ = centerZ
        self.generatePoints()

    def generatePoints(self):
        self._pointsCube = []
        #Punto 1 [-,+,-]
        self._pointsCube.append([self._centerX - (UNIT_CUBE/2),
                                 self._centerY + (UNIT_CUBE/2),
                                 self._centerZ - (UNIT_CUBE/2)])
        # Punto 2 [+,+,-]
        self._pointsCube.append([self._centerX + (UNIT_CUBE / 2),
                                 self._centerY + (UNIT_CUBE / 2),
                                 self._centerZ - (UNIT_CUBE / 2)])
        # Punto 3 [-,+,+]
        self._pointsCube.append([self._centerX - (UNIT_CUBE / 2),
                                 self._centerY + (UNIT_CUBE / 2),
                                 self._centerZ + (UNIT_CUBE / 2)])
        # Punto 4 [+,+,+]
        self._pointsCube.append([self._centerX + (UNIT_CUBE / 2),
                                 self._centerY + (UNIT_CUBE / 2),
                                 self._centerZ + (UNIT_CUBE / 2)])
        # Punto 5 [-,-,+]
        self._pointsCube.append([self._centerX - (UNIT_CUBE / 2),
                                 self._centerY - (UNIT_CUBE / 2),
                                 self._centerZ + (UNIT_CUBE / 2)])
        # Punto 6 [-,-,-]
        self._pointsCube.append([self._centerX - (UNIT_CUBE / 2),
                                 self._centerY - (UNIT_CUBE / 2),
                                 self._centerZ - (UNIT_CUBE / 2)])
        # Punto 7 [+,-,-]
        self._pointsCube.append([self._centerX + (UNIT_CUBE / 2),
                                 self._centerY - (UNIT_CUBE / 2),
                                 self._centerZ - (UNIT_CUBE / 2)])
        # Punto 8 [+,-,+]
        self._pointsCube.append([self._centerX + (UNIT_CUBE / 2),
                                 self._centerY - (UNIT_CUBE / 2),
                                 self._centerZ + (UNIT_CUBE / 2)])
    @property
    def centerX(self):
        return self._centerX

    @centerX.setter
    def centerX(self, val):
        self._centerX = val

    @property
    def centerY(self):
        return self._centerY

    @centerY.setter
    def centerY(self, val):
        self._centerY = val

    @property
    def centerZ(self):
        return self._centerZ

    @centerZ.setter
    def centerZ(self, val):
        self._centerZ = val

    @property
    def pointsCube(self):
        return self._pointsCube

    @pointsCube.setter
    def pointsCube(self, val):
        self._pointsCube = val

    def getPointToArray(self):
        return [self._centerX, self._centerY ,self._centerZ]

    def faces(self, numberFace):
        subPoints = []
        if numberFace == 1:
            subPoints.append(self._pointsCube[0])
            subPoints.append(self._pointsCube[1])
            subPoints.append(self._pointsCube[3])
            subPoints.append(self._pointsCube[2])
        elif numberFace == 2:
            subPoints.append(self._pointsCube[1])
            subPoints.append(self._pointsCube[3])
            subPoints.append(self._pointsCube[7])
            subPoints.append(self._pointsCube[6])
        elif numberFace == 3:
            subPoints.append(self._pointsCube[6])
            subPoints.append(self._pointsCube[7])
            subPoints.append(self._pointsCube[4])
            subPoints.append(self._pointsCube[5])
        elif numberFace == 4:
            subPoints.append(self._pointsCube[4])
            subPoints.append(self._pointsCube[5])
            subPoints.append(self._pointsCube[0])
            subPoints.append(self._pointsCube[2])
        elif numberFace == 5:
            subPoints.append(self._pointsCube[4])
            subPoints.append(self._pointsCube[7])
            subPoints.append(self._pointsCube[3])
            subPoints.append(self._pointsCube[2])
        elif numberFace == 6:
            subPoints.append(self._pointsCube[0])
            subPoints.append(self._pointsCube[1])
            subPoints.append(self._pointsCube[6])
            subPoints.append(self._pointsCube[5])
        return subPoints

class figure:
    _cubes = []
    _typeFigure = []
    def __init__(self, typeFigure, posX, posY, posZ):
        self._cubes.append(cube(posX, posY, posZ))
        self._typeFigure = typeFigure
        if typeFigure == FIG_L:
            self._cubes.append(cube(posX, posY, posZ - 1))
            self._cubes.append(cube(posX, posY, posZ + 1))
            self._cubes.append(cube(posX + 1, posY, posZ + 1))
        elif typeFigure == FIG_LINEAL:
            self._cubes.append(cube(posX, posY, posZ - 1))
            self._cubes.append(cube(posX, posY, posZ + 1))
        elif typeFigure == FIG_S:
            self._cubes.append(cube(posX - 1, posY, posZ))
            self._cubes.append(cube(posX, posY, posZ + 1))
            self._cubes.append(cube(posX + 1, posY, posZ + 1))

    def moveX(self, posX):
        for cube in self._cubes:
            cube.centerX = cube.centerX + posX
            cube.generatePoints()

    def moveY(self, posY):
        for cube in self._cubes:
            cube.centerY = cube.centerY + posY
            cube.generatePoints()

    def moveZ(self, posZ):
        for cube in self._cubes:
            cube.centerZ = cube.centerZ + posZ
            cube.generatePoints()

    @property
    def cubes(self):
        return self._cubes

    @cubes.setter
    def cubes(self, val):
        self._cubes = val

    def isValidateMove(self, posX, posY, posZ):
        # for figure in figures:
        #     for cubes in figure.cubes:
        for myCubes in self.cubes:
            print(myCubes.getPointToArray())
            if (myCubes.centerX + posX) >= 3 or (myCubes.centerX + posX) < 0:
                print('X sobre pasa del terreno')
                return False
            elif (myCubes.centerY + posY) < 0:
                print('Y sobre pasa del terreno ', str(myCubes.centerY))
                return False
            elif (myCubes.centerZ + posZ) >=3 or (myCubes.centerZ + posZ) < 0:
                print('Z sobre pasa del terreno')
                return False
        return True

    def __repr__(self):
        return str(self._typeFigure)
