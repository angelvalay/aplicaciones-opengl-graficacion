import numpy as np
class wall:
    width = 1
    height = 1
    axis = 'X'
    start_point = (0,0,0) #center

    def __init__(self, width, height, start_point, axis):
        self.width = width
        self.height = height
        self.start_point = start_point
        self.axis = axis

    def getPoints(self):
        points = []
        for x in range (self.width + 1):
            for y in range (self.height + 1):
                if self.axis == 'X':
                    points.append([0,x,y])
                elif self.axis == 'Y':
                    points.append([x,0,y])
                elif self.axis == 'Z':
                    points.append([x,y,0])
        print(points)
        return points

class background:
    def __init__(self) -> None:
        super().__init__()