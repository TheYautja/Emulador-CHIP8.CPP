 
#include <iostream>
#include <stdint.h>
#include <fstream>
#include <iomanip>

uint8_t memoria [4096];
uint8_t V [16];
uint16_t I;
uint16_t PC;
uint16_t stack[16];
uint8_t SP;
uint8_t timerDelay;
uint8_t display [64*32];
bool teclas [16];

void printarMemoria (){
    
    for (int i=0; i < 4096; i += 16 ){
        std::cout << std::hex << std::setw(4) << std::setfill('0') << i << ": ";

        for (int j = 0; j < 16; j++){
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)memoria[i + j] << ":";
        }
        std::cout << std::endl;
    }

}




int main(){
    std::cout << "clandg filho da puta" << std::endl;
    printarMemoria();
    return 0;
}
