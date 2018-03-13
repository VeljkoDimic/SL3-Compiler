#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include "Token.h"
#include "DFA.h"
#include "States.h"
#include "ScanningFailure.h"

// Return tokenized input as a vector of Tokens
std::vector<Token> DFA::simplifiedMaximalMunch(std::string input) const {
    std::vector<Token> result;

    State state = start();
    std::string munched_input;

    for (auto position = input.begin(); position != input.end();) {
        State prev_state = state;
        state = transition(state, *position);

        if (!failed(state)) {
            munched_input += *position;
            prev_state = state;

            ++position;
        }

        if (position == input.end() || failed(state)) {
            if (accept(prev_state)) {
                result.push_back(Token(prev_state, munched_input));

                munched_input = "";
                state = start();
            } else {
                if (failed(state)) {
                    munched_input += *position;
                }
                throw ScanningFailure("SCANNING ERROR: Simplified maximal "
                        "munch failed on input: "
                        + munched_input);
            }
        }
    }

    return result;
}

DFA::DFA() {
    accepting_states = std::set<State>{
                            NUM,
                            ID,
                            WHITESPACE,
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
}

// Return the next state based on current state and next character
State DFA::transition(State state, char next_char) const {
    char c = tolower(next_char);
    if (state == START) {
        if (isdigit(c))         return NUM;
        else if (isspace(c))    return WHITESPACE;
        else if (c == '(')      return LPAREN;
        else if (c == ')')      return RPAREN;
        else if (c == '+')      return PLUS;
        else if (c == '-')      return MINUS;
        else if (c == '*')      return STAR;
        else if (c == '/')      return SLASH;
        else if (c == '%')      return MOD;
        else if (c == '<')      return LT;
        else if (c == '>')      return GT;
        else if (isalpha(c))    return ID;
    } else if (state == NUM) {
        if (isdigit(c))         return NUM;
    } else if (state == ID) {
        if (isdigit(c)
                || isalpha(c))  return ID;
    } else if (state == SLASH) {
        if (c == '=')           return NE;
    } else if (state == LT) {
        if (c == '=')           return LE;
    } else if (state == GT) {
        if (c == '=')           return GE;
    } else if (state == WHITESPACE) {
        if (isspace(c))         return WHITESPACE;
    }
    return FAIL;
}

// Return if the state returned from transition is a failure
bool DFA::failed(State state) const {
    return state == FAIL;
}

// Return if the state returned from transition is accepting
bool DFA::accept(State state) const {
    return accepting_states.end() != accepting_states.find(state);
}

// Return starting state of DFA
State DFA::start() const {
    return START;
}

// Scans the input and returns the list of tokens
std::vector<Token> DFA::scan(std::string input) const {
    std::vector<Token> tokens = simplifiedMaximalMunch(input);
    std::vector<Token> new_tokens;


    std::map<std::string, State> keywords = {
            {"define", DEFINE},
            {"mod", MOD},
            {"and", AND},
            {"or", OR},
            {"not", NOT},
            {"logand", LOGAND},
            {"logior", LOGIOR},
            {"logxor", LOGXOR},
            {"lognor", LOGNOR},
            {"logeqv", LOGEQV},
            {"t", TRUE},
            {"nil", NIL},
            {"cond", COND},
            {"var", VAR},
            {"write", WRITE},
            {"lambda", LAMBDA}
            };


    //Remove whitespace and separate IDs from keywords
    tokens.erase(std::remove_if(tokens.begin(), tokens.end(),
                [keywords](Token& t) {
                    if (keywords.find(t.getLexeme()) != keywords.end()) {
                        t = Token(keywords.at(t.getLexeme()),t.getLexeme());
                    }
                    return t.getKind() == WHITESPACE;
                }),
            tokens.end());

    return tokens;
}
