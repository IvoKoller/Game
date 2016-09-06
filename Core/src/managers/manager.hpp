#ifndef MANAGER_H
#define MANAGER_H

//still heavily under development

#include <vector>
#include <string>
#include <iostream>
#include "../utils/debug.hpp"

#include "element.hpp"

namespace evo {
    template<typename T>
    class Manager {
    protected:
        static std::vector<Element*> m_Elements;
    public:
        static void add(T* element);
        static void add(Element* element);

        static void remove(const unsigned int& id);

        static T* get(const unsigned int& id); //get by id should be prefered, faster

        static void clear();

        static void printIDs();
        //void update(); takes function pointer
        static bool exists(const unsigned int& id);
    protected:
        static unsigned int binarySearch(const unsigned int& id, unsigned int first = 0, unsigned int last = m_Elements.size() - 1);
        static void binaryInsert(Element* element, unsigned int first = 0, unsigned int last = m_Elements.size() - 2);
    };

    //static variables
    template<typename T>
    std::vector<Element*> Manager<T>::m_Elements;

    template<typename T>
    void Manager<T>::add(T* element){
        add(static_cast<Element*>(element));
    }

    template<typename T>
    void Manager<T>::add(Element* element) {
        //attention, unsigned int is used as "object not found"
        //unsigned int -1 corrisponds to the highest number of unsigned int
        //in order to prevent undefined behaviour, must protect manager from getting to big
        if(m_Elements.size() == (unsigned int) -2){ //might even be lower (-3)
            std::cerr << "Manager cannot store more objects!" << std::endl;
            return;
        }

        if(element == nullptr){ //handle nullpointer
            //Debug::Log("Nullptr exception, no object passed on to add function!", LogType::Error);
            std::cerr << "Nullptr exception, no object passed on to add function!" << std::endl;
            return;
        }

        if(!m_Elements.empty()){
            if(exists(element->id)){ //check if id already exists
                //Debug::Log("ID already exists! Object already added!", LogType::Warning);
                std::cerr << "ID already exists! Object already added!" << std::endl;
                return;
            }
            //id is new -> insert() only inserts element *before* iterator, thus last one has to be checked manually
            if(m_Elements.back()->id < element->id){
                m_Elements.push_back(element);
                return;
            }
            //insert element at sorted position
            binaryInsert(element);
            return;
        }
        m_Elements.push_back(element);
    }

    template<typename T>
    void Manager<T>::remove(const unsigned int& id){
        unsigned int index = binarySearch(id);
        delete m_Elements[index];
        m_Elements.erase(m_Elements.begin() + index);
    }

    template<typename T>
    T* Manager<T>::get(const unsigned int& id) {
        return static_cast<T*>(m_Elements[binarySearch(id)]);
    }

    template<typename T>
    void Manager<T>::clear() {
        for (unsigned int i = 0; i < m_Elements.size(); i++) delete m_Elements[i];
        m_Elements.clear();
    }

    template<typename T>
    unsigned int Manager<T>::binarySearch(const unsigned int& id, unsigned int first, unsigned int last) {
        std::cout << "passed binary search!" << std::endl;
        std::cout << first << " " << last << std::endl;
        if(first > last || last == -1){ //careful with -1 wrap around
            //Debug::Log("ID not found!", LogType::Error);
            std::cerr << "ID not found! " << (unsigned int)-1 << std::endl;
            return (unsigned int) -1;
        }
        unsigned int mid = (first + last) / 2, midID = m_Elements[mid]->id;
        if(id == midID) return mid;
        else if(id > midID) binarySearch(id, mid+1, last);
        else binarySearch(id, first, mid-1); // if(id < midID)
    }

    template<typename T>
    bool Manager<T>::exists(const unsigned int& id) {
        std::cout << "passed exist binary search!" << std::endl;
        std::cout << binarySearch(id) << " " << (unsigned int)-1 << std::endl;
        return binarySearch(id) != -1 ? false : true; //why the fuck != ?????

    }

    template<typename T>
    void Manager<T>::binaryInsert(Element* element, unsigned int first, unsigned int last) {
        std::cout << "passed binary insert" << std::endl;
        unsigned int id = element->id, mid = (first + last) / 2, next = mid+1,
            midID = m_Elements[mid]->id, nextID = m_Elements[next]->id;

        std::cout << midID << " " << id << " " << nextID << std::endl;
        if(midID < id && id < nextID){
            m_Elements.insert(m_Elements.begin() + next, element);
            return;
        }
        else if(id < midID && mid == 0){ //really neccessary?
            m_Elements.insert(m_Elements.begin(), element);
            return;
        }else if(midID < id && id > nextID) binaryInsert(element, mid+1, last);
        else if(midID > id && id < nextID) binaryInsert(element, first, mid-1);
        else{
            std::cout << "something has gone wrong..." << std::endl;
        }
    }

    template<typename T>
    void Manager<T>::printIDs() {
        for(Element* element : m_Elements){
            std::cout << element->id << std::endl;
        }
    }

}

#endif /* end of include guard: MANAGER_H */
