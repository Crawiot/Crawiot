from typing import List, Tuple

import json

from coordinates import Coordinates


def get_barriers_map(json_file):
    with open(json_file) as file:
        data = json.load(file)

    def to_barriers_tuples(barrier) -> Tuple:
        result = ()
        for point in barrier:
            result += (Coordinates(point['x'], point['y']),)
        return result

    barriers = list(map(
        to_barriers_tuples,
        data['barriers']
    ))
    return BarriersMap(barriers)


class BarriersMap:
    def __init__(self, barriers: List[Tuple[Coordinates]]):
        self.barriers = barriers
