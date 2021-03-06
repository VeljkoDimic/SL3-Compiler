#include "Node.h"
#include "Production.h"

Node::Node(std::string prod) {
    production = Production(prod);
}

Node::Node(Token t) {
    production = Production(t.getKindString() + ' ' + t.getLexeme());
}

Node::~Node() {
    for (Node* n : children) {
        delete n;
    }
}

void Node::AddChild(Node* n) {
    children.push_front(n);
}

Production Node::getProduction() const {
    return production;
}

std::deque<Node*> Node::getChildren() const {
    return children;
}

std::ostream& operator<< (std::ostream &strm, const Node &a) {
    strm << a.production << std::endl;
    for (Node* n : a.children) {
        strm << *n;
    }
    return strm;
}
