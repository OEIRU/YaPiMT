#include "exceptions.h"

lexical_exception::lexical_exception(const string& msg) {
    message = PREFIX + ": " + msg;
}

const char* lexical_exception::what() const throw () {
    return message.c_str();
}
