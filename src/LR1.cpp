#include "LR1.h"
#include <string>
#include <fstream>
#include <iostream>
#include "Node.h"
#include "ParsingFailure.h"

void LR1::ReadLr1(std::string file_name) {
    std::ifstream lr1(file_name);

    if (!lr1) {
        throw ParsingFailure("PARSING ERROR: Unable to find "
                "file " + file_name);
    }

    int num_terminals = Utils::ReadIntLineFromFile(lr1);

    for (int i = 0; i < num_terminals; ++i) {
        std::string line = "";
        try {
            getline(lr1, line);
            terminals.insert(line);
            std::cout << line << std::endl;
        } catch(...) {
            throw ParsingFailure("PARSING ERROR: Unable to "
                    "read terminals");
        }
    }
    for (auto t : terminals) {
        std::cout << t << std::endl;
    }
    //for(std::string line; getline(lr1, line);) {
        //std::cout << line << std::endl;
    //}
}

LR1::LR1() {
    ReadLr1("SL3.lr1");
}

LR1::LR1(std::string file_name) {
    ReadLr1(file_name);
}

Node LR1::Parse(std::vector<Token> tokens) {
    return Node("");
}
