#ifndef DFA_N
#define DFA_N
class DFA {
    private:
        // Set of accepting states TODO: Change all states to enum???
        std::set<std::string> acceptingStates;

        // Return tokenized input as a vector of Tokens
        std::vector<Token> simplifiedMaximalMunch(std::string input) const;
    public:
        DFA();

        // Return string of the next state based on current state and next character
        std::string transition(std::string state, char nextChar) const;

        // Return if the state returned from transition is a failure
        bool failed(std::string state) const;

        // Return if the state returned from transition is accepting
        bool accept(std::string state) const;

        // Return starting state of DFA
        std::string start() const;

        // Scans the input and returns the list of tokens
        std::vector<Token> scan(std::string input) const;
};
#endif
