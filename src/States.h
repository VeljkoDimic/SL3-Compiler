#ifndef STATES_H
#define STATES_H
#include <map>
#include <string>
//All states
enum State {
    /*  "***" for accepting states */
    START,
    FAIL,
    WHITESPACE,
    NUM,    //***
    ID,     //***
    LPAREN, //***
    RPAREN, //***
    DEFINE, //***
    PLUS,   //***
    MINUS,  //***
    STAR,   //***
    SLASH,  //***
    MOD,    //***
    EQ,     //***
    NE,     //***
    LT,     //***
    GT,     //***
    LE,     //***
    GE,     //***
    AND,    //***
    OR,     //***
    NOT,    //***
    LOGAND, //***
    LOGIOR, //***
    LOGXOR, //***
    LOGNOR, //***
    LOGEQV, //***
    TRUE,   //***
    NIL,    //***
    COND,   //***
    VAR,    //***
    WRITE,  //***
    LAMBDA  //***
};

extern std::map<State, std::string> state_string;

#endif
