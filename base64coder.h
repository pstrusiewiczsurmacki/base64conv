//
// Created by patryk on 12/5/18.
//

#ifndef BASE64CODER_BASE64CODER_H
#define BASE64CODER_BASE64CODER_H


#include "converter.h"

class base64coder : public converter {
private:
    char toBase(uint8_t inInt);
    uint8_t* codeSlice(uint8_t (&val)[3],size_t &size);
public:
    base64coder(std::string &inFile, std::string &outFile);
    void doProcessing();
};


#endif //BASE64CODER_BASE64CODER_H