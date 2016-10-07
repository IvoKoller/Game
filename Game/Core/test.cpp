#include "src/managers/DynamicManager.hpp"
// #include <vector>
// #include <iostream>
using namespace evo;

class TestType : public StaticManager<TestType> {
public:
    TestType(const char* name) : StaticManager(name) { }
};

class TestType2 : public StaticManager<TestType2> {
public:
    TestType2(const char* name) : StaticManager(name) { }
};

class TestManager : public DynamicManager<TestType> { };
class TestManager2 : public DynamicManager<TestType2> { };

void gen_random(char *s, const int len) {
    for (int i = 0; i < len; ++i) {
        int randomChar = rand()%(26+26+10);
        if (randomChar < 26)
            s[i] = 'a' + randomChar;
        else if (randomChar < 26+26)
            s[i] = 'A' + randomChar - 26;
        else
            s[i] = '0' + randomChar - 26 - 26;
    }
    s[len] = 0;
}

// class Mngr {
// public:
//     static void add(Mngr* element, std::vector<Mngr*>& elements){
//         elements.push_back(element);
//     }
//     static Mngr* get(unsigned int index, std::vector<Mngr*>& elements) {
//         return elements[index];
//     }
// };
//
//
// template <typename T>
// class StaticMngr : public Mngr {
// public:
//     static std::vector<Mngr*> elements;
//     unsigned int id;
//     StaticMngr(unsigned int id) : id(id) { }
//     static void add(Mngr* element){ Mngr::add(element, elements); }
//     static Mngr* get(unsigned int index){ return Mngr::get(index, elements); }
//     static void print(){
//         for(Mngr* ele : elements){
//             StaticMngr* element = static_cast<StaticMngr*>(ele);
//             std::cout << element->id << std::endl;
//         }
//     }
// };
//
// template <typename T>
// std::vector<Mngr*> StaticMngr<T>::elements;
//
// template <typename T>
// class DynMngr : public Mngr {
// public:
//     static std::vector<Mngr*> elements;
//     unsigned int id;
//     DynMngr(unsigned int id) : id(id) { }
//     static void add(unsigned int id){ Mngr::add(StaticMngr<T>::get(id), elements); }
//     static Mngr* get(unsigned int index){ return Mngr::get(index, elements); }
//     static void print(){
//         for(Mngr* ele : elements){
//             DynMngr* element = static_cast<DynMngr*>(ele);
//             std::cout << element->id << std::endl;
//         }
//     }
// };

// template <typename T>
// std::vector<Mngr*> DynMngr<T>::elements;
//
// class Type1 : public StaticMngr<Type1> {
// public:
//     Type1(unsigned int id) : StaticMngr(id) { }
// };
//
// class Type2 : public StaticMngr<Type2> {
// public:
//     Type2(unsigned int id) : StaticMngr(id) { }
// };
//
// class DynMngrType1 : public DynMngr<Type1> { };
//
// class DynMngrType2 : public DynMngr<Type2> { };


int main(){
    // Type1::add(new Type1(5));
    // Type1::add(new Type1(6));
    // Type1::add(new Type1(7));
    // Type2::add(new Type2(7));
    // Type2::add(new Type2(8));
    // Type2::add(new Type2(9));
    //
    // std::cout << "==========type 1===========" << std::endl;
    // Type1::print();
    // DynMngrType1::add(1);
    // std::cout << "==========type 2===========" << std::endl;
    // Type2::print();
    // DynMngrType2::add(1);
    // std::cout << "==========Manager type 1===========" << std::endl;
    // DynMngrType1::print();
    // std::cout << "==========Manager type 2===========" << std::endl;
    // DynMngrType2::print();

    // for(int i = 0; i < 10; i++){
    //     char s[10];
    //     gen_random(s, 6);
    //     TestType::add(new TestType(s));
    // }

    TestType* asdf = new TestType("1");
    TestType::add(new TestType("a"));
    TestType::add(new TestType("as"));
    TestType::add(new TestType("afs"));
    TestType::add(new TestType("agfd"));
    TestType::add(asdf);

    TestType2::add(new TestType2("s")); //first causes problems... sometimes?
    TestType2::add(new TestType2("sfs"));
    TestType2::add(new TestType2("seg"));
    TestType2::add(new TestType2("jkt7s"));
    TestType2::add(new TestType2("kits"));

    TestManager::add("a");
    TestManager::add("agfd");
    //
    TestManager2::add("s");
    TestManager2::add("kits");
    TestManager2::add("00");
    //
     std::cout << "==========TestType==============" << std::endl;
    TestType::printIDs();
    //
    std::cout << "===========TestType2=============" << std::endl;
    TestType2::printIDs();
    //
    std::cout << "==========TestManager==============" << std::endl;
    //
    TestManager::printIDs();
    std::cout << "============TestManager2============" << std::endl;
    TestManager2::printIDs();

    TestManager::clear();
    return 0;
}
