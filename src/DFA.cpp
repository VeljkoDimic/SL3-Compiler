#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "Token.h"
#include "DFA.h"
#include "States.h"

// Return tokenized input as a vector of Tokens
std::vector<Token> DFA::simplifiedMaximalMunch(std::string input) const {
    return std::vector<Token>();
};

DFA::DFA() {
acceptingStates = new std::set<State>{
                            NUM,
                            ID,
                            LPAREN,
                            RPAREN,
                            DEFINE,
                            PLUS,
                            MINUS,
                            STAR,
                            SLASH,
                            MOD,
                            EQ,
                            NE,
                            LT,
                            GT,
                            LE,
                            GE,
                            AND,
                            OR,
                            NOT,
                            LOGAND,
                            LOGIOR,
                            LOGXOR,
                            LOGNOR,
                            TRUE,
                            NIL,
                            COND,
                            VAR,
                            WRITE,
                            LAMBDA
                    };
};

// Return the next state based on current state and next character
State DFA::transition(State state, char nextChar) const {
    char c = tolower(nextChar);
    if (state == START) {
        if (isdigit(c))         return NUM;
        else if (isspace(c))    return WHITESPACE;
        else if (c == '(')      return LPAREN;
        else if (c == ')')      return RPAREN;
        else if (c == 'd')      return D;
        else if (c == '+')      return PLUS;
        else if (c == '-')      return MINUS;
        else if (c == '*')      return STAR;
        else if (c == '/')      return SLASH;
        else if (c == '<')      return LT;
        else if (c == '>')      return GT;
        else if (c == 'a')      return A;
        else if (c == 'o')      return O;
        else if (c == 'n')      return N;
        else if (c == 'l')      return L;
        else if (c == 't')      return TRUE;
        else if (c == 'c')      return C;
        else if (c == 'v')      return V;
        else if (c == 'w')      return W;
        else if (isalpha(c))    return ID;
    } else if (state == NUM) {
        if (isdigit(c))         return NUM;
    } else if (state == ID) {
        if (isdigit(c)
                || isalpha(c))  return ID;
    } else if (state == D) {
        if (c == 'e')           return DE;
        else if (isalpha(c))    return ID;
    } else if (state == DE) {
        if (c == 'f')           return DEF;
        else if (isalpha(c))    return ID;
    } else if (state == DEF) {
        if (c == 'i')           return DEFI;
        else if (isalpha(c))    return ID;
    } else if (state == DEFI) {
        if (c == 'n')           return DEFIN;
        else if (isalpha(c))    return ID;
    } else if (state == DEFIN) {
        if (c == 'e')           return DEFINE;
        else if (isalpha(c))    return ID;
    } else if (state == M) {
        if (c == 'o')           return MO;
        else if (isalpha(c))    return ID;
    } else if (state == MO) {
        if (c == 'd')           return MOD;
        else if (isalpha(c))    return ID;
    } else if (state == SLASH) {
        if (c == '=')           return NE;
    } else if (state == LT) {
        if (c == '=')           return LE;
    } else if (state == GT) {
        if (c == '=')           return GE;
    } else if (state == A) {
        if (c == 'n')           return AN;
        else if (isalpha(c))    return ID;
    } else if (state == AN) {
        if (c == 'd')           return AND;
        else if (isalpha(c))    return ID;
    } else if (state == O) {
        if (c == 'r')           return OR;
        else if (isalpha(c))    return ID;
    } else if (state == N) {
        if (c == 'o')           return NO;
        else if (c == 'i')      return NI;
        else if (isalpha(c))    return ID;
    } else if (state == NO) {
        if (c == 't')           return NOT;
        else if (isalpha(c))    return ID;
    } else if (state == L) {
        if (c == 'o')           return LO;
        else if (c == 'a')      return LA;
        else if (isalpha(c))    return ID;
    } else if (state == LO) {
        if (c == 'g')           return LOG;
        else if (isalpha(c))    return ID;
    } else if (state == LOG) {
        if (c == 'a')           return LOGA;
        else if (c == 'i')      return LOGI;
        else if (c == 'x')      return LOGX;
        else if (c == 'n')      return LOGN;
        else if (c == 'e')      return LOGE;
        else if (isalpha(c))    return ID;
    } else if (state == LOGA) {
        if (c == 'n')           return LOGAN;
        else if (isalpha(c))    return ID;
    } else if (state == LOGAN) {
        if (c == 'd')           return LOGAND;
        else if (isalpha(c))    return ID;
    } else if (state == LOGI) {
        if (c == 'o')           return LOGIO;
        else if (isalpha(c))    return ID;
    } else if (state == LOGIO) {
        if (c == 'r')           return LOGIOR;
        else if (isalpha(c))    return ID;
    } else if (state == LOGX) {
        if (c == 'o')           return LOGXO;
        else if (isalpha(c))    return ID;
    } else if (state == LOGXO) {
        if (c == 'r')           return LOGXOR;
        else if (isalpha(c))    return ID;
    } else if (state == LOGN) {
        if (c == 'o')           return LOGNO;
        else if (isalpha(c))    return ID;
    } else if (state == LOGNO) {
        if (c == 'r')           return LOGNOR;
        else if (isalpha(c))    return ID;
    } else if (state == LOGE) {
        if (c == 'q')           return LOGEQ;
        else if (isalpha(c))    return ID;
    } else if (state == LOGEQ) {
        if (c == 'v')           return LOGEQV;
        else if (isalpha(c))    return ID;
    } else if (state == NI) {
        if (c == 'l')           return NIL;
        else if (isalpha(c))    return ID;
    } else if (state == C) {
        if (c == 'o')           return CO;
        else if (isalpha(c))    return ID;
    } else if (state == CO) {
        if (c == 'n')           return CON;
        else if (isalpha(c))    return ID;
    } else if (state == CON) {
        if (c == 'd')           return COND;
        else if (isalpha(c))    return ID;
    } else if (state == V) {
        if (c == 'a')           return VA;
        else if (isalpha(c))    return ID;
    } else if (state == VA) {
        if (c == 'r')           return VAR;
        else if (isalpha(c))    return ID;
    } else if (state == W) {
        if (c == 'r')           return WR;
        else if (isalpha(c))    return ID;
    } else if (state == WR) {
        if (c == 'i')           return WRI;
        else if (isalpha(c))    return ID;
    } else if (state == WRI) {
        if (c == 't')           return WRIT;
        else if (isalpha(c))    return ID;
    } else if (state == WRIT) {
        if (c == 'e')           return WRITE;
        else if (isalpha(c))    return ID;
    } else if (state == LA) {
        if (c == 'm')           return LAM;
        else if (isalpha(c))    return ID;
    } else if (state == LAM) {
        if (c == 'b')           return LAMB;
        else if (isalpha(c))    return ID;
    } else if (state == LAMB) {
        if (c == 'd')           return LAMBD;
        else if (isalpha(c))    return ID;
    } else if (state == LAMBD) {
        if (c == 'a')           return LAMBDA;
        else if (isalpha(c))    return ID;
    }
    return START;
};

// Return if the state returned from transition is a failure
bool DFA::failed(State state) const {
    return state == FAIL;
};

// Return if the state returned from transition is accepting
bool DFA::accept(State state) const {
    return acceptingStates->end() != acceptingStates->find(state);
};

// Return starting state of DFA
State DFA::start() const {
    return START;
};

// Scans the input and returns the list of tokens
std::vector<Token> DFA::scan(std::string input) const {
    std::cout << "SCAN 1: " << input << std::endl;
    std::vector<Token> tokens = simplifiedMaximalMunch(input);
    std::vector<Token> newTokens;
    std::cout << tokens.size() << std::endl;
    for (auto it = tokens.begin(); it != tokens.end(); it++) {
        std::cout << it->getLexeme();
    }


    auto it = std::copy_if(tokens.begin(), tokens.end(),
            std::back_inserter(newTokens),
            [](Token t){return t.getKind() != WHITESPACE;} );
    //Remove whitespace
    //for (auto &token : tokens) {
        //if (token.kind == WHITESPACE){
    //}

    return tokens;
};

