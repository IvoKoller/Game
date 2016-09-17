#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <vector>
#include <string>
#include <iostream>
#include "../utils/debug.hpp"

namespace evo {

    class Manager {
    public:
        Manager(const char* name) : id(hash(name)) {
            std::cout << name << " has id: " << id << std::endl;
        }
        Manager(unsigned int& IDCount) : id(IDCount++) { }
    protected:
        const unsigned int id; //can be left here since it is non-static
        static void add(Manager* element, std::vector<Manager*>& vector);
        static bool exists(const unsigned int& id, std::vector<Manager*>& vector);
        static bool exists(const char* name, std::vector<Manager*>& vector){
            return exists(hash(name), vector);
        }
        static Manager* getAtIndex(const unsigned int& index, std::vector<Manager*>& vector){
            return vector[index];
        }
        static Manager* get(const unsigned int& id, std::vector<Manager*>& vector);
        static Manager* get(const char* name, std::vector<Manager*>& vector){
            return get(hash(name), vector);
        }
        static void remove(const unsigned int& id, std::vector<Manager*>& vector);
        static void remove(const char* name, std::vector<Manager*>& vector){
            Manager::remove(hash(name), vector); } //remove already exists
        static void clear(std::vector<Manager*>& vector);

        static bool empty(std::vector<Manager*>& vector){ return vector.empty(); }
        static unsigned int size(std::vector<Manager*>& vector){ return vector.size(); }
        //debug methods
        static void printIDs(std::vector<Manager*>& vector);
        static unsigned int hash(const char *string);
    private: //add reference to vector?
        static unsigned int search(const unsigned int& id, std::vector<Manager*>& vector,
            unsigned int first, unsigned int last); //first = 0, last = size() - 1
        static void insert(Manager* element, std::vector<Manager*>& elements,
            unsigned int first, unsigned int last); //first = 0, last = size() - 2 because of insert
    };

}

#endif /* end of include guard: MANAGER_HPP */
