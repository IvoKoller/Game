#ifndef MENUBUTTON_HPP
#define MENUBUTTON_HPP

#include "../label.hpp"
#include "../sprite.hpp"
#include "../layers/group.hpp"

namespace evo {
namespace graphics {

    class MenuButton : public Group { //does it have to be renderable?
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
        MenuButton(float x, float y, float width, std::string name,
            void (*callbackFunction)(void));
        MenuButton(float x, float y, float width, std::string name,
            void (*toggleCallbackFunction)(bool));
        ~MenuButton();

        void update() override;
    private:
        void setToggleActive() {
            m_ToggleCallbackFunction(true);
            pressed();
            m_ToggleActive = true;
        }
        void normal();
        void hover();
        void pressed();
    };

} }

#endif /* end of include guard: MENUBUTTON_HPP */
