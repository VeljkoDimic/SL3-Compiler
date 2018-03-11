#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include "DFA.h"
#include "ScanningFailure.h"

int main(int argc, char** argv) {
    std::cout << "Lexing..." << std::endl;

    DFA::DFA dfa;
    //std::vector<std::vector<Token>> tokenLines;
    std::vector<Token> tokens;
    std::string line;

    //Lexing
    try {
        while (getline(std::cin, line)) {
            //tokenLines.push_back(dfa.scan(line));
            std::vector<Token> scanned_tokens = dfa.scan(line);
            tokens.insert(std::end(tokens),
                    std::begin(scanned_tokens),
                    std::end(scanned_tokens));
        }
    } catch (ScanningFailure &f) {
        std::cerr << f.getMessage() << std::endl;
        return 1;
    }

    for (int i = 0; i < tokens.size(); ++i) {
        std::cout << tokens.at(i) << std::endl;
    }

    return 0;
}
