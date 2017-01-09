#include "menuButton.hpp"

namespace evo {
namespace graphics {

    MenuButton::MenuButton(float x, float y, float width, std::string name)
        : Group(maths::mat4::translate(maths::vec3(x, y, 0.0f))),
        m_Position(maths::vec2(x,y)),
        m_ButtonLeft(-1 ,0, 1, 1,"ButtonLeftNormal"),
        m_ButtonMiddle(0, 0,width, 1,"ButtonMiddleNormal",true),
        m_ButtonRight(width, 0, 1, 1, "ButtonRightNormal"),
        m_Label(name, 0, 0, "Bpdots32", 0xff000000) {
        this->Group::add(&m_ButtonLeft);
        this->Group::add(&m_ButtonMiddle);
        this->Group::add(&m_ButtonRight);
        this->Group::add(&m_Label);

        MenuButton::StaticManager::add(this);
    }

    MenuButton::~MenuButton() { }

    void MenuButton::checkstate(const Window& window) {
        for(int i = 0; i < MenuButton::size(); i++){
            MenuButton* button = MenuButton::getAtIndex(i);
            double mx, my; float fmx, fmy;
            window.getMousePosition(mx, my);
            fmx = -16 + static_cast<float>(mx)/(window.getWidth()/32);
            fmy = 9 - static_cast<float>(my)/(window.getHeight()/18);
            maths::vec2 cursor = maths::vec2(fmx, fmy);
            maths::vec2 relativeMousePosition = cursor - button->m_Position;
            if(button->m_Toggle){
                if(!button->m_ToggleActive){
                    if(button->m_ButtonMiddle.collider->Contains(relativeMousePosition)){
                        if(window.isMouseButtonClicked(0)){
                            button->m_ToggleCallbackFunction(true);
                            button->pressed();
                            button->m_ToggleActive = true;
                        } else button->hover();
                    } else button->normal();
                } else {
                    if(button->m_ButtonMiddle.collider->Contains(relativeMousePosition)
                    && window.isMouseButtonClicked(0)){
                        button->m_ToggleCallbackFunction(false);
                        button->normal();
                        button->m_ToggleActive = false;
                    }
                }
            }else{
                if(button->m_ButtonMiddle.collider->Contains(relativeMousePosition)){
                    if(window.isMouseButtonClicked(0)) button->m_CallbackFunction();
                    else if(window.isMouseButtonPressed(0)) button->pressed();
                    else button->hover();
                } else button->normal();
            }
        }
    }

    void MenuButton::normal() {
        m_ButtonLeft.setTile("ButtonLeftNormal");
        m_ButtonMiddle.setTile("ButtonMiddleNormal");
        m_ButtonRight.setTile("ButtonRightNormal");
        m_Label.setColor(maths::vec4(0,0,0,255));
        m_Label.setPosition(maths::vec3(0.15f,0.4f,0));
    }

    void MenuButton::hover() {
        m_ButtonLeft.setTile("ButtonLeftHover");
        m_ButtonMiddle.setTile("ButtonMiddleHover");
        m_ButtonRight.setTile("ButtonRightHover");
        m_Label.setColor(0xff000000);
        m_Label.setPosition(maths::vec3(0.15f,0.4f,0));
    }

    void MenuButton::pressed() {
        m_ButtonLeft.setTile("ButtonLeftPressed");
        m_ButtonMiddle.setTile("ButtonMiddlePressed");
        m_ButtonRight.setTile("ButtonRightPressed");
        m_Label.setColor(0xff000000);
        m_Label.setPosition(maths::vec3(0.15f,0.3f,0));
    }

} }
