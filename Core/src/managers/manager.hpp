#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include <string>
#include <iostream>

namespace evo {

    template <typename T> //template <class T> is syntacally equal
    class Manager {
    public:
        struct Element {
            const std::string& name;
            T* object;

            Element(const std::string& name, T* object)
            : name(name), object(object) { }
        };
    protected:
        static std::vector<Element> m_Elements;
    public:
        static void add(const std::string& name, T* object);
        static T* get(const std::string& name);
        static void clean();
        //void update(); takes function pointer
    };

    template <typename T>
    std::vector<typename Manager<T>::Element> Manager<T>::m_Elements;

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

}

#endif /* end of include guard: MANAGER_H */
