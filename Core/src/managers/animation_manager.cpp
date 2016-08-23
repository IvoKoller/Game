#include "animation_manager.hpp"

namespace evo {
namespace graphics {

    std::vector<Sprite*> AnimationManager::m_Sprites;
    unsigned int AnimationManager::m_IDCount;

    AnimationManager::AnimationManager(){
        m_IDCount = 0;
    }

    unsigned int AnimationManager::createID(){
        return m_IDCount++;
    }

    void AnimationManager::addActive(Sprite& sprite){
        m_Sprites.push_back(&sprite);
    }

    void AnimationManager::removeActive(const unsigned int& ID){
        unsigned int index = 0;
        for (Sprite* sprite : m_Sprites) {
            if (sprite->m_ID == ID){
                m_Sprites.erase(m_Sprites.begin() + index);
                return;
            }
            index++;
        }
    }

    void AnimationManager::update(){
        for(Sprite* sprite : m_Sprites){
            Animation* animation = sprite->m_ActiveAnimation;
            if(checkTime(sprite->m_StartOfAnimation)){ //0.091 = 30fps
                sprite->setUV(sprite->m_CurrentFrame);
                sprite->resetTimePoint(); //should happen after uv update
                if(sprite->m_RepeatType == RepeatType::pingpong){
                    if (sprite->m_CurrentFrame == animation->end)
                    sprite->m_Ping = false;

                    if (sprite->m_CurrentFrame == animation->start)
                    sprite->m_Ping = true;

                    sprite->m_Ping ? sprite->m_CurrentFrame++ : sprite->m_CurrentFrame--;
                    break;
                }
                if (sprite->m_CurrentFrame < animation->end){
                    sprite->m_CurrentFrame++;
                    break;
                } else if (sprite->m_RepeatType == RepeatType::loop){
                    sprite->m_CurrentFrame = animation->start;
                    break;
                } else sprite->stop();
            }

        }

    }
}}
