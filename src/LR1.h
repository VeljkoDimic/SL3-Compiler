#ifndef LR1_H
#define LR1_h

#include <stack>
#include <string>
#include <set>
#include <vector>
#include "Production.h"
#include "Lr1Node.h"
#include "Token.h"

typedef Lr1Node Node;
typedef std::map<std::pair<int, std::string>,
                 std::pair<std::string, int>> Actions;

class LR1 {
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

        // Symbol stack
        std::stack<Node> symbol_stack;

        // State stack
        std::stack<int> state_stack;

        // Reads a .lr1 file and populates LR1
        void ReadLr1(std::string file_name);
    public:
        LR1();
        LR1(std::string file_name);
        Node Parse(std::vector<Token> tokens) const;
}

#endif