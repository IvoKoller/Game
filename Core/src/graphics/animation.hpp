#ifndef ANIMATION_H
#define ANIMATION_H

namespace evo{
namespace graphics{

    struct Animation {
        int start;
        int end;
        int speed; //NOTE: in fps or in ms?
        int fallback;

        Animation(int start, int end, int fallback = -1, int speed = 15)
        : start(start), end(end), speed(speed), fallback(fallback) { }

    };
}}

#endif /* end of include guard: ANIMATION_H */
