#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <vector>
#include <string>
#include <iostream>
//#include "../utils/debug.hpp"

namespace evo {

    class Manager {
    public:
        Manager(const char* name) : id(hash(name)) { }
    protected:
        static void add(Manager* element, std::vector<Manager*>& vector);
        static Manager* get(const unsigned int& id, std::vector<Manager*>& vector);
        static void remove(const unsigned int& id, std::vector<Manager*>& vector);
        static void clear(std::vector<Manager*>& vector);
        //debug methods
        static void printIDs(std::vector<Manager*>& vector);
        static unsigned int hash(const char *string);
    private:
        unsigned int id; //can be left here since it is non-static
        static unsigned int search(const unsigned int& id, std::vector<Manager*>& vector,
            unsigned int first, unsigned int last); //first = 0, last = size() - 1
        static bool exists(const unsigned int& id, std::vector<Manager*>& vector);
        static void insert(Manager* element, std::vector<Manager*>& elements,
            unsigned int first, unsigned int last); //first = 0, last = size() - 2 because of insert
    };

}

#endif /* end of include guard: MANAGER_HPP */
