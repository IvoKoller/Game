#include "textfield.hpp"

namespace evo {
namespace graphics {

    Textfield::Textfield(float x, float y, float width, int max, bool input)
    : Group(maths::mat4::translate(maths::vec3(x, y, 0.0f))) {
        m_Position = maths::vec2(x,y);
        m_Max = max;
        m_TextfieldLeft = new Sprite(-1.5f,0,1.5f, 1.5f, "TextfieldLeft");
        m_Textfield = new Sprite(0,0,width, 1.5f, "TextfieldMiddle", true);
        m_TextfieldRight = new Sprite(width,0,1.5f, 1.5f, "TextfieldRight");
        m_Cursor = new Sprite(0.1f,0.5f,0.3f,0.6f, 0xffffffff);
        m_Label = new Label("",0.1f,0.6f,"Bpdots20",0xff000000);
        m_Label->setColor(maths::vec4(157,168,201,1));

        Sprite::add(m_TextfieldLeft);
        Sprite::add(m_Textfield);
        Sprite::add(m_TextfieldRight);
        Sprite::add(m_Cursor);
        Label::add(m_Label);

        this->Group::add(m_TextfieldLeft);
        this->Group::add(m_Textfield);
        this->Group::add(m_TextfieldRight);
        this->Group::add(m_Cursor);
        this->Group::add(m_Label);
        m_Timer = new Timer();
    }

    void Textfield::update(const Window& window){
        for(int i = 0; i < Textfield::size(); i++){
            Textfield* tf = Textfield::getAtIndex(i);
            double mx, my; float fmx, fmy;
            window.getMousePosition(mx, my);
            fmx = -16 + static_cast<float>(mx)/(window.getWidth()/32);
            fmy = 9 - static_cast<float>(my)/(window.getHeight()/18);
            maths::vec2 cursor = maths::vec2(fmx, fmy);
            maths::vec2 relativeMousePosition = cursor - tf->m_Position;

            if(!tf->m_Active){
                if(tf->m_Textfield->collider->Contains(relativeMousePosition)){
                    if(window.isMouseButtonClicked(0)){
                        tf->pressed();
                        tf->m_Active = true;
                    } else tf->hover();
                } else tf->normal();
            } else {
                if(!tf->m_Textfield->collider->Contains(relativeMousePosition) &&
                window.isMouseButtonClicked(0)){
                    tf->normal();
                    tf->m_Active = false;
                } else tf->pressed();
            }
            if(tf->m_Active) tf->getInput(window);
            tf->m_Cursor->setPosition(maths::vec3(0.1f + 0.4f * tf->m_String.size(),0.5f,0));
            tf->m_Label->text = tf->m_String;
        }
    }

    void Textfield::normal(){
        m_TextfieldLeft->setTile("TextfieldLeft");
        m_Textfield->setTile("TextfieldMiddle");
        m_TextfieldRight->setTile("TextfieldRight");
        m_Cursor->setColor(0x00000000);
    }

    void Textfield::hover(){
        m_TextfieldLeft->setTile("TextfieldLeft");
        m_Textfield->setTile("TextfieldMiddleHover");
        m_TextfieldRight->setTile("TextfieldRight");
        m_Cursor->setColor(0x00000000);
    }

    void Textfield::pressed(){
        m_TextfieldLeft->setTile("TextfieldLeft");
        m_Textfield->setTile("TextfieldMiddleHover");
        m_TextfieldRight->setTile("TextfieldRight");
        //m_Cursor->setColor(maths::vec4(157,168,201,1));
        if(m_Timer->elapsed() > 0.5f){
            m_CursorHide = !m_CursorHide;
            m_Timer->reset();
        }
        m_CursorHide ? m_Cursor->setColor(0x00000000) : m_Cursor->setColor(maths::vec4(157,168,201,1));
    }

    void Textfield::getInput(const Window& window){
        if(m_String.size() < m_Max) {
            if(window.isKeyTyped(GLFW_KEY_A)) m_String += "a";
            else if(window.isKeyTyped(GLFW_KEY_B)) m_String += "b";
            else if(window.isKeyTyped(GLFW_KEY_C)) m_String += "c";
            else if(window.isKeyTyped(GLFW_KEY_D)) m_String += "d";
            else if(window.isKeyTyped(GLFW_KEY_E)) m_String += "e";
            else if(window.isKeyTyped(GLFW_KEY_F)) m_String += "f";
            else if(window.isKeyTyped(GLFW_KEY_G)) m_String += "g";
            else if(window.isKeyTyped(GLFW_KEY_H)) m_String += "h";
            else if(window.isKeyTyped(GLFW_KEY_I)) m_String += "i";
            else if(window.isKeyTyped(GLFW_KEY_J)) m_String += "j";
            else if(window.isKeyTyped(GLFW_KEY_K)) m_String += "k";
            else if(window.isKeyTyped(GLFW_KEY_L)) m_String += "l";
            else if(window.isKeyTyped(GLFW_KEY_M)) m_String += "m";
            else if(window.isKeyTyped(GLFW_KEY_N)) m_String += "n";
            else if(window.isKeyTyped(GLFW_KEY_O)) m_String += "o";
            else if(window.isKeyTyped(GLFW_KEY_P)) m_String += "p";
            else if(window.isKeyTyped(GLFW_KEY_Q)) m_String += "q";
            else if(window.isKeyTyped(GLFW_KEY_R)) m_String += "r";
            else if(window.isKeyTyped(GLFW_KEY_S)) m_String += "s";
            else if(window.isKeyTyped(GLFW_KEY_T)) m_String += "t";
            else if(window.isKeyTyped(GLFW_KEY_U)) m_String += "u";
            else if(window.isKeyTyped(GLFW_KEY_V)) m_String += "v";
            else if(window.isKeyTyped(GLFW_KEY_W)) m_String += "w";
            else if(window.isKeyTyped(GLFW_KEY_X)) m_String += "x";
            else if(window.isKeyTyped(GLFW_KEY_Y)) m_String += "y";
            else if(window.isKeyTyped(GLFW_KEY_Z)) m_String += "z";
            else if(window.isKeyTyped(GLFW_KEY_1)) m_String += "1";
            else if(window.isKeyTyped(GLFW_KEY_2)) m_String += "2";
            else if(window.isKeyTyped(GLFW_KEY_3)) m_String += "3";
            else if(window.isKeyTyped(GLFW_KEY_4)) m_String += "4";
            else if(window.isKeyTyped(GLFW_KEY_5)) m_String += "5";
            else if(window.isKeyTyped(GLFW_KEY_6)) m_String += "6";
            else if(window.isKeyTyped(GLFW_KEY_7)) m_String += "7";
            else if(window.isKeyTyped(GLFW_KEY_8)) m_String += "8";
            else if(window.isKeyTyped(GLFW_KEY_9)) m_String += "9";
            else if(window.isKeyTyped(GLFW_KEY_0)) m_String += "0";
            else if(window.isKeyTyped(GLFW_KEY_PERIOD)) m_String += ".";
            else if(window.isKeyTyped(GLFW_KEY_MINUS)) m_String += "-";
        }
        if (window.isKeyTyped(GLFW_KEY_BACKSPACE) && m_String.size() > 0) m_String.pop_back();
    }

} }
