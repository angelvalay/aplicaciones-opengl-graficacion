import math
import random
import sys
from PIL import Image
import numpy
# NODO
class Node(object):
    def __init__(self, data, prev, next):
        self.data = data
        self.prev = prev
        self.next = next


# LISTA DOBLEMENTE ENLAZADA
class DoubleList(object):
    head = None
    tail = None
    best = None
    explorado = 1

    def append(self, data):
        new_node = Node(data, None, None)
        if self.head is None:
            self.head = self.tail = self.best = new_node
        else:
            new_node.prev = self.best
            new_node.next = None
            self.tail.next = new_node
            self.tail = new_node

    def recover(self):
        current_node = self.best
        while current_node is not None:
            yield current_node.data
            current_node = current_node.prev

    def bestNode(self):
        f = 0
        m = 2000
        h = 0
        nm = m

        i = self.head
        while i is not None:
            f = i.data.h + i.data.g
            if (i.data.explorado == 0 and f < m):
                m = f
            i = i.next

        i = self.head
        while i is not None:
            f = i.data.h + i.data.g
            h = i.data.h
            if (i.data.explorado == 0 and f == m and h < nm):
                self.best = i
                nm = h
            i = i.next

        self.explorado = self.explorado + 1
        self.best.data.explorado = self.explorado


# ESCENARIO DE JUEGO
class Puzzle(object):
    coordenadas_x = [1, 1, 1, 2, 2, 2, 3, 3, 3]
    coordenadas_y = [1, 2, 3, 1, 2, 3, 1, 2, 3]
    elementos = ["1", "2", "3", "4", "5", "6", "7", "8"]
    intercambios = [[1, 3, 9, 9],
                    [0, 2, 4, 9],
                    [1, 5, 9, 9],
                    [0, 4, 6, 9],
                    [1, 3, 5, 7, 9],
                    [2, 4, 8, 9],
                    [3, 7, 9, 9],
                    [4, 6, 8, 9],
                    [5, 7, 9, 9]]

    def __init__(self):
        self.estado = None
        self.h = 0
        self.g = 0
        self.explorado = 0
        self.ascendiente = None

    def posx(self, c):
        return self.coordenadas_x[self.estado.index(c)]

    def posy(self, c):
        return self.coordenadas_y[self.estado.index(c)]

    def distanciaManhatan(self, meta):
        suma = 0
        for j in self.elementos:
            dmx = abs(self.posx(j) - meta.posx(j))
            dmy = abs(self.posy(j) - meta.posy(j))
            suma = suma + dmx + dmy
        return suma

    def descendientes(self):
        b = self.estado.index(" ")
        a = self.ascendiente
        r = list()
        j = 0
        while (self.intercambios[b][j] != 9):
            d = self.estado[:]
            d[b] = self.estado[self.intercambios[b][j]]
            d[self.intercambios[b][j]] = " "
            j = j + 1
            if (d != a):
                r.append(d)
        return r

    def printPuzzle(self):
        print("_____")
        print(' '.join(self.estado[0:3]))
        print(' '.join(self.estado[3:6]))
        print(' '.join(self.estado[6:9]))
        print("_____ h->{}  n->{} f->{} e->{}".format(self.h, self.g, self.h + self.g, self.explorado))
        print('')


# INICIO
if __name__ == "__main__":

    estados = []

    # OBJETOS LISTA, ESTADO INICIAL Y ESTADO META O FINAL
    lista = DoubleList()
    estado_inicial = Puzzle()
    estado_meta = Puzzle()

    # ESTADO META O FINAL
    estado_meta.estado = list("12345678 ")

    # ESTADO INICIAL Y PARAMETROS
    estado_inicial.estado = list("4531 2678")
    estado_inicial.h = estado_inicial.distanciaManhatan(estado_meta)
    estado_inicial.g = 0
    estado_inicial.explorado = 1

    # IMPRIME ENCABEZADOS DEL JUEGO
    print("Rompecabezas de 8 piezas")
    print("")
    print("Estado inicial")
    estado_inicial.printPuzzle()
    print("Estado meta ")
    estado_meta.printPuzzle()

    print("Inicia solucion ")

    # METE A LA LISTA EL NODO INICIAL
    lista.append(estado_inicial)

    # OBTIENE EL MEJOR NODO DE LA LISTA
    lista.bestNode()
    mejorNodo = lista.best.data

    j = 0
    while (j < 2000 and mejorNodo.estado != estado_meta.estado):
        # OBTIENE DESCENDIENTES DEL MEJOR NODO Y LOS AGREGA A LA LISTA
        for hijo in mejorNodo.descendientes():
            elem = Puzzle()
            elem.estado = hijo
            elem.h = elem.distanciaManhatan(estado_meta)
            elem.g = mejorNodo.g + 1
            elem.explorado = 0
            elem.ascendiente = mejorNodo.estado
            lista.append(elem)
        # OBTIENE EL MEJOR NODO DE LA LISTA
        lista.bestNode()
        mejorNodo = lista.best.data
        j = j + 1

    # IMPRIME LISTA COMPLETA CON EL RESULTADO
    for v in lista.recover():
        estados.append(v)

    estados.reverse()

    for e in estados:
        e.printPuzzle()