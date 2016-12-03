#ifndef TEXTFIELD_HPP
#define TEXTFIELD_HPP

#include "../sprite.hpp"

#include "../label.hpp"
#include "../../utils/timer.hpp"
#include "../layers/group.hpp"
#include "editor.hpp"

namespace evo {
namespace graphics {

    class Textfield : public Group {
        maths::vec2 m_Position;
        Sprite m_TextfieldLeft;
        Sprite m_Textfield;
        Sprite m_TextfieldRight;

        Sprite m_Cursor;
        bool m_CursorHide = false;

        Label m_Label;
        Timer m_Timer;
        std::string m_String;
        int m_Max;
        bool m_Input;
        bool m_Active = false;
    public:
        Textfield(float x, float y, float width, int max, bool input = true);
        void update() override;
        std::string getString() { return m_String; }
        bool isActive() { return m_Active; }
    private:
        void getInput();
        void normal();
        void hover();
        void pressed();
    };

} }

#endif /* end of include guard: TEXTFIELD_HPP */
