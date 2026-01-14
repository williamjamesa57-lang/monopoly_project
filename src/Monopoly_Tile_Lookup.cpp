#include <algorithm>
#include <iterator>
#include "../include/Monopoly_Tile_Lookup.h"

Tile_info set_tax_tiles(int tax){
    Tile_info to_write{};
    Tile_type taxation_tile = TAX;
    std::array<std::string,2> tax_names{{"Income Tax", "Luxury Tax"}};
    std::array<int,2> rates{{200, 100}};
    to_write.type = taxation_tile;
    to_write.name = tax_names[tax];
    to_write.owner = -1;
    to_write.purchase_price = rates[tax];
    return to_write;
}

Tile_info set_chance_tiles(int type){
    Tile_type chance_tile = CARD;
    Tile_info to_write{};
    std::array<std::string,2> card_name{{"Chance", "Community Chest"}};
    to_write.type = chance_tile;
    to_write.name = card_name[type];
    to_write.owner = -1;
    return to_write;
}

Monopoly_Tile_Lookup::Monopoly_Tile_Lookup(){
    Tile_type default_type = PROPERTY;
    Tile_info default_tile = {default_type, "tile", -1, 10,0};
    std::fill(std::begin(tile_lookup), std::end(tile_lookup), default_tile);
    set_special_tiles();
}

void Monopoly_Tile_Lookup::set_special_tiles(){
    Tile_type corner_type = CORNER;
    std::array<std::string, 4> corner_names{{"GO", "Jail/Visiting", "Free Parking", "Go To Jail"}};

    for(int i = 0; i < 40; i+=10){
        tile_lookup[i].type = corner_type;
        tile_lookup[i].name = corner_names[i/10];
        tile_lookup[i].owner = -1;
    }

    tile_lookup[4] = set_tax_tiles(0);
    tile_lookup[38] = set_tax_tiles(1);

    tile_lookup[2] = set_chance_tiles(1);
    tile_lookup[17] = set_chance_tiles(1);
    tile_lookup[33] = set_chance_tiles(1);

    tile_lookup[7] = set_chance_tiles(0);
    tile_lookup[22] = set_chance_tiles(0);
    tile_lookup[36] = set_chance_tiles(0); 
}

Tile_info Monopoly_Tile_Lookup::get_tile(const int position) const{
    return tile_lookup[position];
}

void Monopoly_Tile_Lookup::set_tile_owner(const int position, const int player_number){
    tile_lookup[position].owner = player_number;
}

