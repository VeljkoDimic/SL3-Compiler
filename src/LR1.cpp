#include "LR1.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
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
    //Copy tokens to liste
    std::list<Token> unread_input;

    //Resize to avoid reallocating multiple times
    //unread_input.resize(tokens.size());
    std::copy(std::begin(tokens), std::end(tokens),
              std::end(unread_input));

    //TODO: Change back to stack of Nodes
    //Shift |- onto symbol stack
    symbol_stack.push(unread_input.front().getKindString());
    unread_input.pop_front();
    state_stack.push(0);

    //Push sigma(q0, |-) on state stack
    auto act = actions.find(std::make_pair(
                state_stack.top(), symbol_stack.top()));
    if (act == actions.end()) {
        throw ParsingFailure("PARSING ERROR: Unable to find "
                "action at state " + std::to_string(state_stack.top()) +
                " and symbol " + symbol_stack.top());
    }
    if (std::strcmp(act->second.first.c_str(), "reduce") == 0) {
        throw ParsingFailure("PARSING ERROR: Attempting to reduce "
                "at start state");
    }
    state_stack.push(act->second.second);

    //For each token a in input
    for (auto unread_token : unread_input) {
        std::string unread_symbol = unread_token.getKindString();

        /* ___ REDUCE ___ */
        //while (there is a reduction A -> gamma. {a} in state_stack.top )
        //TODO: Make this a lot more elegant
        while(actions.find(std::make_pair(
                        state_stack.top(), unread_symbol))
                    != actions.end() &&
                strcmp(actions[std::make_pair(
                        state_stack.top(), unread_symbol)]
                    .first.c_str(), "reduce") == 0) {
            std::pair<std::string, int> a =
                actions[std::make_pair(state_stack.top(), unread_symbol)];

            Production gamma = productions.at(a.second);
            int magnitude_gamma = gamma.size;

            std::stringstream production_ss;
            production_ss << gamma;
            Node new_node(production_ss.str());

            //Pop |gamma| symbols off the stack
            for (int i = 0; i < magnitude_gamma; ++i) {
                //new_node.AddChild(Node())
            }
        }
    }





    return Node("");
}
