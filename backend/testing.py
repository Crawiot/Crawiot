from coordinates import Coordinates
from find_path import get_path

def testing():
    start_pos = Coordinates(0, 0)
    end_pos = Coordinates(10, 9)
    barriers = [
        (Coordinates(2, 1), Coordinates(4, 3)),
        (Coordinates(1, 6), Coordinates(5, 10)),
        (Coordinates(7, 7), Coordinates(9, 12))
        ]
    borders = (Coordinates(-3, -2), Coordinates(13, 11))
    res = get_path(start_pos, end_pos, barriers, borders)
    print(res)

testing()