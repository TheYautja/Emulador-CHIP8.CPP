// C:\msys64\ucrt64\bin\g++.exe -fdiagnostics-color=always -g "C:\Users\Asus\Desktop\C++\CHIP8\CHIP8.cpp" -o "C:\Users\Asus\Desktop\C++\CHIP8\CHIP8.exe"
 
// "C:\Users\Asus\Desktop\C++\CHIP8\CHIP8.exe"
 
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
