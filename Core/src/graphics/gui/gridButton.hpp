#ifndef GRIDBUTTON_HPP
#define GRIDBUTTON_HPP

#include "../sprite.hpp"
#include "../window.hpp"
#include "../layers/group.hpp"

namespace evo {
namespace graphics {

    class GridButton : public Group {
        maths::vec2 m_Position;
        Sprite m_Overlay;
        Sprite m_Button;
        unsigned int m_Value;
        void (*m_CallbackFunction)(unsigned int);
        void (*m_SecondCallbackFunction)(unsigned int);
    public:
        GridButton(float x, float y, float width, float height, unsigned int ID,
             const char* tile, void (*callbackFunction)(unsigned int),
             void (*secondCallbackFunction)(unsigned int));

        GridButton(float x, float y, float width, float height, unsigned int ID,
            Tile* tile, void (*callbackFunction)(unsigned int),
            void (*secondCallbackFunction)(unsigned int));

        ~GridButton();

        unsigned int getValue() { return m_Value; }
        void setTile(Tile* tile){ m_Button.setTile(tile); }
        void hide();
        void show();
        void update() override;
    protected:
        void normal();
        void hover();
        void pressed();

    };

} }

#endif /* end of include guard: GRIDBUTTON_HPP */
