#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include "manager.hpp"
#include "../animation.hpp"
#include "../sprite.hpp"

namespace evo {
namespace graphics {

    class AnimationManager : public Manager<Animation> {

        /*
        m_Sprites is as big as the total amount of all sprites.
        When a sprite is created, an ID is assigned (the next free index in the vector)
        If a sprite has not any active animations, the value at that it's ID/index
        must be nullptr. Otherwise, the sprite has to submit a pointer to itself at
        its ID/index
        */

        static std::vector<Sprite*> m_Sprites; //if sprite has active animation -> object : else -> nullptr
        static int m_IDCount;
    public:
        AnimationManager();
        static void update();

        static const unsigned int getID(){ return m_IDCount++; }
        static void addActive(const Sprite& sprite);
        static void removeActive();
    };

}}

#endif /* end of include guard: ANIMATION_MANAGER_H */
