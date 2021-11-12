from typing import List, Tuple

from coordinates import Coordinates


def get_path(start_position: Coordinates, end_position: Coordinates, barriers: List[Tuple[Coordinates]]):
    inner_subtargets = list(map(lambda border: Coordinates(border[1].x - 1, border[1].y + 1), barriers))
    return [start_position, *inner_subtargets, end_position]
