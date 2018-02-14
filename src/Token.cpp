#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "Token.h"
#include "States.h"
#include "DFA.h"

Token::Token(State kind, std::string lexeme)
        : kind(kind), lexeme(lexeme) { }

State Token::getKind() const {
    return kind;
}

std::string Token::getLexeme() const {
    return lexeme;
}

std::ostream& operator<< (std::ostream &strm, const Token &a) {
    return strm << "TOKEN(" << state_string[a.getKind()]
            << ",'" << a.getLexeme() << "')";
}

long long Token::toLong() const {
    std::istringstream iss;
    long long result;
    iss.str(lexeme);
    iss >> result;
    return result;
}

int Token::toInt() const {
    return (int)toLong();
}
