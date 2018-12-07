//
// Created by patryk on 12/6/18.
//

#ifndef BASE64DECODER_BASE64DECODER_H
#define BASE64DECODER_BASE64DECODER_H

#include "converter.h"

class base64decoder : public converter {
private:
    uint8_t* decodeSlice(uint8_t (&val)[4],size_t &size, uint8_t padNum);
    uint8_t toData(uint8_t &val);
public:
    base64decoder(std::string &inFile, std::string &outFile);
    void doProcessing();
};


#endif //BASE64DECODER_BASE64DECODER_H