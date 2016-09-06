#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

namespace evo {
    class Element{
        //Hash function "x65599"
        //http://www.popekim.com/2012/01/compile-time-hash-string-generation.html
        unsigned int generateHash(const char *string){
            unsigned int hash = 0, len = strlen(string);
            for(size_t i = 0; i < len; ++i) hash = 65599 * hash + string[i];
            return hash ^ (hash >> 16);
        }
    public:
        const unsigned int id;
        Element(const char *name) : id(generateHash(name)) { }
    };
}

#endif /* end of include guard: ELEMENT_H */
