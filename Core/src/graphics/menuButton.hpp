#ifndef MENUBUTTON_HPP
#define MENUBUTTON_HPP

#include "label.hpp"
#include "sprite.hpp"
#include "layers/group.hpp"
#include "window.hpp"

namespace evo {
namespace graphics {

    class MenuButton : public Group, public StaticManager<MenuButton> {
        maths::vec2 m_Position;
        Sprite m_ButtonLeft;
        Sprite m_ButtonMiddle;
        Sprite m_ButtonRight;
        Label m_Label;
        void (*m_CallbackFunction)(void);
        void (*m_ToggleCallbackFunction)(bool);
        bool m_Toggle = false;
        bool m_ToggleActive = false;
    public:
        MenuButton(float x, float y, float width, std::string name);

        ~MenuButton();
        void setFunction(void (*callbackFunction)(void)){
            m_CallbackFunction = callbackFunction;
        }
        void setToggleFunction(void (*toggleCallbackFunction)(bool)){
            m_Toggle = true;
            m_ToggleCallbackFunction = toggleCallbackFunction;
        }
        void setToggleActive() {
            m_ToggleCallbackFunction(true);
            pressed();
            m_ToggleActive = true;
        }
        static void checkstate(const Window& window);
    private:
        void normal();
        void hover();
        void pressed();
    };

} }

#endif /* end of include guard: MENUBUTTON_HPP */
