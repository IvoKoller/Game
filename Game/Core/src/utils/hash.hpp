#ifndef HASH_HPP
#define HASH_HPP

#include <string>
//TODO: exclude possibility of hash collision!
//Custom version of hash function "x65599"
//http://www.popekim.com/2012/01/compile-time-hash-string-generation.html
inline static unsigned int hash(const char *string){
    unsigned int hash = 0, len = strlen(string);
    for(size_t i = 0; i < len; ++i) hash = 65599 * hash + string[i];
    hash = hash ^ (hash >> 16);
    //if(StaticManager::exists(hash)) hash++;
    return hash;
}

#endif /* end of include guard: HASH_HPP */
