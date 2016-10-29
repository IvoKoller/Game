#include "countButton.hpp"

namespace evo {
namespace graphics {

    CountButton::CountButton(float x, float y,  void (*callbackfunction)(int),
    int countInit, int min, int max)
    : Group(maths::mat4::translate(maths::vec3(x, y, 0.0f))),
    m_Count(countInit),
    m_Min(min),
    m_Max(max),
    m_Position(maths::vec2(x,y)),
    m_Callbackfunction(callbackfunction),
    m_TextfieldLeft(-1,0,1, 1, "TextfieldLeft"),
    m_Textfield(0,0,2, 1, "TextfieldMiddle"),
    m_Button(2,0,1,1, "CountButtonNormal"),
    m_Label(std::to_string(countInit), 0.1f, 0.3f, "Bpdots32", 0xff000000),
    m_ColliderLeft(maths::vec3(x+2,y,0),0.5,1),
    m_ColliderRight(maths::vec3(x+2.5,y,0),0.5,1) {

    Sprite::add(&m_TextfieldLeft);
    Sprite::add(&m_Textfield);
    Sprite::add(&m_Button);
    Label::add(&m_Label);

    this->Group::add(&m_TextfieldLeft);
    this->Group::add(&m_Textfield);
    this->Group::add(&m_Button);
    this->Group::add(&m_Label);

    CountButton::StaticManager::add(this);
    }

    CountButton::~CountButton() {
        //delete pointers
    }

    void CountButton::update(const Window& window) {
        for(int i = 0; i < CountButton::size(); i++){
            CountButton* button = CountButton::getAtIndex(i);
            double mx, my; float fmx, fmy;
            window.getMousePosition(mx, my);
            fmx = -16 + static_cast<float>(mx)/(window.getWidth()/32);
            fmy = 9 - static_cast<float>(my)/(window.getHeight()/18);
            maths::vec2 cursor = maths::vec2(fmx, fmy);
            if(button->m_ColliderLeft.Contains(cursor)){
                if(window.isMouseButtonPressed(0)){
                    button->m_Button.setTile("CountButtonMinusPressed");
                    if(window.isMouseButtonClicked(0) && button->m_Count > button->m_Min){
                        button->m_Count--;
                        button->m_Label.text = std::to_string(button->m_Count);
                        button->m_Callbackfunction(button->m_Count);
                    }
                } else button->m_Button.setTile("CountButtonMinusHover");
            } else if(button->m_ColliderRight.Contains(cursor)){
                if(window.isMouseButtonPressed(0)){
                    button->m_Button.setTile("CountButtonPlusPressed");
                    if(window.isMouseButtonClicked(0) && button->m_Count < button->m_Max){
                        button->m_Label.text = std::to_string(button->m_Count);
                        button->m_Count++;
                        button->m_Callbackfunction(button->m_Count);
                    }
                } else button->m_Button.setTile("CountButtonPlusHover");
            } else button->m_Button.setTile("CountButtonNormal");
        }
    }

} }
