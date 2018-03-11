#ifndef LR1_NODE_H
#define LR1_NODE_h

#include <vector>
#include <string>
#include "LR1.h"

class Lr1Node {
    private:
        // Child nodes
        std::vector<Node> children;

        // Production data initialized, ie "sexps sexp sexps"
        std::string production;
    public:
        // Initializes with production
        Node(std::string prod);

        // Add child Node to children
        void AddChild(Node n);

        // << overload
        friend std::ostream& operator<< (std::ostream &strm, const Node &a);
}

#endif
