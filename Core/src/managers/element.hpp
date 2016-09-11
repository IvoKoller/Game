#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <string>
#include "staticManager.hpp"

namespace evo {
    //Even though it looks very strange,
    //every Element is StaticManager as every type deriving from Element
    //(for instance "Font") should have a list/vector of all the elements
    //of the same type. Since the StaticManager only has static methods and variables
    //this shouldn't affect memory consumption.
    //This is useful because:
    //-multiple DynamicManagers handling different aspects of a certain type is possible
    //-clear function can be called
    //-makes redundant classes like AnimationManager or TextureManager obsolete

    class Element : public StaticManager {
        unsigned int hash(const char *string){
            unsigned int hash = 0, len = strlen(string);
            for(size_t i = 0; i < len; ++i) hash = 65599 * hash + string[i];
            hash = hash ^ (hash >> 16);
            //if(StaticManager::exists(hash)) hash++;
            return hash;
        }

    public:
        const unsigned int id;
        Element(const char* str) : id(hash(str)) { }
    };
}

#endif /* end of include guard: ELEMENT_HPP */
