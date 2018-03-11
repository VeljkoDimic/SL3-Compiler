#ifndef PARSING_FAILURE_H
#define PARSING_FAILURE_H

// Parsing failure class
class ParsingFailure {
    private:
        std::string message;
    public:
        ParsingFailure(std::string message);

        std::string getMessage() const;
};

#endif
