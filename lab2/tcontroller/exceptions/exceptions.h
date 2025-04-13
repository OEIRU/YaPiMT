#pragma once

#include <string>

using namespace std;

class variable_exception : public exception {
public:
    variable_exception(const string& msg);

    const char* what() const throw ();

private:
    string message;
    const string PREFIX = "Variable error";
};
