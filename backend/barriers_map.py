from typing import List

import json

from coordinates import Coordinates


def get_barriers_map(json_file):
    data = json.load(json_file)
    barriers = list(map(
        lambda barrier: Coordinates(barrier['x'], barrier['y']),
        data['barriers']
    ))
    return BarriersMap(barriers)


class BarriersMap:
    def __init__(self, barriers: List[Coordinates]):
        self.barriers = barriers
