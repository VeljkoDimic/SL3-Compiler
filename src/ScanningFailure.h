#ifndef SCANNING_FAILURE_H
#define SCANNING_FAILURE_H

// Scanning failure class
class ScanningFailure {
    private:
        std::string message;
    public:
        ScanningFailure(std::string message);

        std::string getMessage() const;
};

#endif
