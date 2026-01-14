//
// Created by willi on 12/01/2026.
//

#ifndef MONOPOLY_PROJECT_MONOPOLY_CORE_H
#define MONOPOLY_PROJECT_MONOPOLY_CORE_H

#include <vector>
#include <random>
#include <memory>
#include <array>
#include "../include/Monopoly_Tile_Lookup.h"

class Board {
private:
    mutable std::unique_ptr<std::mt19937> rng;
    int cash;
    int current_player_position = 0;
    Monopoly_Tile_Lookup tile_lookup;

public:
    Board();
    Board(const Board& other);
    Board& operator=(const Board& other);

    static constexpr int NUM_SPACES = 40;
    void roll_dice();
    std::vector<int> get_board_state() const;
    int get_current_player_position() const;
    int get_cash() const;
    void update_cash(const int additive);
    Tile_info get_tile_details() const;
    Tile_info purchase_tile();
};

#endif //MONOPOLY_PROJECT_MONOPOLY_CORE_H