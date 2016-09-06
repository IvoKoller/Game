#include "animation.hpp"
#include "../managers/animation_manager.hpp"

namespace evo{
namespace graphics{

    Animation::Animation(const std::string& name, int start, int end, int fallback, int speed)
    : Element(name, AnimationManager::getID()), start(start), end(end), speed(speed), fallback(fallback) { }

}}
