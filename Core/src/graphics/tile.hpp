#ifndef TILE_H
#define TILE_H

namespace evo {
namespace graphics {

    struct Tile {
        int index, height, width;

        Tile(int index, int height = 1, int width = 1)
        : index(index), height(height), width(width) { }
    };
    
}}

#endif /* end of include guard: TILE_H */
