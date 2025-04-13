#include <sstream>

#include "tcontroller.h"

using namespace std;

BASE_TYPE type_from_string(const string& element) {
    if (element == "bool") return BOOL;
    if (element == "float") return FLOAT;
    if (element == "char") return CHAR;
}

string type_to_string(BASE_TYPE type) {
    switch (type) {
    case BOOL: return "bool";
    case FLOAT: return "float";
    case CHAR: return "char";
    }
}

string TVARIABLE::to_string() {
    stringstream res;
    res // << type_to_string(type) << " "
        << index;//                << " "
        // << scope;
    return res.str();
}
