#pragma once

#include <string>

using namespace std;

class lexical_exception : public exception {
public:
    lexical_exception(const string& msg);

    const char* what() const throw ();

private:
    string message;
    const string PREFIX = "Lexical error";
};
