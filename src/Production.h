#ifndef PRODUCTION_H
#define PRODUCTION_h

#include <string>
#include <vector>
#include <ostream>

class Production {
    private:
        // Number of symbols on the rhs
        int size;

        // Left hand side
        std::string lhs;

        // Right hand side
        std::vector<std::string> rhs;
    public:
        // Creates the productions, where string is in form "sexps sexp sexps"
        Production(std::string prod);

        // Get size
        int size() const;

        // Get lhs
        std::string getLhs() const;

        // << overload
        friend std::ostream& operator<< (std::ostream &strm, const Production &a);
}

#endif
