 
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
std::string caminhoDaROM = "C:/Users/Asus/Desktop/C++/CHIP8/danm8ku.ch8";


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



uint16_t pegarOpcode(){

    uint8_t byteMaior = memoria[PC];
    uint8_t byteMenor = memoria [PC + 1];

    uint16_t opcode = (byteMaior << 8) | byteMenor;
    PC = PC + 2;
    return opcode;
}



void executarOpcode() {

    uint16_t opcode = pegarOpcode();

    switch (opcode & 0xF000) {

        case 0x0000:
            switch (opcode & 0x00FF) {
                case 0x00E0:
                    memset(display, 0, sizeof(display));
                    break;

                case 0x00EE:
                    PC = stack[SP--];
                    break;

                default:
                    break;
            }
            break;

        case 0x1000: {
            uint16_t addr = opcode & 0x0FFF;
            PC = addr;
            break;
        }

        case 0x2000: {
            uint16_t addr = opcode & 0x0FFF;
            stack[++SP] = PC;
            PC = addr;
            break;
        }

        case 0x3000: {
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t kk = opcode & 0x00FF;
            if (V[x] == kk) PC += 2;
            break;
        }

        case 0x4000: {
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t kk = opcode & 0x00FF;
            if (V[x] != kk) PC += 2;
            break;
        }

        case 0x5000: {
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t y = (opcode & 0x00F0) >> 4;
            if (V[x] == V[y]) PC += 2;
            break;
        }

        case 0x6000: {
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t kk = opcode & 0x00FF;
            V[x] = kk;
            break;
        }

        case 0x7000: {
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t kk = opcode & 0x00FF;
            V[x] += kk;
            break;
        }

        case 0x8000:
            switch (opcode & 0x000F) {
                case 0x0: {
                    uint8_t x = (opcode & 0x0F00) >> 8;
                    uint8_t y = (opcode & 0x00F0) >> 4;
                    V[x] = V[y];
                    break;
                }
                case 0x1: {
                    uint8_t x = (opcode & 0x0F00) >> 8;
                    uint8_t y = (opcode & 0x00F0) >> 4;
                    V[x] |= V[y];
                    break;
                }
                case 0x2: {
                    uint8_t x = (opcode & 0x0F00) >> 8;
                    uint8_t y = (opcode & 0x00F0) >> 4;
                    V[x] &= V[y];
                    break;
                }
                case 0x3: {
                    uint8_t x = (opcode & 0x0F00) >> 8;
                    uint8_t y = (opcode & 0x00F0) >> 4;
                    V[x] ^= V[y];
                    break;
                }
                case 0x4: {
                    uint8_t x = (opcode & 0x0F00) >> 8;
                    uint8_t y = (opcode & 0x00F0) >> 4;
                    uint16_t sum = V[x] + V[y];
                    V[0xF] = (sum > 255);
                    V[x] = sum & 0xFF;
                    break;
                }
                case 0x5: {
                    uint8_t x = (opcode & 0x0F00) >> 8;
                    uint8_t y = (opcode & 0x00F0) >> 4;
                    V[0xF] = (V[x] > V[y]);
                    V[x] -= V[y];
                    break;
                }
                case 0x6: {
                    uint8_t x = (opcode & 0x0F00) >> 8;
                    V[0xF] = V[x] & 0x1;
                    V[x] >>= 1;
                    break;
                }
                case 0x7: {
                    uint8_t x = (opcode & 0x0F00) >> 8;
                    uint8_t y = (opcode & 0x00F0) >> 4;
                    V[0xF] = (V[y] > V[x]);
                    V[x] = V[y] - V[x];
                    break;
                }
                case 0xE: {
                    uint8_t x = (opcode & 0x0F00) >> 8;
                    V[0xF] = (V[x] & 0x80) >> 7;
                    V[x] <<= 1;
                    break;
                }
            }
            break;

        case 0x9000: {
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t y = (opcode & 0x00F0) >> 4;
            if (V[x] != V[y]) PC += 2;
            break;
        }

        case 0xA000: {
            uint16_t addr = opcode & 0x0FFF;
            I = addr;
            break;
        }

        case 0xB000: {
            uint16_t addr = opcode & 0x0FFF;
            PC = V[0] + addr;
            break;
        }

        case 0xC000: { 
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t kk = opcode & 0x00FF;
            V[x] = (rand() % 256) & kk;
            break;
        }

        case 0xD000: {
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t y = (opcode & 0x00F0) >> 4;
            uint8_t n = opcode & 0x000F;

            V[0xF] = 0;
            for (int row = 0; row < n; row++) {
                uint8_t sprite = memoria[I + row];
                for (int col = 0; col < 8; col++) {
                    if (sprite & (0x80 >> col)) {
                        int px = (V[x] + col) % 64;
                        int py = (V[y] + row) % 32;
                        int idx = py * 64 + px;

                        if (display[idx] == 1) V[0xF] = 1;
                        display[idx] ^= 1;
                    }
                }
            }
            break;
        }

        case 0xE000: {
            uint8_t x = (opcode & 0x0F00) >> 8;
            switch (opcode & 0x00FF) {
                case 0x9E:
                    if (teclas[V[x]]) PC += 2;
                    break;
                case 0xA1: 
                    if (!teclas[V[x]]) PC += 2;
                    break;
            }
            break;
        }

        case 0xF000: {
            uint8_t x = (opcode & 0x0F00) >> 8;
            switch (opcode & 0x00FF) {
                case 0x07:
                    V[x] = timerDelay;
                    break;
                case 0x0A: {
                    bool tecla = false;
                    for (int i = 0; i < 16; i++) {
                        if (teclas[i]) {
                            V[x] = i;
                            tecla = true;
                            break;
                        }
                    }
                    if (!tecla) PC -= 2;
                    break;
                }
                case 0x15:
                    timerDelay = V[x];
                    break;
                case 0x18:
                    break;
                case 0x1E:
                    I += V[x];
                    break;
                case 0x29:
                    I = V[x] * 5;
                    break;
                case 0x33: {
                    uint8_t value = V[x];
                    memoria[I]     = value / 100;
                    memoria[I + 1] = (value / 10) % 10;
                    memoria[I + 2] = value % 10;
                    break;
                }
                case 0x55:
                    for (int i = 0; i <= x; i++) memoria[I + i] = V[i];
                    break;
                case 0x65:
                    for (int i = 0; i <= x; i++) V[i] = memoria[I + i];
                    break;
            }
            break;
        }

        default:
            std::cout << "grande graxa " 
                      << std::hex << opcode << std::endl;
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
