#include <string>
#include "ParsingFailure.h"
ParsingFailure::ParsingFailure(std::string message):message(message){ }

std::string ParsingFailure::getMessage() const {
    return message;
}
