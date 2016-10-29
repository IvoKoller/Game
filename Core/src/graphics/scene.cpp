#include "scene.hpp"

namespace evo {
namespace graphics {

    Scene::Scene(const std::string& file) { }
    Scene::~Scene() { }

    void Scene::load(const std::string &filepath){
        std::ifstream file;
        file.open(filepath::makeAbsolute("assets/scenes/"+filepath));
        if(file.is_open()){
            for(int i = 0; i < 16*16; i++){
                unsigned int n;
                file >> n;
                m_Tiles.push_back(n)
            }
            file.close();
        } else { std::cout << "file not found!" << std::endl; }
    }
} }
