#ifndef DYNAMICMANAGER_HPP
#define DYNAMICMANAGER_HPP

#include "staticManager.hpp"

namespace evo {

    template <typename T>
    class DynamicManager : public Manager{
    public:
        static std::vector<Manager*> m_Vector;
        static void add(const unsigned int& id) { Manager::add(StaticManager<T>::get(id), m_Vector); }
        static void add(const char* name) { Manager::add(StaticManager<T>::get(name), m_Vector); }
        static T* getAtIndex(const unsigned int& index) {
            return static_cast<T*>(Manager::getAtIndex(index, m_Vector)); }
        static T* get(const unsigned int& id) { return static_cast<T*>(Manager::get(id, m_Vector)); }
        static T* get(const char* name) { return static_cast<T*>(Manager::get(name, m_Vector)); }
        static void remove(const unsigned int& id) { Manager::remove(id, m_Vector); }
        static void remove(const char* name) { Manager::remove(name, m_Vector); }
        static void clear() { Manager::clear(m_Vector); }
        static void printIDs() { Manager::printIDs(m_Vector); }

        static bool empty() { return Manager::empty(m_Vector); }
        static unsigned int size() { return Manager::size(m_Vector); }
    };

    template <typename T>
    std::vector<Manager*> DynamicManager<T>::m_Vector;
}

#endif /* end of include guard: DYNAMICMANAGER_HPP */
