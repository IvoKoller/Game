#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include <string>
#include "../../utils/debug.hpp"

namespace evo {
namespace graphics {

    template <typename T> //template <class T> is synatacally equal
    class Manager {
        struct Element {
            const std::string& name; //value must exist, thus reference
            const T& object; //value must exist, thus reference
            Element(const std::string& name, const T& object)
                : name(name), object(object) { }
        };

        static std::vector<const Element*> m_Elements;
    public:
        static void add(const std::string& name, const T& object);
        static T* get(const std::string& name);
        static void clean(); //NOTE: Can optionally be called if created on heap
        //void update();
    };

}}

#endif /* end of include guard: MANAGER_H */
