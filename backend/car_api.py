import requests
import json


def post_target(subtargets_list) -> bool:
    data = {'subtargets': subtargets_list}
    headers = {'Content-Type': 'application/json'}
    r = requests.post("http://crawiot.lan/api/subtargets", data=json.dumps(data), headers=headers)
    return r.status_code == 200


def get_traces() -> str:
    trace = requests.get("http://crawiot.lan/api/traces")
    return trace.text


def get_location() -> tuple:
    location = requests.get("http://crawiot.lan/api/location")
    location.json()
    parsed_string = json.loads(location.json())
    coordinates = (parsed_string["x"], parsed_string["y"])
    return coordinates
