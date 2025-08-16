 
#include <iostream>
#include <stdint.h>
#include <fstream>
#include <iomanip>
#include <string.h>


//carrega as constantes
uint8_t memoria [4096];
uint8_t V [16];
uint16_t I;
uint16_t PC;
uint16_t stack[16];
uint8_t SP;
uint8_t timerDelay;
uint8_t display [64*32];
bool teclas [16];
std::string caminhoDaROM = "C:/Users/Asus/Desktop/C++/CHIP8/danm8ku.ch8";


//mostra a memoria no terminal com os valores da ROM carregados
void printarMemoria (){
    for (int i=0; i < 4096; i += 16 ){
        std::cout << std::hex << std::setw(4) << std::setfill('0') << i << ": ";

        for (int j = 0; j < 16; j++){
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)memoria[i + j] << ":";
        }
        std::cout << std::endl;
    }
}


//le a ROM contida em caminhoDaROM como um arquivo binario e carrega na memoria
bool carregarROM(const char* caminhoDaROM) {

    int inicioROM = 0x200;
    int index = inicioROM;

    std::ifstream ROM(caminhoDaROM, std::ios::binary);

    if (!ROM.is_open()) {
        std::cout << "deu pau na ROM" << std::endl;
        return false;
    }

    char byte;
    while (ROM.get(byte)) {
        memoria[index++] = static_cast<uint8_t>(byte);
    }

    ROM.close();
    return true;
}


//funcao para pegar os opcodes da ROM na memoria
uint16_t pegarOpcode(){

    uint8_t byteMaior = memoria[PC];
    uint8_t byteMenor = memoria [PC + 1];

    uint16_t opcode = (byteMaior << 8) | byteMenor;
    PC = PC + 2;
    return opcode;
}


//switch com os opcodes
void opcodes (){

uint16_t opcode = pegarOpcode();
    
    switch(opcode){
        //CLS -- limpa o display
        case 0x00E0:

            break;
        case 0x00EE:
            PC = stack[SP];
            SP = SP - 1;
            break;
        case 0x1nnn:
        uint16_t nnn = opcode & 0x0FFF;
            PC = nnn
            break;
        case 0x2nnn:

            break;
    }
}



//main
int main(){
    std::cout << "refogado de macaco-prego amanha no refeitorio" << std::endl;
    carregarROM(caminhoDaROM.c_str());
    printarMemoria();
    return 0;
}
