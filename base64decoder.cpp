//
// Created by patryk on 12/6/18.
//

#include "base64decoder.h"
#include <fstream>
#include <iostream>
#include <cstring>

base64decoder::base64decoder(std::string &inFile, std::string &outFile):converter(inFile, outFile) {}

void base64decoder::doProcessing() {
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
    uint8_t val[4] = "\0";
    size_t i = 0;

    uint8_t pads = 0;
    int count = 0;
    while (input.get(buf)){

        val[i] = buf;
        i++;
        if (i > 3){
            count++;
            if (count > 202)
                std::cout <<"";
            if (val[i-1] == '='){
                ++pads;
                if (val[i-2] == '=')
                    ++pads;
            }
            for (size_t j = 0; j < i; ++j)
                val[j] = this->toData(val[j]);
            uint8_t* conv = this->decodeSlice(val,i,pads);

            for (size_t j = 0; j < (3 - pads); ++j)
                output << conv[j];

            std::memset(&val,0,4);
            i = 0;
            delete conv;
        }
    }
}

uint8_t *base64decoder::decodeSlice(uint8_t (&val)[4], size_t &size, uint8_t padNum) {
    uint32_t iVal = 0;
    uint8_t* ans = new uint8_t[3-padNum];

    for (size_t l = 0, k = 3; l < size; ++l, --k) {
        iVal += (((uint32_t) val[l]) & 0x3F) << (6 * k);
    }

    for (size_t i = 0; i < 3-padNum; ++i) {
        ans[i] = (iVal >> (8 * (2-i))) & 0xFF;
    }

    return ans;
}

uint8_t base64decoder::toData(uint8_t &inInt) {
    if (inInt == 43)
        return 62;
    else if (inInt == 47)
        return 63;
    else if (inInt == 61)
        return 0;
    else if (inInt < 58)
        return inInt + 4;
    else if (inInt < 91)
        return inInt - 'A';
    else
        return inInt - 71;
}