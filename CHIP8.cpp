 
#include <iostream>
#include <stdint.h>
#include <fstream>
#include <iomanip>
#include <string.h>

uint8_t memoria [4096];
uint8_t V [16];
uint16_t I;
uint16_t PC;
uint16_t stack[16];
uint8_t SP;
uint8_t timerDelay;
uint8_t display [64*32];
bool teclas [16];
std::string caminhoDaROM = "C:/Users/Asus/Desktop/C++/CHIP8/ibm.ch8";



void printarMemoria (){
    for (int i=0; i < 4096; i += 16 ){
        std::cout << std::hex << std::setw(4) << std::setfill('0') << i << ": ";

        for (int j = 0; j < 16; j++){
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)memoria[i + j] << ":";
        }
        std::cout << std::endl;
    }
}



bool carregarROM(const char* caminhoDaROM) {
    int inicioROM = 0x200;
    int index = inicioROM;

    std::ifstream ROM(caminhoDaROM, std::ios::binary);
    if (!ROM.is_open()) {
        std::cout << "Deu pau na ROM" << std::endl;
        return false;
    }

    char byte;
    while (ROM.get(byte)) {
        memoria[index++] = static_cast<uint8_t>(byte);
    }

    ROM.close();
}


int main(){
    std::cout << "Clang do caralho" << std::endl;
    carregarROM(caminhoDaROM.c_str());
    printarMemoria();
    return 0;
}
