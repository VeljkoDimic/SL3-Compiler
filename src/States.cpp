#include <map>
#include <string>
#include "States.h"

std::map<State, std::string> state_string = {
        {START, "START"},
        {FAIL, "FAIL"},
        {WHITESPACE, "WHITESPACE"},
        {NUM, "NUM"},
        {ID, "ID"},
        {LPAREN, "LPAREN"},
        {RPAREN, "RPAREN"},
        {DEFINE, "DEFINE"},
        {PLUS, "PLUS"},
        {MINUS, "MINUS"},
        {STAR, "STAR"},
        {SLASH, "SLASH"},
        {MOD, "MOD"},
        {EQ, "EQ"},
        {NE, "NE"},
        {LT, "LT"},
        {GT, "GT"},
        {GE, "GE"},
        {AND, "AND"},
        {OR, "OR"},
        {NOT, "NOT"},
        {LOGAND, "LOGAND"},
        {LOGIOR, "LOGIOR"},
        {LOGXOR, "LOGXOR"},
        {LOGNOR, "LOGNOR"},
        {LOGEQV, "LOGEQV"},
        {TRUE, "TRUE"},
        {NIL, "NIL"},
        {COND, "COND"},
        {VAR, "VAR"},
        {WRITE, "WRITE"},
        {LAMBDA, "LAMBDA"}
    };
