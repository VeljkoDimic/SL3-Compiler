#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <string>
#include <vector>
#include <ostream>

class Production {
    private:
        // Left hand side
        std::string lhs;

        // Right hand side
        std::vector<std::string> rhs;
    public:
        // Default empty constructor. Should not need to be used
        Production();

        // Creates the productions, where string is in form "sexps sexp sexps"
        Production(std::string prod);

        // Number of symbols on the rhs
        int size;

        // Get lhs
        std::string getLhs() const;

        // Get rhs
        std::vector<std::string> getRhs() const;

        // << overload
        friend std::ostream& operator<< (std::ostream &strm, const Production &a);
};

#endif
