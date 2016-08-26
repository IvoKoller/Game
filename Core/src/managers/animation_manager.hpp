#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include <ctime>

#include "manager.hpp"
#include "../graphics/animation.hpp"
#include "../graphics/sprite.hpp"

namespace evo {
namespace graphics {

    class AnimationManager : public Manager<Animation> {
        static std::vector<Sprite*> m_Sprites;
        static unsigned int m_IDCount;
        static std::chrono::high_resolution_clock::time_point m_TimePoint;
    public:
        AnimationManager();

        static unsigned int createID();
        static void addActive(Sprite& sprite);
        static void removeActive(const unsigned int& ID);
        static void update();
    private:
        static bool checkTime(std::chrono::high_resolution_clock::time_point timePoint, const unsigned int& speed);
    };

}}

#endif /* end of include guard: ANIMATION_MANAGER_H */