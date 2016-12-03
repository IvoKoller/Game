#include "tileButton.hpp"

namespace evo {
namespace graphics {

    TileButton::TileButton(float x, float y, float width, float height, unsigned int value, Tile* tile,
        void (*callbackFunction)(unsigned int))
        : Group(maths::mat4::translate(maths::vec3(x, y, 0.0f))),
        m_Position(maths::vec2(x,y)),
        m_CallbackFunction(callbackFunction),
        m_Value(value),
        m_Button(0,0,width,height,tile,true),
        m_Overlay(0,0,width,height,0x00ffffff) {
        add(&m_Button);
        add(&m_Overlay);
    }

    TileButton::TileButton(float x, float y, float width, float height, unsigned int value, const char* tile,
        void (*callbackFunction)(unsigned int))
        : Group(maths::mat4::translate(maths::vec3(x, y, 0.0f))),
        m_Position(maths::vec2(x,y)),
        m_CallbackFunction(callbackFunction),
        m_Value(value),
        m_Button(0,0,width,height,tile,true),
        m_Overlay(0,0,width,height,0x00ffffff) {
        add(&m_Button);
        add(&m_Overlay);
    }

    TileButton::~TileButton() { }

    void TileButton::update() {
        if(m_Button.collider->CollidesWithMouse(m_Position)){
            if(Window::isMouseButtonPressed(0)){
                m_CallbackFunction(m_Value);
                pressed();
            } else hover();
        } else normal();
    }

    void TileButton::normal() {
        m_Overlay.setColor(0x00ffffff);
    }

    void TileButton::hover() {
        m_Overlay.setColor(0xffffffff);
        m_Overlay.setTile("Hover");
    }

    void TileButton::pressed() {
        m_Overlay.setColor(0xffffffff);
        m_Overlay.setTile("Selected");
    }

} }
