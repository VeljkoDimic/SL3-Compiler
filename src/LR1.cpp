#include "LR1.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include <deque>
#include "Node.h"
#include "ParsingFailure.h"
#include "States.h"

void LR1::ReadLr1(std::deque<std::string> lines) {
    // Read terminals
    int num_terminals = Utils::ReadIntLineFromLines(lines);
    for (int i = 0; i < num_terminals; ++i) {
        std::string line = "";
        try {
            line = lines.at(0).c_str();
            lines.pop_front();
            terminals.insert(line);
        } catch(...) {
            throw ParsingFailure("Unable to "
                    "read terminals. Failed at " + line);
        }
    }

    // Read nonterminals
    int num_nonterminals = Utils::ReadIntLineFromLines(lines);
    for (int i = 0; i < num_nonterminals; ++i) {
        std::string line = "";
        try {
            line = lines.at(0);
            lines.pop_front();
            nonterminals.insert(line);
        } catch(...) {
            throw ParsingFailure("Unable to "
                    "read non-terminals. Failed at " + line);
        }
    }

    // Read start symbol
    try {
        start_symbol = lines.at(0);
        lines.pop_front();
    } catch(...) {
            throw ParsingFailure("Unable to "
                    "read start symbol");
    }

    // Read productions
    int num_productions = Utils::ReadIntLineFromLines(lines);
    for (int i = 0; i < num_productions; ++i) {
        std::string line = "";
        try {
            line = lines.at(0);
            lines.pop_front();
            productions.push_back(Production(line));
        } catch(...) {
            throw ParsingFailure("Unable to "
                    "read productions. Failed at " + line);
        }
    }

    // Read number of states
    try {
        num_states = Utils::ReadIntLineFromLines(lines);
    } catch(...) {
            throw ParsingFailure("Unable to "
                    "read number of states");
    }

    // Read actions
    int num_actions = Utils::ReadIntLineFromLines(lines);
    for (int i = 0; i < num_actions; ++i) {
        std::string line = "";
        try {
            line = lines.at(0);
            lines.pop_front();
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
            throw ParsingFailure("Unable to "
                    "read actions. Failed at " + line);
        }
    }
}

std::pair<std::string, int> LR1::TopAction() const {
    auto act = actions.find(std::make_pair(
                        state_stack.top(),
                        symbol_stack.top()->getProduction().getLhs()));
    if (act == actions.end()) {
        throw ParsingFailure("Unable to find "
                "action at state " + std::to_string(state_stack.top()) +
                " and symbol " + symbol_stack.top()->getProduction().getLhs());
    }
    return act->second;
}

LR1::LR1() {
    std::deque<std::string> d;
    ReadLr1(d);
}

LR1::LR1(std::deque<std::string> lines) {
    ReadLr1(lines);
}

LR1::~LR1() {
}

Node* LR1::Parse(std::vector<Token> tokens) {
    //Copy tokens to list
    std::list<Token> unread_input;
    std::copy(std::begin(tokens), std::end(tokens),
              std::back_inserter(unread_input));
    unread_input.push_front(Token(BOF, "BOF"));
    unread_input.push_back(Token(EEOF, "EOF"));

    //Shift |- onto symbol stack
    symbol_stack.push(new Node(unread_input.front()));
    unread_input.pop_front();
    state_stack.push(0);

    //Push sigma(q0, |-) on state stack
    std::pair<std::string, int> first_action = TopAction();
    if (std::strcmp(first_action.first.c_str(), "reduce") == 0) {
        throw ParsingFailure("Attempting to reduce "
                "at start state");
    }
    state_stack.push(first_action.second);

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
            Node* new_node = new Node(production_ss.str());

            //Pop |gamma| symbols & states off the stack
            for (int i = 0; i < magnitude_gamma; ++i) {
                new_node->AddChild(symbol_stack.top());
                symbol_stack.pop();
                state_stack.pop();
            }

            //Push A on symbol stack
            symbol_stack.push(new_node);

            //Push sigma(state_stack.top, A) onto the state_stack
            //Shift if it is a shift action, otherwise go back through loop
            std::pair<std::string, int> curr_action = TopAction();
            if (std::strcmp(first_action.first.c_str(), "shift") == 0) {
                state_stack.push(curr_action.second);
            }
        }
        /* ___ END REDUCE ___ */

        /* ___ SHIFT ___ */
        //Shift a onto symbol stack
        symbol_stack.push(new Node(unread_token));

        //if (sigma(state_stack.top, a) == undefined) report parse error
        std::pair<std::string, int> curr_action = TopAction();
        if (std::strcmp(first_action.first.c_str(), "reduce") == 0) {
            throw ParsingFailure("Attempting to reduce "
                    "at shift state at state " +
                    std::to_string(state_stack.top()) + "and symbol " +
                    symbol_stack.top()->getProduction().getLhs());
        }
        //else push sigma(state_stack.top, a) onto the state_stack
        state_stack.push(curr_action.second);
    }

    //If it is done, add start state
    if (symbol_stack.top()->getProduction().getLhs() != "EOF") {
        throw ParsingFailure("Reached end of file "
                "without 'EOF' symbol on stack");
    }
    //TODO: Remove hardcoding
    Node* new_node = new Node("start BOF sexp EOF");
    while (!symbol_stack.empty()) {
        new_node->AddChild(symbol_stack.top());
        symbol_stack.pop();
    }
    symbol_stack.push(new_node);

    return symbol_stack.top();
}
