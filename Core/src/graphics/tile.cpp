#include "tile.hpp"
#include "../managers/tile_manager.hpp"

namespace evo {
namespace graphics {

    Tile::Tile(const std::string& name, int index, int height, int width)
    : Element(name, TileManager::getID()), index(index), height(height), width(width) { }

}}
