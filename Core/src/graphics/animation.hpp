#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>

struct Animation {
    std::string name;
    int start;
    int end;
    int current;
    int fallback;

    Animation(std::string name, int start, int end, int fallback)
    : name(name), start(start), end(end), current(start), fallback(fallback) { }

};

#endif /* end of include guard: ANIMATION_H */
