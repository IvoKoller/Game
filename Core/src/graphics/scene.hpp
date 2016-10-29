#ifndef SCENE_HPP
#define SCENE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "renderable2d.hpp"
#include "../utils/filepath.hpp"

namespace evo {
namespace graphics {

    class Scene {
        //masterColorLevel
        //players start position
        //savetiles
        //music  
        //...

        //world
        std::vector<unsigned int> m_Tiles;

    public:
        Scene(const std::string& file);
        ~Scene(); //delete all objects
        void save();
    private:
        void load(const std::string& file);
    };

} }


#endif /* end of include guard: SCENE_HPP */
