#include "Lr1Node.h"
#include "LR1.h"

Lr1Node::Node(std::string prod) {
    production = prod;
};

void Lr1Node::AddChild(Node n) {
    children.push_back(n);
};

std::ostream& operator<< (std::ostream &strm, const Node &a) {
    strm << production << std::endl;
    for (Node n : children) {
        strm << n;
    }
};
