#include "exceptions.h"

variable_exception::variable_exception(const string& msg) {
    message = PREFIX + ": " + msg;
}

const char* variable_exception::what() const throw () {
    return message.c_str();
}
