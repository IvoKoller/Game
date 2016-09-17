#ifndef STATICMANAGER_HPP
#define STATICMANAGER_HPP

#include "manager.hpp"

namespace evo {

    template <typename T>
    class StaticManager : public Manager{
        static unsigned int m_IDCount;
    protected:
        static std::vector<Manager*> m_Vector;
    public:
        StaticManager(const char* name) : Manager(name) { }
        StaticManager() : Manager(m_IDCount) { }
        static void add(Manager* element) { Manager::add(element, m_Vector); }
        static T* getAtIndex(const unsigned int& index) {
            return static_cast<T*>(Manager::getAtIndex(index, m_Vector)); }
        static T* get(const unsigned int& id) { return static_cast<T*>(Manager::get(id, m_Vector)); }
        static T* get(const char* name) { return static_cast<T*>(Manager::get(name, m_Vector)); }
        static void clear() { Manager::clear(m_Vector); }
        static void printIDs() { Manager::printIDs(m_Vector); }
        static bool empty() { return Manager::empty(m_Vector); }
        static unsigned int size() { return Manager::size(m_Vector); }
    };

    template <typename T>
    std::vector<Manager*> StaticManager<T>::m_Vector;

    template <typename T>
    unsigned int StaticManager<T>::m_IDCount = 0;
}

#endif /* end of include guard: STATICMANAGER_HPP */
