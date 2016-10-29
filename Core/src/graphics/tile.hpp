#ifndef TILE_HPP
#define TILE_HPP

#include "../managers/staticManager.hpp"
#include "texture.hpp"
#include "../maths/maths.hpp"

namespace evo {
namespace graphics {

    struct Tile : public StaticManager<Tile> {
        Texture* texture; //has to be non-const
        const int index;
        const int height;
        const int width;
        const maths::vec3 ColorLevel;
        Tile(const char* name, int index, int height = 1, int width = 1,
            Texture* tex = Texture::getAtIndex(0), maths::vec3 clrlvl = maths::vec3(1,1,1))
            : StaticManager(name), ColorLevel(clrlvl), index(index), height(height), width(width), texture(tex) { }
    };

}}

#endif /* end of include guard: TILE_HPP */
