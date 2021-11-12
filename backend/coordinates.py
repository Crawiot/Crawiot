import sympy.geometry as geoma


class Coordinates:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def to_point(self):
        return geoma.Point(self.x, self.y)
