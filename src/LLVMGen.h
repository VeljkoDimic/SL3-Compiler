#ifndef LLVMGEN_H
#define LLVMGEN_H

#include <string>
#include <iostream>
#include <sstream>
#include "Node.h"

class LLVMGen {
    private:
        // Contains .ll program
        std::stringstream llvm;

        // Keeps track of current top instruction number
        int instruction;

        // Stores variables in symbol table
        std::map<std::string, int> symbol_table;

        // Return code of node n
        std::string code(Node* n);

        // Return code required to print a number
        std::string printNumCode(int i);

        // Return header code
        std::string header() const;

        // Return footer code
        std::string footer() const;
    public:
        // Constructor, where n is the root of the parsed sl3
        LLVMGen(Node* n);

        // Get code
        std::string getLlvm() const;
};

#endif
