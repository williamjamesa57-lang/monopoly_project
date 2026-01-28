#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../include/Monopoly_Core.h"

PYBIND11_MODULE(monopoly_cpp,m) {
  pybind11::class_<Board>(m, "Board")
    .def(pybind11::init<>())
    .def("roll_dice", &Board::roll_dice)
    .def("get_state", &Board::get_board_state)
    .def("get_current_player_position", &Board::get_current_player_position)
    .def("get_cash", &Board::get_cash)
    .def("update_cash", &Board::update_cash)
    .def("get_tile_details", &Board::get_tile_details)
    .def("modify_tile_info", &Board::modify_tile_info);

  pybind11::enum_<Tile_type>(m, "Tile_type")
    .value("PROPERTY", Tile_type::PROPERTY)
    .value("CORNER", Tile_type::CORNER)
    .value("TAX", Tile_type::TAX)
    .value("CARD", Tile_type::CARD)
    .export_values();

  pybind11::class_<Tile_info>(m, "Tile_info")
    .def(pybind11::init<>())
    .def_readwrite("type", &Tile_info::type)
    .def_readwrite("name", &Tile_info::name)
    .def_readwrite("owner", &Tile_info::owner)
    .def_readwrite("purchase_price", &Tile_info::purchase_price)
    .def_readwrite("house_price", &Tile_info::house_price)
    .def_readwrite("base_rent", &Tile_info::base_rent)
    .def_readwrite("house_count", &Tile_info::house_count)
    .def_readwrite("is_mortgaged", &Tile_info::is_mortgaged)
    .def_readwrite("has_monopoly", &Tile_info::has_monopoly)
    .def_readwrite("color", &Tile_info::color);

  m.def("create_game",[]() {return Board();});
}
