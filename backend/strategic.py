import car_api


def handle_post_target(x: int, y: int) -> bool:
    return car_api.post_target(x, y)
