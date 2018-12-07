//
// Created by patryk on 12/5/18.
//

#ifndef BASE64CODER_CONVERTER_H
#define BASE64CODER_CONVERTER_H

#include <string>

class converter {
protected:
    std::string inFileStr;
    std::string outFileStr;
public:
    converter(std::string &inFile, std::string &outFile);
    virtual ~converter();
    virtual void doProcessing() = 0;
    static void usage();
};


#endif //BASE64CODER_CONVERTER_H