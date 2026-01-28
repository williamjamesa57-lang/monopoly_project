import json
import os
from monopoly_cpp import Tile_info
from monopoly_cpp import Tile_type


class Tiles_loader:
    
    def __init__(self):
        self.__input_file = os.path.join(os.path.dirname(__file__),
                                         "Tiles_defaults.json")

    def load(self):
        tiles_list = []
        with open(self.__input_file, "r") as f:
            data = json.load(f)
            for item in range(len(data)):
                specimen = Tile_info()
                #specimen.type = 
                self.__tile_type_classifier(data[item]["type"])
                specimen.name = data[item]["name"]
                specimen.owner = data[item]["owner"]
                specimen.purchase_price = data[item]["purchase_price"]
                specimen.house_price = data[item]["house_price"]
                specimen.base_rent = data[item]["base_rent"]
                specimen.house_count = data[item]["house_count"]
                specimen.is_mortgaged = data[item]["is_mortgaged"]
                specimen.has_monopoly = data[item]["has_monopoly"]
                specimen.color = data[item]["color"]
                tiles_list.append(specimen)

        return tiles_list

    def __tile_type_classifier(self, data):
        my_tile_type = Tile_type
        if data == "PROPERTY":
            my_tile_type = Tile_type.PROPERTY
        elif data == "CORNER":
            my_tile_type = Tile_type.CORNER
        elif data == "TAX":
            my_tile_type = Tile_type.TAX
        elif data == "CARD":
            my_tile_type = Tile_type.CARD
        return my_tile_type
