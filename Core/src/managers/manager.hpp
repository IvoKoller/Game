#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include <string>
#include <iostream>

#include "../audio/sound.hpp"
#include "../graphics/tile.hpp"
#include "../graphics/texture.hpp"
#include "../graphics/font.hpp"
#include "../graphics/animation.hpp"

namespace evo {

    template <typename T> //template <class T> is syntacally equal
    class Manager {
    protected:
        struct Element {
            const std::string& name;
            T* object;

            Element(const std::string& name, T* object)
            : name(name), object(object) { }
        };

        static std::vector<Element> m_Elements;

    public:
        static void add(const std::string& name, T* object);
        static T* get(const std::string& name);
        static void clean();
        //void update();
    };
}

#endif /* end of include guard: MANAGER_H */
