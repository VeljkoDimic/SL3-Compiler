#ifndef TOKEN_H
#define TOKEN_H
//namespace SL3 {

enum Kind {ID, INT, HEXINT};

class Token {
    private:
        Kind kind;
        std::string lexeme;
    public:
        Token(Kind kind, std::string lexeme);

        Kind getKind() const;
        std::string getLexeme() const;

        long long toLong() const;
        int toInt() const;
};
//} //End Namespace

#endif
