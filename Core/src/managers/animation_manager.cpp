#include "animation_manager.hpp"

namespace evo {
namespace graphics {

    void AnimationManager::update(){
        for(Manager* element : m_Vector){
            Sprite* sprite = static_cast<Sprite*>(element);
            Animation* animation = sprite->m_ActiveAnimation;
            if(checkTime(sprite->m_StartOfAnimation, animation->speed)){
                sprite->setUV(sprite->m_CurrentFrame);
                sprite->resetTimePoint();
                sprite->m_IsPlaying = true;
                if(sprite->m_RepeatType == RepeatType::Pingpong){
                    if (sprite->m_CurrentFrame == animation->endFrame) sprite->m_Ping = false;
                    if (sprite->m_CurrentFrame == animation->startFrame) sprite->m_Ping = true;

                    sprite->m_Ping ? sprite->m_CurrentFrame++ : sprite->m_CurrentFrame--;
                    break;
                }
                if (sprite->m_CurrentFrame < animation->endFrame){
                    sprite->m_CurrentFrame++;
                    break;
                } else if (sprite->m_RepeatType == RepeatType::Loop){
                    sprite->m_CurrentFrame = animation->startFrame;
                    break;
                } else sprite->stop();
            }
            sprite->m_IsPlaying = false;
        }
    }

    bool AnimationManager::checkTime(std::chrono::high_resolution_clock::time_point startOfAnimation, const unsigned int &speed){
        std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
        return (std::chrono::duration_cast<std::chrono::milliseconds>(now - startOfAnimation).count() >= speed) ? true : false;
    }

}}
