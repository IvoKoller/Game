#ifndef DYNAMICMANAGER_HPP
#define DYNAMICMANAGER_HPP

#include "staticManager.hpp"

namespace evo {

    template <typename T>
    class DynamicManager : public Manager{
        static std::vector<Manager*> m_Vector;
    public:
        static void add(const unsigned int& id) { Manager::add(StaticManager<T>::get(id), m_Vector); }
        static void add(const char* name) { add(Manager::hash(name)); }
        static T* get(const unsigned int& id) { return static_cast<T*>(Manager::get(id, m_Vector)); }
        static void remove(const unsigned int& id) { Manager::remove(id, m_Vector); }
        static void clear() { Manager::clear(m_Vector); }
        static void printIDs() { Manager::printIDs(m_Vector); }
    };

    template <typename T>
    std::vector<Manager*> DynamicManager<T>::m_Vector;
}

#endif /* end of include guard: DYNAMICMANAGER_HPP */
