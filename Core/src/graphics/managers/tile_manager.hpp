#ifndef TILE_MANAGER_H
#define TILE_MANAGER_H

#include "manager.hpp"
#include "../tile.hpp"

namespace evo {
namespace graphics {

    class TileManager : public Manager<Tile> {

    public:
        TileManager();

    };

}}

#endif /* end of include guard: TILE_MANAGER_H */
