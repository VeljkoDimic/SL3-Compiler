#ifndef TOKEN_H
#define TOKEN_H
#include "States.h"

//namespace SL3 {


class Token {
    private:
        State kind;
        std::string lexeme;
    public:
        Token(State kind, std::string lexeme);

        State getKind() const;
        std::string getLexeme() const;

        long long toLong() const;
        int toInt() const;
};
//} //End Namespace

#endif
