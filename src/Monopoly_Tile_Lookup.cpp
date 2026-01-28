#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <pybind11/embed.h>
#include <iostream>
#include <vector>
#include <pybind11/stl.h>
#include "../include/Monopoly_Tile_Lookup.h"

Monopoly_Tile_Lookup::Monopoly_Tile_Lookup(){
  pybind11::module_ sys = pybind11::module_::import("sys");
  sys.attr("path").attr("append")("./python/Monopoly_Env/"); 
  pybind11::module_ loader = pybind11::module_::import("Tiles_loader");
  pybind11::object loader_class = loader.attr("Tiles_loader");
  pybind11::object loader_instance = loader_class();
  pybind11::object lodaer_results = loader_instance.attr("load")();
  std::vector<Tile_info> extracted_data = lodaer_results.cast<std::vector<Tile_info>>();
  std::copy(std::begin(extracted_data), std::end(extracted_data), std::begin(tile_lookup));
}

const Tile_info& Monopoly_Tile_Lookup::get_tile(const int position) const{
  bool is_in_range = position >= 0 && position < tile_lookup.size();

  if(is_in_range){
    return tile_lookup[position];
  }
  else{
    throw std::out_of_range("Invalid Tile Position!");
  }
}

const std::array<Tile_info, 40>& Monopoly_Tile_Lookup::get_all_tiles() const{
  return tile_lookup;
}

void Monopoly_Tile_Lookup::update_tile(const int position,
  const Tile_info& new_tile_info){
    bool is_in_range = position >= 0 && position < tile_lookup.size();

  if (is_in_range){
    tile_lookup[position] = new_tile_info;
  }
  else{
    throw std::out_of_range("Invalid Tile Position!");
  }
}

