#ifndef ANIMATION_H
#define ANIMATION_H

#include "../managers/element.hpp"

namespace evo{
namespace graphics{

    struct Animation : public Element {
        int start;
        int end;
        int speed; //NOTE: in fps or in ms?
        int fallback;

        Animation(const std::string& name, int start, int end, int fallback = -1, int speed = 15);

    };
}}

#endif /* end of include guard: ANIMATION_H */
