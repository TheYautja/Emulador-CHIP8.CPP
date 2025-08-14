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
        if (index >= 4096) {
            std::cout << "ROM muito grande para caber na memoria" << std::endl;
            return false;
        }
        memoria[index++] = static_cast<uint8_t>(byte);
    }

    ROM.close();

    std::cout << "ROM carregada com sucesso (" << (index - inicioROM) << " bytes)" << std::endl;
    return true;
}

int main() {
    std::cout << "Iniciando CHIP-8" << std::endl;

    if (carregarROM(caminhoDaROM.c_str())) {
        printarMemoria();
    }

    return 0;
}
