from coordinates import Coordinates
from grid import get_path, chain


def testing():
    start_pos = Coordinates(0, 0)
    end_pos = Coordinates(10, 9)
    barriers = [
        (Coordinates(4, 2), Coordinates(4, 10)),
    ]
    borders = (Coordinates(-3, -2), Coordinates(13, 11))
    res = get_path(start_pos, end_pos, barriers, borders)
    print(list(map(lambda x: x.__str__(), res)))


testing()
