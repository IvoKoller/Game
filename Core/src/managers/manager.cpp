#include "manager.hpp"

namespace evo {

    void Manager::add(Manager* element, std::vector<Manager*>& vector) {
        if(element == nullptr){ //handle nullpointer
            Debug::Log("Nullptr exception, no object passed on to add function!", LogType::Error);
            return;
        }
        //attention, unsigned int is used as "object not found"
        //unsigned int -1 corrisponds to the highest number of unsigned int
        //in order to prevent undefined behaviour, must protect manager from getting to big
        if(vector.size() == (unsigned int) -2){
            Debug::Log("Manager cannot store more objects!", LogType::Error);
            return;
        }

        if(!vector.empty()) { //do I need to check again after size() ?
            if(exists(element->id, vector)){ //check if id already exists
                //Debug::Log("ID [" + std::to_string(element->id) + "] already exists! Object already added!", LogType::Warning);
                return;
            }
            //id is new -> insert() only inserts element *before* iterator, thus last one has to be checked manually
            if(vector.back()->id < element->id) {
                vector.push_back(element);
                return;
            }
            if(vector.size() == 1){ //vector size for insert() has to be bigger than one in order to work
                vector.insert(vector.begin(), element); //special case, new id is smaller than last one
                return;
            }
            //insert element at sorted position
            insert(element, vector, 0, vector.size() -2);
            return;
        }
        vector.push_back(element);
    }

    Manager* Manager::get(const unsigned int& id, std::vector<Manager*>& vector) {
        unsigned int index = search(id, vector, 0, vector.size() - 1);
        if(index != -1) return vector[index];
        Debug::Log("Couldn't get ID [" + std::to_string(id) + "]", LogType::Error);
        return nullptr;
    }

    void Manager::remove(const unsigned int& id, std::vector<Manager*>& vector) {
        unsigned int index = search(id, vector, 0, vector.size() - 1);
        if(index != -1){
            vector.erase(vector.begin() + index);
        }
    }

    void Manager::removeFromStatic(const unsigned int& id, std::vector<Manager*>& vector) {
        unsigned int index = search(id, vector, 0, vector.size() - 1);

        if(index != -1){
            delete vector[index];
            std::cout << 1 << std::endl;
            vector.erase(vector.begin() + index);
        }
    }

    void Manager::clear(std::vector<Manager*>& vector) {
        //printIDs(vector);
        for (int i = 0; i < vector.size(); i++) {
            Manager* m = vector[i];
            //std::cout << m->id << std::endl;
            delete m;
        }
        vector.clear();
        std::cout << vector.size() << std::endl;
    }

    void Manager::printIDs(std::vector<Manager*>& vector) {
        for(Manager* element : vector) std::cout << element->id << std::endl;
    }

    unsigned int Manager::hash(const char *string) {
        unsigned int hash = 0, len = strlen(string);
        for(size_t i = 0; i < len; ++i) hash = 65599 * hash + string[i];
        hash = hash ^ (hash >> 16);
        return hash;
    }

    unsigned int Manager::search(const unsigned int& id, std::vector<Manager*>& vector, unsigned int first, unsigned int last) {
        unsigned int index;
        if(first <= last && last != -1) { // careful with -1 wrap around
            unsigned int mid = (first + last) / 2, midID = vector[mid]->id;
            if(id == midID) index = mid;
            else if(id > midID) index = search(id, vector, mid+1, last);
            else index = search(id, vector, first, mid-1); // if(id < midID)
        }else {
            //Debug::Log("ID not found", LogType::Note);
            index = -1;
        }
        return index;
    }

    bool Manager::exists(const unsigned int& id, std::vector<Manager*>& vector) {
        return search(id, vector, 0, vector.size() - 1) == -1 ? false : true;
    }

    void Manager::insert(Manager* element, std::vector<Manager*>& vector, unsigned int first, unsigned int last) {
        //check for duplicates!
        unsigned int id = element->id, mid = (first + last) / 2, next = mid+1,
            midID = vector[mid]->id, nextID = vector[next]->id;

        if(midID < id && id < nextID) {
            vector.insert(vector.begin() + next, element);
            return;
        }
        else if(id < midID && mid == 0) {
            vector.insert(vector.begin(), element);
            return;
        }else if(midID < id && id > nextID) insert(element, vector, mid+1, last);
        else if(midID > id && id < nextID) insert(element, vector, first, mid-1);
    }

}
