#ifndef TILE_HPP
#define TILE_HPP

#include "../managers/element.hpp"

namespace evo {
namespace graphics {

    struct Tile : public Element {
        int index, height, width;

        Tile(const std::string& name, int index, int height = 1, int width = 1);
    };

}}

#endif /* end of include guard: TILE_HPP */
