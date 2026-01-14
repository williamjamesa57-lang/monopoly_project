pybind11_add_module(monopoly_cpp SHARED
    ../src/Monopoly_Core.cpp
    ../src/Monopoly_Tile_Lookup.cpp
    Monopoly_Bindings.cpp
)

target_include_directories(monopoly_cpp PRIVATE ../include)

set_target_properties(monopoly_cpp PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/python
)