#ifndef DFA_H
#define DFA_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "DFA.h"
#include "States.h"
#include "Token.h"

class DFA {
    private:
        std::set<State>* acceptingStates;

        // Return tokenized input as a vector of Tokens
        std::vector<Token> simplifiedMaximalMunch(std::string input) const;
    public:
        DFA();

        // Return the next state based on current state and next character
        State transition(State state, char nextChar) const;

        // Return if the state returned from transition is a failure
        bool failed(State state) const;

        // Return if the state returned from transition is accepting
        bool accept(State state) const;

        // Return starting state of DFA
        State start() const;

        // Scans the input and returns the list of tokens
        std::vector<Token> scan(std::string input) const;
};
#endif
