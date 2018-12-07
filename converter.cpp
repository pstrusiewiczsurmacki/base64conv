//
// Created by patryk on 12/5/18.
//

#include <cstdint>
#include <iostream>
#include "converter.h"

converter::converter(std::string &inFile, std::string &outFile) {
    this->inFileStr = inFile;
    this->outFileStr = outFile;
}

converter::~converter() {

}

void converter::usage() {
    std::cout << std::endl << "base64conv [OPTION] [INPUT FILE] [OUTPUT FILE]" << std::endl << std::endl;
    std::cout << "Options:" << std::endl << std::endl;
    std::cout << "\t-c\tConvert file to base64" << std::endl << std::endl;
    std::cout << "\t-d\tDecode base64 file" << std::endl << std::endl;
}
