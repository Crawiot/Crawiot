from typing import List
import requests
import json

def post_target(list) -> bool:

    data = {'subtargets': list}
    headers = {'Content-type': 'application/json'}
    r = requests.post("http://crawiot.lan/api/subtargets", data=json.dumps(data), headers=headers)
    return True

def get_traces() -> str:
    trace = requests.get("http://crawiot.lan/api/traces")
    return trace.text()

def get_location() -> tuple:
    location = requests.get("http://crawiot.lan/api/location")
    location.json()
    parsed_string = json.loads(location.json())
    coordinates = (parsed_string["x"], parsed_string["y"])
    return coordinates