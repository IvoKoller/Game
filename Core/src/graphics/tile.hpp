#ifndef TILE_HPP
#define TILE_HPP

#include "../managers/staticManager.hpp"
#include "texture.hpp"

namespace evo {
namespace graphics {

    struct Tile : public StaticManager<Tile> {
        Texture* texture; //has to be non-const
        const int index;
        const int height;
        const int width;
        Tile(const char* name, int index, int height = 1, int width = 1, Texture* tex = Texture::getAtIndex(0))
            : StaticManager(name), index(index), height(height), width(width), texture(tex) { }
    };

}}

#endif /* end of include guard: TILE_HPP */
