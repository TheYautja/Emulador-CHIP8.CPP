#include <bitset>
#include <iostream>

class CPU {
    public:
        CPU(){

            std::bitset<4096> memoria;
            std::bitset<16> stack;
            std::bitset<16> registradores;

        }
};

int main(){
    
    CPU();
    std::cout << "teste" << std::endl;

    return 0;
}
