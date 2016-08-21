#include "animation_manager.hpp"

namespace evo {
namespace graphics {

    std::vector<Sprite&> AnimationManager::m_ActiveAnimations;

    void AnimationManager::addSprite(const Sprite& sprite){
        m_ActiveAnimations.push_back(sprite);
    }
}}
