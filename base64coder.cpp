//
// Created by patryk on 12/5/18.
//

#include "base64coder.h"
#include <fstream>
#include <iostream>
#include <cstring>

#define mask 0x3F
#define shift (6*(3-j))

base64coder::base64coder(std::string &inFile, std::string &outFile):converter(inFile, outFile) {}

void base64coder::doProcessing() {
    std::ifstream input;
    input.open(this->inFileStr,std::ios::in | std::ios::binary);
    std::ofstream output;
    output.open(this->outFileStr,std::ios::out | std::ios::binary);
    if (!input.is_open()){
        std::cerr << "ERROR: Could not open input file." << std::endl;
        exit(101);
    }
    if (!output.is_open()){
        std::cerr << "ERROR: Could not create output file." << std::endl;
        exit(102);
    }

    char buf = 0;
    uint8_t val[3] = "\0";
    size_t i = 0;

    while (input.get(buf)){
        val[i] = buf;
        i++;
        if (i > 2){
            uint8_t* conv = this->codeSlice(val,i);
            for (size_t j = 0; j < i+1; ++j)
                output << this->toBase(conv[j]);
            std::memset(&val,0,3);
            i = 0;
            delete conv;
        }
    }
    if (i != 0) {
        uint8_t* conv = this->codeSlice(val,i);
        for (size_t j = 0; j <= i; ++j)
            output << this->toBase(conv[j]);

        for (int s = 2-i; s >= 0; --s)
            output << "=";
        delete conv;
    }
}

char base64coder::toBase(uint8_t inInt) {
    if (inInt < 26)
        return 'A' + inInt;
    else if (inInt < 52)
        return 'a' + inInt - 26;
    else if (inInt < 62)
        return '0' + inInt - 52;
    else if (inInt == 62)
        return '+';
    else
        return '/';
}

uint8_t *base64coder::codeSlice(uint8_t (&val)[3], size_t &size) {
    uint32_t iVal = 0;
    for (size_t l = 0, k = 2; l < size; ++l, --k){
        iVal += ((uint32_t) val[l]) << (8 * k);
    }
    uint8_t* ans = new uint8_t[4];
    for (size_t j = 0; j < 4; ++j){
        ans[j] = ((iVal & (mask << shift))>>shift);
    }
    return ans;
}