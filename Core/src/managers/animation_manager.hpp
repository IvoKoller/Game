#ifndef ANIMATION_MANAGER_HPP
#define ANIMATION_MANAGER_HPP

#include <ctime>

#include "../graphics/animation.hpp"
#include "../graphics/sprite.hpp"
#include "dynamicManager.hpp"

namespace evo {
namespace graphics {

    class AnimationManager : public DynamicManager<Sprite> {
    public:
        static void update();
        static bool checkTime(std::chrono::high_resolution_clock::time_point startOfAnimation, const unsigned int& speed);
    };
}}

#endif /* end of include guard: ANIMATION_MANAGER_HPP */
