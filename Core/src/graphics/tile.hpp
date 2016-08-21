#ifndef TILE_H
#define TILE_H

struct Tile {
    int index, height, width;
    bool repeat;

    Tile(int index, int height = 1, int width = 1, bool repeat = false)
        : index(index), height(height), width(width), repeat(repeat) { }
};

#endif /* end of include guard: TILE_H */
