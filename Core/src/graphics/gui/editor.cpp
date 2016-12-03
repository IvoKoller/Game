#include "editor.hpp"

namespace evo {
namespace graphics {

    std::string Editor::m_Filepath;

    int Editor::m_Width;
    int Editor::m_Height;
    int Editor::m_Parafactor;
    int Editor::m_ActiveLayer;
    bool Editor::m_Parallax;
    bool Editor::m_UI;
    bool Editor::m_hasChanged;
    Sprite* Editor::m_Preview;
    std::vector< std::vector< std::vector<unsigned int> > >Editor::m_Tiles;
    std::vector< std::vector<GridButton*> > Editor::m_Buttons;
    unsigned int Editor::m_SelectedID;

    void Editor::build(Layer& layer, int z, int width, int height) {
        //clear all existing gridButton instances via layer
        layer.clear();

        for(int y = 0; y < height; y++){ //rebuild
            for(int x = 0; x < width; x++){
                Tile* tile;
                if(m_Tiles[z][y][x] == 0)
                    tile = Tile::get("Grid");
                else
                    tile = Tile::get(m_Tiles[z][y][x]);
                GridButton* grid = new GridButton(x,y,
                    tile->width, tile->height,
                    y*width+x, tile, Editor::addTile, Editor::removeTile);
                layer.add(*grid);
                m_Buttons[z].push_back(grid);
            }
        }
    }

    void Editor::resize(int width, int height) {
        m_Buttons.clear();
        m_Buttons.resize(5);

        if(m_Tiles.size() == 0){
            m_Tiles.resize(5);
        }

        m_Tiles[0].resize(height);
        m_Tiles[1].resize(height);
        m_Tiles[2].resize(height);
        m_Tiles[3].resize(height);
        m_Tiles[4].resize(height);

        for(int i = 0; i < height; i++){
            m_Tiles[0][i].resize(width-2*m_Parafactor, 0);
            m_Tiles[1][i].resize(width-m_Parafactor, 0);
            m_Tiles[2][i].resize(width, 0);
            m_Tiles[3][i].resize(width+m_Parafactor, 0);
            m_Tiles[4][i].resize(width+2*m_Parafactor, 0);
        }

        std::cout << width << " " << height << std::endl;
        for(int z = 0; z < 5; z++){
            for(int y = 0; y < m_Tiles[z].size(); y++){
                for(int x = 0; x < m_Tiles[z][y].size(); x++){
                    std::cout << m_Tiles[z][y][x];
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }

    void Editor::save() {
    //     std::ofstream file;
    //     file.open(filepath::makeAbsolute("assets/scenes/"+m_Filepath));
    //     if(file.is_open()){
    //         for(int i = 0; i < 16*16; i++) file << m_Tiles[i] << std::endl;
    //         file.close();
    //     } else { std::cout << "file not found!" << std::endl; }
    }

    void Editor::load() {
        // std::ifstream file;
        // file.open(filepath::makeAbsolute("assets/scenes/"+m_Filepath));
        // if(file.is_open()){
        //     for(int i = 0; i < 16*16; i++){
        //         unsigned int n;
        //         file >> n;
        //         m_Tiles[i] = n;
        //     }
        //     file.close();
        // } else { std::cout << "file not found!" << std::endl; }
    }

    void Editor::run() { }

    void Editor::update() {
        for(int z = 0; z < 5; z++){
            for(int x = 0; x < m_Buttons[z].size(); x++){
                int index = m_Buttons[z][x]->getValue();
                int width = m_Tiles[z][0].size();
                int tileIndex = m_Tiles[z][index/width][index%width];
                if(tileIndex == 0){
                    m_Buttons[z][x]->setTile(Tile::get("Grid"));
                    m_Parallax ? m_Buttons[z][x]->hide() : m_Buttons[z][x]->show();

                }else{
                    m_Buttons[z][x]->setTile(Tile::get(tileIndex));
                }
            }
        }
    }

} }
