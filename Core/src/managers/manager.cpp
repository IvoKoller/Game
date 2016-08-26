#include "manager.hpp"

namespace evo {

    template <typename T>
    void Manager<T>::add(const std::string& name, T* object) {
        //handle nullpointer
        if(object == nullptr) std::cerr << "Nullptr exception, no object passed on to add function!" << std::endl;
        //check for duplicate name
        for (Element element : m_Elements) {
            if (element.name == name)
                std::cerr << "Name already exists! Use other name when adding object" << std::endl;
        }

        m_Elements.push_back(Element(name, object));
    }

    template <typename T>
    T* Manager<T>::get(const std::string& name) {
        int index = 0;
        for (Element element : m_Elements) {
            if (element.name == name)
                return m_Elements[index].object;

            index++;
        }
        std::cerr << "Name not found!" << std::endl;
        return nullptr;
    }

    template <typename T>
    void Manager<T>::clean(){ //NOTE: Can optionally be called if created on heap
        for (int i = 0; i < m_Elements.size(); i++) delete m_Elements[i].object;
    }


    template class Manager<Tile>;
    template class Manager<graphics::Texture>;
    template class Manager<audio::Sound>;
    template class Manager<graphics::Font>;
    template class Manager<graphics::Animation>;
}
