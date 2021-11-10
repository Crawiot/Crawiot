import Object
import json

def parseMapToObject(filePath):
    with open(filePath) as json_file:
        map = Object.Map()
        data = json.load(json_file)
        for p in data['blocks']:
            block = Object.Block()
            for i in range(4):
                pointXY = p['Position'][i]
                block.addPoint(i,pointXY)
            map.blocks.append(block)
