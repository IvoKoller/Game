#include "textfield.hpp"
#include "../window.hpp"

namespace evo {
namespace graphics {

    Textfield::Textfield(float x, float y, float width, int max, bool input)
    : Group(maths::mat4::translate(maths::vec3(x, y, 0.0f))),
        m_Position(maths::vec2(x,y)),
        m_Max(max),
        m_TextfieldLeft(-1,0,1, 1, "TextfieldLeft"),
        m_Textfield(0,0,width, 1, "TextfieldMiddle", true),
        m_TextfieldRight(width,0,1, 1, "TextfieldRight"),
        m_Cursor(0.1f,0.5f,0.3f,0.6f, 0xffffffff),
        m_Label("",0.1f,0.6f,"Bpdots32",0xff000000),
        m_Timer() {

        m_Label.setColor(maths::vec4(157,168,201,255));
        add(&m_TextfieldLeft);
        add(&m_Textfield);
        add(&m_TextfieldRight);
        add(&m_Cursor);
        add(&m_Label);
        normal();
    }

    void Textfield::update(){
        if(!m_Active){
            if(m_Textfield.collider->CollidesWithMouse(m_Position)){
                if(Window::isMouseButtonClicked(0)){
                    pressed();
                    m_Active = true;
                } else hover();
            } else normal();
        } else {
            if(!m_Textfield.collider->CollidesWithMouse(m_Position) &&
            Window::isMouseButtonClicked(0)){
                normal();
                m_Active = false;
            } else pressed();
        }
        if(m_Active) getInput();
        m_Cursor.setPosition(maths::vec3(0.1f + 0.4f * m_String.size(),0.5f,0));
        m_Label.text = m_String;

        //Editor::setFile(m_String); //reeeally bad, just for the sake of getting things done
    }

    void Textfield::normal(){
        m_TextfieldLeft.setTile("TextfieldLeft");
        m_Textfield.setTile("TextfieldMiddle");
        m_TextfieldRight.setTile("TextfieldRight");
        m_Cursor.setColor(0x00000000);
    }

    void Textfield::hover(){
        m_TextfieldLeft.setTile("TextfieldLeft");
        m_Textfield.setTile("TextfieldMiddleHover");
        m_TextfieldRight.setTile("TextfieldRight");
        m_Cursor.setColor(0x00000000);
    }

    void Textfield::pressed(){
        m_TextfieldLeft.setTile("TextfieldLeft");
        m_Textfield.setTile("TextfieldMiddleHover");
        m_TextfieldRight.setTile("TextfieldRight");
        //m_Cursor.setColor(maths::vec4(157,168,201,1));
        if(m_Timer.elapsed() > 0.5f){
            m_CursorHide = !m_CursorHide;
            m_Timer.reset();
        }
        m_CursorHide ? m_Cursor.setColor(0x00000000) : m_Cursor.setColor(maths::vec4(157,168,201,1));
    }

    void Textfield::getInput(){
        //TODO: do dynamically with char value
        if(m_String.size() < m_Max) {
            if(Window::isKeyTyped(GLFW_KEY_A)) m_String += "a";
            else if(Window::isKeyTyped(GLFW_KEY_B)) m_String += "b";
            else if(Window::isKeyTyped(GLFW_KEY_C)) m_String += "c";
            else if(Window::isKeyTyped(GLFW_KEY_D)) m_String += "d";
            else if(Window::isKeyTyped(GLFW_KEY_E)) m_String += "e";
            else if(Window::isKeyTyped(GLFW_KEY_F)) m_String += "f";
            else if(Window::isKeyTyped(GLFW_KEY_G)) m_String += "g";
            else if(Window::isKeyTyped(GLFW_KEY_H)) m_String += "h";
            else if(Window::isKeyTyped(GLFW_KEY_J)) m_String += "j";
            else if(Window::isKeyTyped(GLFW_KEY_I)) m_String += "i";
            else if(Window::isKeyTyped(GLFW_KEY_K)) m_String += "k";
            else if(Window::isKeyTyped(GLFW_KEY_L)) m_String += "l";
            else if(Window::isKeyTyped(GLFW_KEY_M)) m_String += "m";
            else if(Window::isKeyTyped(GLFW_KEY_N)) m_String += "n";
            else if(Window::isKeyTyped(GLFW_KEY_O)) m_String += "o";
            else if(Window::isKeyTyped(GLFW_KEY_P)) m_String += "p";
            else if(Window::isKeyTyped(GLFW_KEY_Q)) m_String += "q";
            else if(Window::isKeyTyped(GLFW_KEY_R)) m_String += "r";
            else if(Window::isKeyTyped(GLFW_KEY_S)) m_String += "s";
            else if(Window::isKeyTyped(GLFW_KEY_T)) m_String += "t";
            else if(Window::isKeyTyped(GLFW_KEY_U)) m_String += "u";
            else if(Window::isKeyTyped(GLFW_KEY_V)) m_String += "v";
            else if(Window::isKeyTyped(GLFW_KEY_W)) m_String += "w";
            else if(Window::isKeyTyped(GLFW_KEY_X)) m_String += "x";
            else if(Window::isKeyTyped(GLFW_KEY_Y)) m_String += "y";
            else if(Window::isKeyTyped(GLFW_KEY_Z)) m_String += "z";
            else if(Window::isKeyTyped(GLFW_KEY_1)) m_String += "1";
            else if(Window::isKeyTyped(GLFW_KEY_2)) m_String += "2";
            else if(Window::isKeyTyped(GLFW_KEY_3)) m_String += "3";
            else if(Window::isKeyTyped(GLFW_KEY_4)) m_String += "4";
            else if(Window::isKeyTyped(GLFW_KEY_5)) m_String += "5";
            else if(Window::isKeyTyped(GLFW_KEY_6)) m_String += "6";
            else if(Window::isKeyTyped(GLFW_KEY_7)) m_String += "7";
            else if(Window::isKeyTyped(GLFW_KEY_8)) m_String += "8";
            else if(Window::isKeyTyped(GLFW_KEY_9)) m_String += "9";
            else if(Window::isKeyTyped(GLFW_KEY_0)) m_String += "0";
            else if(Window::isKeyTyped(GLFW_KEY_PERIOD)) m_String += ".";
            else if(Window::isKeyTyped(GLFW_KEY_MINUS)) m_String += "-";
        }
        if (Window::isKeyTyped(GLFW_KEY_BACKSPACE) && m_String.size() > 0) m_String.pop_back();
    }

} }
