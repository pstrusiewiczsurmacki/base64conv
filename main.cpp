#include <iostream>
#include <getopt.h>

#include "base64coder.h"
#include "base64decoder.h"

enum usecase {CODER,DECODER};

int main(int argc,char** argv) {

    if (argc < 4) {
        std::cerr << std::endl << "ERROR: Too few arguments" << std::endl;
        converter::usage();
        exit(99);
    }

    if (argc > 4) {
        std::cerr << std::endl << "ERROR: Too many arguments" << std::endl;
        converter::usage();
        exit(100);
    }

    usecase uc;
    int opt = 0;

    while ((opt = getopt(argc, argv, "cd")) != -1) {
        switch (opt) {
            case 'c':
                uc = CODER;
                break;
            case 'd':
                uc = DECODER;
                break;
            default:
                //std::cerr << "ERROR: Wrong arguments" << std::endl << std::endl;
                converter::usage();
                exit(103);
        }
    }

    std::string inFile = argv[optind];
    std::string outFile = argv[optind + 1];

    converter* c;

    if (uc == CODER)
        c = new base64coder(inFile, outFile);
    else
        c = new base64decoder(inFile, outFile);

    c->doProcessing();
    delete c;
    return 0;

}