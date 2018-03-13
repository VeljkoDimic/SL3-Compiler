#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include "Utils.h"

class Node {
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
};

#endif
