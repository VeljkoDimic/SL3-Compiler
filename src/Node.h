#ifndef NODE_H
#define NODE_H

#include <list>
#include <string>
#include "Utils.h"
#include "Token.h"
#include "Production.h"

class Node {
    private:
        // Child nodes
        std::list<Node> children;

        // Production data initialized, ie "sexps sexp sexps"
        Production production;
    public:
        // Initializes with production
        Node(std::string prod);

        // Initialize with token (ie "ID 5")
        Node(Token t);

        // Add child Node to children
        void AddChild(Node n);

        Production getProduction() const;

        // << overload
        friend std::ostream& operator<< (std::ostream &strm, const Node &a);
};

#endif
