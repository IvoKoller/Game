#include "menuButton.hpp"
#include "../window.hpp"

namespace evo {
namespace graphics {

    MenuButton::MenuButton(float x, float y, float width, std::string name,
    void (*callbackFunction)(void))
        : Group(maths::mat4::translate(maths::vec3(x, y, 0.0f))),
        m_Position(maths::vec2(x,y)),
        m_ButtonLeft(-1 ,0, 1, 1,"ButtonLeftNormal"),
        m_ButtonMiddle(0, 0,width, 1,"ButtonMiddleNormal",true),
        m_ButtonRight(width, 0, 1, 1, "ButtonRightNormal"),
        m_Label(name, 0, 0, "Bpdots32", 0xff000000),
        m_CallbackFunction(callbackFunction) {
        add(&m_ButtonLeft);
        add(&m_ButtonMiddle);
        add(&m_ButtonRight);
        add(&m_Label);
        normal();
    }

    MenuButton::MenuButton(float x, float y, float width, std::string name,
    void (*toggleCallbackFunction)(bool))
        : Group(maths::mat4::translate(maths::vec3(x, y, 0.0f))),
        m_Position(maths::vec2(x,y)),
        m_ButtonLeft(-1 ,0, 1, 1,"ButtonLeftNormal"),
        m_ButtonMiddle(0, 0,width, 1,"ButtonMiddleNormal",true),
        m_ButtonRight(width, 0, 1, 1, "ButtonRightNormal"),
        m_Label(name, 0, 0, "Bpdots32", 0xff000000),
        m_Toggle(true),
        m_ToggleCallbackFunction(toggleCallbackFunction) {
        add(&m_ButtonLeft);
        add(&m_ButtonMiddle);
        add(&m_ButtonRight);
        add(&m_Label);
        setToggleActive();
        normal();
    }

    MenuButton::~MenuButton() { }

    void MenuButton::update() {
        if(m_Toggle){
            if(!m_ToggleActive){
                if(m_ButtonMiddle.collider->CollidesWithMouse(m_Position)){
                    if(graphics::Window::isMouseButtonClicked(0)){
                        m_ToggleCallbackFunction(true);
                        pressed();
                        m_ToggleActive = true;
                    } else hover();
                } else normal();
            } else {
                if(m_ButtonMiddle.collider->CollidesWithMouse(m_Position)
                && graphics::Window::isMouseButtonClicked(0)){
                    m_ToggleCallbackFunction(false);
                    normal();
                    m_ToggleActive = false;
                } else pressed();
            }
        }else{
            if(m_ButtonMiddle.collider->CollidesWithMouse(m_Position)){
                if(graphics::Window::isMouseButtonClicked(0)){
                    m_CallbackFunction();
                    pressed();
                }  else hover();
            } else normal();
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
