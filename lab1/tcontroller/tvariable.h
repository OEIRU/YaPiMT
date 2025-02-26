#pragma once

#include <string>

using namespace std;

enum BASE_TYPE {
    BOOL    = 1,
    FLOAT   = 2,
    CHAR    = 3
};

typedef struct TVARIABLE {
    BASE_TYPE type;
    unsigned long index;
    unsigned long scope;

    TVARIABLE() = default;

    string to_string();
} TVARIABLE;

BASE_TYPE type_from_string(const string& element);