#ifndef MONOPOLY_PROJECT_MONOPOLY_TILE_LOOKUP_H
#define MONOPOLY_PROJECT_MONOPOLY_TILE_LOOKUP_H

#include <array>
#include <tuple>
#include <string>

enum Tile_type{
    PROPERTY,
    CORNER,
    TAX,
    CARD
};

struct Tile_info{
    Tile_type type;
    std::string name;
    int owner; // -1 for non property and default state
    int purchase_price; // 10 default
    int base_rent; // 0 for non property
};


class Monopoly_Tile_Lookup{
    private:  
        std::array<Tile_info, 40> tile_lookup;
        
        void set_special_tiles();
    public:
        Monopoly_Tile_Lookup();
        Tile_info get_tile(const int position) const;
        void set_tile_owner(const int position, const int player_number);
};

#endif //MONOPOLY_PROJECT_MONOPOLY_TILE_LOOKUP_H