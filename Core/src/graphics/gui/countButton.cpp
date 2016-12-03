#include "countButton.hpp"

namespace evo {
namespace graphics {

    CountButton::CountButton(float posX, float posY,  void (*callbackfunction)(int),
    int countInit, int min, int max)
    : Group(maths::mat4::translate(maths::vec3(posX, posY, 0.0f))),
    m_Count(countInit),
    m_Min(min),
    m_Max(max),
    m_Position(maths::vec2(posX,posY)),
    m_ColliderLeftPos(maths::vec3(posX+2,posY,0)),
    m_ColliderRightPos(maths::vec3(posX+2.5,posY,0)),
    m_Callbackfunction(callbackfunction),
    m_TextfieldLeft(-1,0,1, 1, "TextfieldLeft"),
    m_Textfield(0,0,2, 1, "TextfieldMiddle"),
    m_Button(2,0,1,1, "CountButtonNormal"),
    m_Label(std::to_string(countInit), 0.1f, 0.3f, "Bpdots32", 0xff000000),
    m_ColliderLeft(m_ColliderLeftPos,0.5,1),
    m_ColliderRight(m_ColliderRightPos,0.5,1) {

    add(&m_TextfieldLeft);
    add(&m_Textfield);
    add(&m_Button);
    add(&m_Label);

    }

    CountButton::~CountButton() {
        //remove components from manager
    }

    void CountButton::update() {
        if(m_ColliderLeft.CollidesWithMouse()){
            if(Window::isMouseButtonClicked(0)){
                m_Button.setTile("CountButtonMinusPressed");
                if(Window::isMouseButtonClicked(0) && m_Count > m_Min){
                    m_Count--;
                    m_Label.text = std::to_string(m_Count);
                    m_Callbackfunction(m_Count);
                }
            } else m_Button.setTile("CountButtonMinusHover");
        } else if(m_ColliderRight.CollidesWithMouse()){
            if(Window::isMouseButtonClicked(0)){
                m_Button.setTile("CountButtonPlusPressed");
                if(Window::isMouseButtonClicked(0) && m_Count < m_Max){
                    m_Count++;
                    m_Label.text = std::to_string(m_Count);
                    m_Callbackfunction(m_Count);
                }
            } else m_Button.setTile("CountButtonPlusHover");
        } else m_Button.setTile("CountButtonNormal");
    }

} }
