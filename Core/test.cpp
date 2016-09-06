#include "src/managers/manager.hpp"

using namespace evo;

class TestType;

class TestManager : public Manager<TestType> { };

class TestType : public Element {
public:
    TestType(const char* name) : Element(name) { }
};



int main(){

    TestType* sdf = new TestType("7");
    TestType* asdf = new TestType("0");
    TestManager::add(asdf);
    TestManager::add(new TestType("1"));
    TestManager::add(new TestType("2"));
    TestManager::add(new TestType("4"));
    TestManager::add(new TestType("5"));
    TestManager::add(new TestType("6"));
    TestManager::printIDs();
    TestManager::add(sdf);
    TestManager::add(sdf);

    TestManager::printIDs();

    TestManager::clear();

    return 0;
}
