#include "gridButton.hpp"

namespace evo {
namespace graphics {

GridButton::GridButton(float x, float y, float width, float height, unsigned int value, Tile* tile,
        void (*callbackFunction)(unsigned int), void (*secondCallbackFunction)(unsigned int))
        : Group(maths::mat4::translate(maths::vec3(x, y, 0.0f))),
        m_Position(maths::vec2(x,y)),
        m_CallbackFunction(callbackFunction),
        m_SecondCallbackFunction(secondCallbackFunction),
        m_Value(value),
        m_Button(0,0,width,height,tile,true),
        m_Overlay(0,0,width,height,0x00ffffff) {
        add(&m_Button);
        add(&m_Overlay);
    }

    GridButton::GridButton(float x, float y, float width, float height, unsigned int value, const char* tile,
        void (*callbackFunction)(unsigned int), void (*secondCallbackFunction)(unsigned int))
        : Group(maths::mat4::translate(maths::vec3(x, y, 0.0f))),
        m_Position(maths::vec2(x,y)),
        m_CallbackFunction(callbackFunction),
        m_SecondCallbackFunction(secondCallbackFunction),
        m_Value(value),
        m_Button(0,0,width,height,tile,true),
        m_Overlay(0,0,width,height,0x00ffffff) {
        add(&m_Button);
        add(&m_Overlay);
    }

    GridButton::~GridButton() { }

    void GridButton::update() {
        if(m_Button.collider->CollidesWithMouse(m_Position)){
            //std::cout << m_Value << std::endl;
            if(Window::isMouseButtonPressed(0)){
                m_CallbackFunction(m_Value);
                pressed();
            } else if(Window::isMouseButtonPressed(1)) m_SecondCallbackFunction(m_Value);
            else hover();
        } else normal();
    }

    void GridButton::hide() {
        m_Button.setColor(0x00ffffff);
    }

    void GridButton::show() {
        m_Button.setColor(0xffffffff);    
    }

    void GridButton::normal() {
        m_Overlay.setColor(0x00ffffff);
    }

    void GridButton::hover() {
        m_Overlay.setColor(0xffffffff);
        m_Overlay.setTile("Hover");
    }

    void GridButton::pressed() {
        m_Overlay.setColor(0xffffffff);
        m_Overlay.setTile("Selected");
    }

} }
