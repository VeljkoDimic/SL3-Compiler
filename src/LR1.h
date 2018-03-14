#ifndef LR1_H
#define LR1_H

#include <stack>
#include <string>
#include <set>
#include <vector>
#include "Production.h"
#include "Node.h"
#include "Token.h"
#include "Utils.h"

class LR1 {
    typedef std::map<std::pair<int, std::string>,
                     std::pair<std::string, int>> Actions;

    private:
        // Terminal symbols
        std::set<std::string> terminals;

        // Nonterminal symbols
        std::set<std::string> nonterminals;

        // Start symbol
        std::string start_symbol;

        // Productions in the grammar
        std::vector<Production> productions;

        // LR1 actions
        Actions actions;

        // Number of states in the LR1 file
        int num_states;

        // Symbol stack
        std::stack<std::string> symbol_stack;

        // State stack
        std::stack<int> state_stack;

        // Reads a .lr1 file and populates LR1
        void ReadLr1(std::string file_name);
    public:
        LR1();
        LR1(std::string file_name);
        Node Parse(std::vector<Token> tokens);
};

#endif
