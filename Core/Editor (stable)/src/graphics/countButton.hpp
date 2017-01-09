#ifndef COUNTBUTTON_HPP
#define COUNTBUTTON_HPP

#include "label.hpp"
#include "sprite.hpp"
#include "layers/group.hpp"
#include "window.hpp"
namespace evo {
namespace graphics {

    class CountButton : public Group, public StaticManager<CountButton> {
        maths::vec2 m_Position;
        Sprite m_Textfield;
        Sprite m_TextfieldLeft;
        Sprite m_Button;
        Label m_Label;
        physics::Collider m_ColliderLeft, m_ColliderRight;
        int m_Count, m_Min, m_Max;
        void (*m_Callbackfunction)(int);
    public:
        //also need step variable (normally 1)
        CountButton(float x, float y, void (*callbackfunction)(int), int countInit = 0,
        int min = 0, int max = 100);
        ~CountButton();
        int getCount() { return m_Count; }
        static void update(const Window& window);
    };

} }

#endif /* end of include guard: COUNTBUTTON_HPP */
