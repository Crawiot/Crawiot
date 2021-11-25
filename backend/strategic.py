import car_api
from coordinates import Coordinates
from trivial_path import get_path
import barriers_map


def handle_post_target(x: int, y: int) -> bool:
    barriers = barriers_map.get_barriers_map('./map.json')
    current_location = car_api.get_location()
    target = Coordinates(x, y)
    path = get_path(current_location, target, barriers.barriers)
    path = [
        Coordinates(6, 0),
        Coordinates(6, 15),
        Coordinates(0, 15),
        Coordinates(6, 15),
        Coordinates(6, 0),
        Coordinates(0, 0),
    ]
    return car_api.post_subtargets(path)
