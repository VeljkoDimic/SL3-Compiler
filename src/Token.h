#ifndef TOKEN_H
#define TOKEN_H

#include "States.h"

class Token {
    private:
        State kind;
        std::string lexeme;
    public:
        Token(State kind, std::string lexeme);

        State getKind() const;
        std::string getLexeme() const;

        friend std::ostream& operator<< (std::ostream &strm, const Token &a);

        long long toLong() const;
        int toInt() const;
};

#endif
