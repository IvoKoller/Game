#ifndef STATICMANAGER_HPP
#define STATICMANAGER_HPP

#include "manager.hpp"

namespace evo {

    template <typename T>
    class StaticManager : public Manager{
        static std::vector<Manager*> m_Vector;
    public:
        StaticManager(const char* name) : Manager(name) { }
        static void add(Manager* element) { Manager::add(element, m_Vector); }
        static T* get(const unsigned int& id) { return static_cast<T*>(Manager::get(id, m_Vector)); }
        static void clear() { Manager::clear(m_Vector); }
        static void printIDs() { Manager::printIDs(m_Vector); }
    };

    template <typename T>
    std::vector<Manager*> StaticManager<T>::m_Vector;
}

#endif /* end of include guard: STATICMANAGER_HPP */
