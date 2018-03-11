#include <vector>
#include <string>
#include <ostream>
#include "Production.h"
#include "Utils.h"

Production::Production(std::string prod) {
    std::vector<std::string> tokens = Utils::split(prod, ' ');

    size = tokens.size() - 1;
    lhs = tokens.at(0);

    //Pop front and set to rhs
    tokens.erase(tokens.begin());
    rhs = tokens;
};

int Production::size() const {
    return size;
};

std::string Productions::getLhs() const {
    return lhs;
};

std::ostream& operator<< (std::ostream &strm, const Production &a) {
    strm << lhs;
    for (std::string symbol : rhs) {
        strm << ' ' << symbol;
    }
};
