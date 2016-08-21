#include "manager.hpp"

namespace evo {
namespace graphics {

    template <class T>
    std::vector<(Manager<T>::Element)&> Manager<T>::m_Elements;

    template <class T>
    Manager<T>::Manager(){

    }

    template <class T>
    void Manager<T>::add(const std::string& name, const T& object){
        Element element(name, object);
        m_Elements.push_back(element); //NOTE: gets destroyed after it leaves scope?
    }

    template <class T>
    T* Manager<T>::get(const std::string& name){
        int index = 0;
        for (Element& element : m_Elements) {
            if (element.name == name){
                return m_Elements[m_Elements.begin() + index].object;
            }
            index++;
        }
        Debug::Log("Name not found!", LogType::Error);
        return nullptr;
    }

}}
