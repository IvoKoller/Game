#include <iostream>
#include <vector>


int main() {

    std::vector<int*> v;
    v.push_back(new int(8));
    std::cout << v.size() << std::endl;
    delete v[0];
    if(v[0] == nullptr) std::cout << "hello" << std::endl;
    return 0;
}
