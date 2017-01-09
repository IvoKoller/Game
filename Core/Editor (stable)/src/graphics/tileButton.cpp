#include "tileButton.hpp"

namespace evo {
namespace graphics {

    TileButton::TileButton(float x, float y, float width, float height, unsigned int value, Tile* tile,
        void (*callbackFunction)(unsigned int), bool grid)
        : Group(maths::mat4::translate(maths::vec3(x, y, 0.0f))),
        m_Position(maths::vec2(x,y)),
        m_CallbackFunction(callbackFunction),
        m_Value(value),
        m_GridTile(grid),
        m_Button(0,0,width,height,tile,true),
        m_Overlay(0,0,width,height,0x00ffffff) {

        this->Group::add(&m_Button);
        this->Group::add(&m_Overlay);
        TileButton::StaticManager::add(this);
    }

    TileButton::TileButton(float x, float y, float width, float height, unsigned int value, const char* tile,
        void (*callbackFunction)(unsigned int), bool grid)
        : Group(maths::mat4::translate(maths::vec3(x, y, 0.0f))),
        m_Position(maths::vec2(x,y)),
        m_CallbackFunction(callbackFunction),
        m_Value(value),
        m_GridTile(grid),
        m_Button(0,0,width,height,tile,true),
        m_Overlay(0,0,width,height,0x00ffffff) {

        this->Group::add(&m_Button);
        this->Group::add(&m_Overlay);
        TileButton::StaticManager::add(this);
    }

    TileButton::~TileButton() { }

    void TileButton::checkstate(const Window& window) {
        for(int i = 0; i < TileButton::size(); i++){
            TileButton* button = TileButton::getAtIndex(i);
            double mx, my; float fmx, fmy;
            window.getMousePosition(mx, my);
            fmx = -16 + static_cast<float>(mx)/(window.getWidth()/32);
            fmy = 9 - static_cast<float>(my)/(window.getHeight()/18);
            maths::vec2 cursor = maths::vec2(fmx, fmy);
            maths::vec2 relativeMousePosition = cursor - button->m_Position;
            if(button->m_Button.collider->Contains(relativeMousePosition)){
                if(button->m_GridTile) std::cout << button->m_Value << std::endl;

                if(window.isMouseButtonPressed(0)) button->m_CallbackFunction(button->m_Value);
                else if(window.isMouseButtonPressed(1)){
                    if(button->m_GridTile) button->m_SecondCallbackFunction(button->m_Value);
                }
                else if(window.isMouseButtonPressed(0)) button->pressed();
                else button->hover();
            } else button->normal();
        }
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
