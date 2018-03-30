#ifndef LR1_H
#define LR1_H

#include <stack>
#include <string>
#include <set>
#include <vector>
#include <deque>
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
        std::stack<Node*> symbol_stack;

        // State stack
        std::stack<int> state_stack;

        // Reads .lr1 file lines and populates LR1
        void ReadLr1(std::deque<std::string> lines);

        // actions[state_stack.head, symbol_stack.head]
        std::pair<std::string, int> TopAction() const;
    public:
        // Default constructor
        LR1();

        // Constructor with given LR1 file
        LR1(std::deque<std::string> lines);

        // Destructor
        virtual ~LR1();

        // Parses the tokens and outputs root of the parse tree
        Node* Parse(std::vector<Token> tokens);
};

#endif
