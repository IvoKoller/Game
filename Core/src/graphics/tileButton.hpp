#ifndef TILEBUTTON_HPP
#define TILEBUTTON_HPP

#include "sprite.hpp"
#include "window.hpp"
#include "layers/group.hpp"

namespace evo {
namespace graphics {

    class TileButton : public Group, public StaticManager<TileButton> {
        maths::vec2 m_Position;
        Sprite* m_Overlay;
        Sprite* m_Button;
        bool m_GridTile;
        unsigned int m_Value;
        void (*m_CallbackFunction)(unsigned int);
        void (*m_SecondCallbackFunction)(unsigned int);
    public:
        TileButton(float x, float y, float width, float height, unsigned int ID,
             const char* tile, void (*callbackFunction)(unsigned int), bool grid = false);

        TileButton(float x, float y, float width, float height, unsigned int ID,
            Tile* tile, void (*callbackFunction)(unsigned int), bool grid = false);

        ~TileButton() { }

        bool isGridTile() { return m_GridTile; }
        unsigned int getValue() { return m_Value; }
        void setTile(Tile* tile){ m_Button->setTile(tile); }
        void setSecondCallback(void (*callbackFunction)(unsigned int)) {
            m_SecondCallbackFunction = callbackFunction;
         }
        static void checkstate(const Window& window); //call update
    protected:
        void normal();
        void hover();
        void pressed();

    };


} }

#endif /* end of include guard: TILEBUTTON_HPP */
