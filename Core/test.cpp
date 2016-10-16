// #include <vector>
#include <iostream>

void func(){ std::cout << "asfd" << std::endl; }

class test {
    void (*functionp)(void);
public:
    test(void (*func)(void)) {
        functionp = func;
        functionp();
    }
};

int main(){
    test asdf(func);
    int a;
    std::cin >> a;
    return 0;
}
