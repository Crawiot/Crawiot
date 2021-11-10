class Map():
    blocks = []


class Block():
    positionPoints = []  # len(positionPoints)
    # [0] - down left point
    # [1] - down right point
    # [2] - upper right point
    # [3] - upper left point

    def addPoint(self, pointNumber, pointXY):
        self.positionPoints.append(parseToPoint(pointXY))



class Point():
    X = 0
    Y = 0

    def __init__(self, x, y):
        self.X = x
        self.Y = y


def parseToPoint(pointXY):
    for i in range(len(pointXY)):
        if pointXY[i] == ';':
            xLenght = i
            break
    x = int(pointXY[:xLenght])
    y = int(pointXY[xLenght + 1:])
    return Point(x, y)
