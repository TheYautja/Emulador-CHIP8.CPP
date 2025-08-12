 
#include <iostream>
#include <stdint.h>
#include <fstream>

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
    
    for (int i=0; i < 4096; i++ ){
        std::cout << std::hex << (int)memoria[i] << std::endl;
    }
}




int main(){
    std::cout << "clandg filho da puta" << std::endl;
    printarMemoria();
    return 0;
}
