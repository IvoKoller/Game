#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "../managers/staticManager.hpp"
#include "texture.hpp"

namespace evo{
namespace graphics{

    struct Animation : public StaticManager<Animation> {
        Texture* texture; //has to be non const
        const int speed; //in ms
        const int startFrame;
        const int endFrame;
        const int fallbackFrame;

        Animation(const char* name, int start, int end, int fallback = -1, int speed = 90, Texture* tex = Texture::getAtIndex(0))
            : StaticManager(name), startFrame(start), endFrame(end), fallbackFrame(fallback), speed(speed), texture(tex) { }
    };
}}

#endif /* end of include guard: ANIMATION_HPP */
