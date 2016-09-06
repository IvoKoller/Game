#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include <ctime>

#include "manager.hpp"
#include "../graphics/animation.hpp"
#include "../graphics/sprite.hpp"

namespace evo {
namespace graphics {

    //AnimationManager is responsible for holding all the different animations available
    class AnimationManager : public Manager<Animation> { };

    //ActiveAnimationManager is responsible for managing and updating active animations
    //it is of type sprite, as each sprite holds additional information
    //about the animation it is currently playing
    class ActiveAnimationManager : public Manager<Sprite> {
        static std::chrono::high_resolution_clock::time_point m_TimePoint;
    public:
        static void update();
        static bool checkTime(std::chrono::high_resolution_clock::time_point timePoint, const unsigned int& speed);
    };
}}

#endif /* end of include guard: ANIMATION_MANAGER_H */
