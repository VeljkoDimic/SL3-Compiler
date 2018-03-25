#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include "Utils.h"
#include "LR1.h"
#include "DFA.h"
#include "Node.h"
#include "LLVMGen.h"
#include "ScanningFailure.h"
#include "ParsingFailure.h"
#include "CodeGenFailure.h"

int main(int argc, char** argv) {
    std::cout << "Lexing..." << std::endl;

    std::vector<Token> tokens;

    // Lexing
    try {
        DFA dfa;
        std::string line;

        while (getline(std::cin, line)) {
            std::vector<Token> scanned_tokens = dfa.scan(line);
            tokens.insert(std::end(tokens),
                    std::begin(scanned_tokens),
                    std::end(scanned_tokens));
        }
    } catch (ScanningFailure &f) {
        std::cerr << f.getMessage() << std::endl;
        return 1;
    }

    //for (int i = 0; i < tokens.size(); ++i) {
        //std::cout << tokens.at(i) << std::endl;
    //}

    // Parsing
    std::cout << "Parsing..." << std::endl;
    Node* root;
    try {
        LR1 lr1("SL3.lr1");
        root = lr1.Parse(tokens);
        std::cout << *root << std::endl;
    } catch (ParsingFailure &f) {
        std::cerr << f.getMessage() << std::endl;
        return 1;
    }

    // Code Generation (LLVM)
    std::cout << "Generating Code..." << std::endl;
    try {
        LLVMGen llvm(root);
        std::cout << llvm.getLlvm() << std::endl;

    } catch (CodeGenFailure &f) {
        std::cerr << f.getMessage() << std::endl;
        return 1;
    }

    return 0;
}
