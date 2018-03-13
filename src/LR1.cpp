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

    // Read terminals
    int num_terminals = Utils::ReadIntLineFromFile(lr1);
    for (int i = 0; i < num_terminals; ++i) {
        std::string line = "";
        try {
            getline(lr1, line);
            terminals.insert(line);
        } catch(...) {
            throw ParsingFailure("PARSING ERROR: Unable to "
                    "read terminals. Failed at " + line);
        }
    }

    // Read nonterminals
    int num_nonterminals = Utils::ReadIntLineFromFile(lr1);
    for (int i = 0; i < num_nonterminals; ++i) {
        std::string line = "";
        try {
            getline(lr1, line);
            nonterminals.insert(line);
        } catch(...) {
            throw ParsingFailure("PARSING ERROR: Unable to "
                    "read non-terminals. Failed at " + line);
        }
    }

    // Read start symbol
    try {
        getline(lr1, start_symbol);
    } catch(...) {
            throw ParsingFailure("PARSING ERROR: Unable to "
                    "read start symbol");
    }

    // Read productions
    int num_productions = Utils::ReadIntLineFromFile(lr1);
    for (int i = 0; i < num_productions; ++i) {
        std::string line = "";
        try {
            getline(lr1, line);
            productions.push_back(Production(line));
        } catch(...) {
            throw ParsingFailure("PARSING ERROR: Unable to "
                    "read productions. Failed at " + line);
        }
    }

    // Read number of states
    try {
        num_states = Utils::ReadIntLineFromFile(lr1);
    } catch(...) {
            throw ParsingFailure("PARSING ERROR: Unable to "
                    "read number of states");
    }

    // Read actions
    int num_actions = Utils::ReadIntLineFromFile(lr1);
    for (int i = 0; i < num_actions; ++i) {
        std::string line = "";
        try {
            getline(lr1, line);
            std::stringstream line_ss(line);

            int start_state;
            std::string follow;
            std::string action;
            int destination;

            line_ss >> start_state >> follow >>
                action >> destination;

            actions.insert(std::make_pair(
                        std::make_pair(start_state, follow),
                        std::make_pair(action, destination)));
        } catch(...) {
            throw ParsingFailure("PARSING ERROR: Unable to "
                    "read actions. Failed at " + line);
        }
    }
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
