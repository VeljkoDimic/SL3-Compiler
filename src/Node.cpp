#include "Node.h"

Node::Node(std::string prod)
            : production(prod) { }

void Node::AddChild(Node n) {
    children.push_back(n);
}

std::ostream& operator<< (std::ostream &strm, const Node &a) {
    strm << a.production << std::endl;
    for (Node n : a.children) {
        strm << n;
    }
    return strm;
}
