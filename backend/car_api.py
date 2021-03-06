import requests
import json
from coordinates import Coordinates

BASE = 'http://crawiot.lan'


def post_subtargets(subtargets_list) -> bool:
    data = {'subtargets': subtargets_list}
    resp = requests.post(f'{BASE}/api/subtargets',
                         data=json.dumps(data, default=vars),
                         headers={'Content-Type': 'application/json'}
                         )
    return resp.status_code == 200


def get_traces() -> str:
    trace = requests.get(f'{BASE}/api/traces')
    return trace.text


def get_location() -> Coordinates:
    location = requests.get(f'{BASE}/api/location')
    parsed_string = location.json()
    return Coordinates(parsed_string["X"], parsed_string["Y"])
