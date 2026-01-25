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
  int house_count; // 0 default
  bool is_mortgaged; // false default
  bool has_monopoly; // false defalt
};


class Monopoly_Tile_Lookup{
    private:  
        std::array<Tile_info, 40> tile_lookup;       
        void set_special_tiles();
    public:
        Monopoly_Tile_Lookup();
  const Tile_info& get_tile(const int position) const;
  const std::array<Tile_info, 40>& get_all_tiles() const;
  void update_tile(const int position, const Tile_info& new_tile_info);
};

#endif //MONOPOLY_PROJECT_TILE_LOOKUP_H
