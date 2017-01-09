#include "editor.hpp"

namespace evo {
namespace graphics {

    std::string Editor::m_Filepath;
    Shader* Editor::m_Shader;
    Window* Editor::m_Window;
    Layer* Editor::m_UILayer;

    unsigned int Editor::m_Tiles[16*16];
    bool Editor::m_ActiveColors[3];
    unsigned int Editor::m_SelectedID;
    unsigned int Editor::m_PlayerPosition; //index of playertile

    void Editor::save() {
        std::ofstream file;
        file.open(filepath::makeAbsolute("assets/scenes/"+m_Filepath));
        if(file.is_open()){
            for(int i = 0; i < 16*16; i++) file << m_Tiles[i] << std::endl;
            file.close();
        } else { std::cout << "file not found!" << std::endl; }
    }

    void Editor::load() {
        std::ifstream file;
        file.open(filepath::makeAbsolute("assets/scenes/"+m_Filepath));
        if(file.is_open()){
            for(int i = 0; i < 16*16; i++){
                unsigned int n;
                file >> n;
                m_Tiles[i] = n;
            }
            file.close();
        } else { std::cout << "file not found!" << std::endl; }
    }

    void Editor::run() { }
    void Editor::setColliderDefault() { }

    void Editor::updateWorldMap(int tilecount){

    }

    void Editor::update() {
        MenuButton::checkstate(*m_Window);
        TileButton::checkstate(*m_Window);
        Textfield::update(*m_Window);
        CountButton::update(*m_Window);
        m_Shader->setUniform4f("filter",
        maths::vec4(m_ActiveColors[0],m_ActiveColors[1],m_ActiveColors[2],1));

        for(int i = 0; i < TileButton::size(); i++){
            TileButton* button = TileButton::getAtIndex(i);
            if(button->isGridTile()){
                if(m_Tiles[button->getValue()] == 0) button->setTile(Tile::get("Grid"));
                else button->setTile(Tile::get(m_Tiles[button->getValue()]));
            }
        }

    }

} }
