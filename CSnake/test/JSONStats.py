import json


def json_stats(json_str):
    json_dict = json.loads(json_str)
    return len(json_dict)
