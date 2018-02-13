#ifndef STATES_H
#define STATES_H
#include <set>
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
    D,
    DE,
    DEF,
    DEFI,
    DEFIN,
    DEFINE, //***
    PLUS,   //***
    MINUS,  //***
    STAR,   //***
    SLASH,  //***
    M,
    MO,
    MOD,    //***
    EQ,     //***
    NE,     //***
    LT,     //***
    GT,     //***
    LE,     //***
    GE,     //***
    A,
    AN,
    AND,    //***
    O,
    OR,     //***
    N,
    NO,
    NOT,    //***
    L,
    LO,
    LOG,
    LOGA,
    LOGAN,
    LOGAND, //***
    LOGI,
    LOGIO,
    LOGIOR, //***
    LOGX,
    LOGXO,
    LOGXOR, //***
    LOGN,
    LOGNO,
    LOGNOR, //***
    LOGE,
    LOGEQ,
    LOGEQV, //***
    TRUE,   //***
    //N,
    NI,
    NIL,    //***
    C,
    CO,
    CON,
    COND,   //***
    V,
    VA,
    VAR,
    W,
    WR,
    WRI,
    WRIT,
    WRITE,  //***
    //L,
    LA,
    LAM,
    LAMB,
    LAMBD,
    LAMBDA  //***
};
#endif
