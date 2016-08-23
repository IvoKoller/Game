#include "manager.hpp"

namespace evo {
namespace graphics {

    template <typename T>
    std::vector<const typename Manager<T>::Element*> Manager<T>::m_Elements;

    template <typename T>
    void Manager<T>::add(const std::string& name, const T& object){
        Element element(name, object);
        m_Elements.push_back(element);
    }

    template <typename T>
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
