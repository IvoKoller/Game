#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include <ctime>

#include "manager.hpp"
#include "../animation.hpp"
#include "../sprite.hpp"

namespace evo {
namespace graphics {

    class AnimationManager : public Manager<Animation> {
        static std::vector<Sprite*> m_Sprites;
        static unsigned int m_IDCount;
    public:
        AnimationManager();

        static unsigned int createID();
        static void addActive(Sprite& sprite);
        static void removeActive(const unsigned int& ID);
        static void update();
    private:
        static bool checkTime(std::chrono::high_resolution_clock::time_point timePoint);
    };

}}

#endif /* end of include guard: ANIMATION_MANAGER_H */
