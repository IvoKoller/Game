#include "animation_manager.hpp"

namespace evo {
namespace graphics {

    std::chrono::high_resolution_clock::time_point ActiveAnimationManager::m_TimePoint;

    void ActiveAnimationManager::update(){
        for(Element* element : m_Elements){
            Sprite* sprite = static_cast<Sprite*>(element);
            Animation* animation = sprite->m_ActiveAnimation;
            if(checkTime(sprite->m_StartOfAnimation, animation->speed)){ //0.091 = 30fps
                sprite->setUV(sprite->m_CurrentFrame);
                sprite->resetTimePoint(); //should happen after uv update
                if(sprite->m_RepeatType == RepeatType::Pingpong){
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
                } else if (sprite->m_RepeatType == RepeatType::Loop){
                    sprite->m_CurrentFrame = animation->start;
                    break;
                } else sprite->stop();
            }
        }
    }

    bool ActiveAnimationManager::checkTime(std::chrono::high_resolution_clock::time_point timePoint, const unsigned int &speed){
        return (std::chrono::duration_cast<std::chrono::milliseconds>(m_TimePoint - timePoint).count() < speed) ? true : false;
    }

}}
