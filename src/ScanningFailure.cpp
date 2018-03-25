#include <string>
#include "ScanningFailure.h"
ScanningFailure::ScanningFailure(std::string message):message(message){ }

std::string ScanningFailure::getMessage() const {
    return "SCANNING ERROR: " + message;
}
