#include <vector>
#include <string>
#include <ostream>
#include "Production.h"
#include "Utils.h"

Production::Production() {
    lhs = "";
    rhs = std::vector<std::string>();
}

Production::Production(std::string prod) {
    std::vector<std::string> tokens = Utils::split(prod, ' ');

    size = tokens.size() - 1;
    lhs = tokens.at(0);

    //Pop front and set to rhs
    tokens.erase(tokens.begin());
    rhs = tokens;
}

std::string Production::getLhs() const {
    return lhs;
}

std::vector<std::string> Production::getRhs() const {
    return rhs;
}

std::ostream& operator<< (std::ostream &strm, const Production &a) {
    strm << a.lhs;
    for (std::string symbol : a.rhs) {
        strm << ' ' << symbol;
    }
    return strm;
}
