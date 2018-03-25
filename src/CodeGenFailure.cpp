#include <string>
#include "CodeGenFailure.h"
CodeGenFailure::CodeGenFailure(std::string message):message(message){ }

std::string CodeGenFailure::getMessage() const {
    return "CODE GENERATION ERROR: " + message;
}
