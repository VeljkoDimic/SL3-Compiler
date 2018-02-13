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
    std::vector<std::vector<Token>> tokenLines;
    std::string line;

    try {
        while (getline(std::cin, line)) {
            tokenLines.push_back(dfa.scan(line));
        }
    } catch (ScanningFailure &f) {
        return 1;
    }

    for (int i = 0; i < tokenLines.size(); ++i) {
        for (int j = 0; j < tokenLines.at(i).size(); ++j) {
            std::cout << tokenLines.at(i).at(j).getLexeme() << std::endl;
        }
    }

    //try {
        //assemble(tokenLines);
    //} catch (AssemblingFailure &f) {
        //std::cerr << f.getMessage() << std::endl;
        //return 1;
    //}

    return 0;


}
