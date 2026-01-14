//
// Created by willi on 12/01/2026.
//
#include <sstream>
#include "../include/Monopoly_Core.h"

Board::Board() :
    rng(std::make_unique<std::mt19937>(std::random_device{}())),
    cash(100),
    tile_lookup(Monopoly_Tile_Lookup()){
}

Board::Board(const Board& other)
    : current_player_position(other.current_player_position){
    if(other.rng){
        std::stringstream oss;
        oss << *other.rng;
        auto copied_rng = std::make_unique<std::mt19937>();
        oss >> *copied_rng;
        rng = std::move(copied_rng);
        cash = other.cash;
    }
}

Board& Board::operator=(const Board& other){
    if(this != &other){
        current_player_position = other.current_player_position;
        if(other.rng){
            std::stringstream oss;
            oss << *other.rng;
            auto copied_rng = std::make_unique<std::mt19937>();
            oss >> *copied_rng;
            rng = std::move(copied_rng);
            cash = other.cash;
        }else{
            rng = nullptr;
            cash = -1;
        }
    }

    return *this;
}

void Board::roll_dice() {
    std::uniform_int_distribution<> die1(1,6);
    int roll = die1(*rng) + die1(*rng);
    current_player_position = (current_player_position + roll) % NUM_SPACES;
}

std::vector<int> Board::get_board_state() const {
    std::vector<int> state(NUM_SPACES,0);
    state[current_player_position] = 1;
    return state;
}

int Board::get_current_player_position() const{
    return current_player_position;
}

int Board::get_cash() const{
    return cash;
}

void Board::update_cash(const int additive){
    cash += additive;
}

Tile_info Board::get_tile_details() const{
    return tile_lookup.get_tile(current_player_position);
}

Tile_info Board::purchase_tile(){
    tile_lookup.set_tile_owner(current_player_position, 0);
    return tile_lookup.get_tile(current_player_position);

}