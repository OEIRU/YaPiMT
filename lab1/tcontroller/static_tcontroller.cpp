#include "tcontroller.h"
#include <fstream>
#include <algorithm>

#include <iostream>
#include <filesystem>

void STATIC_TCONTROLLER::load_static_table(TABLE_TYPE ttype, const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        tconst[line] = ttype;
    }
    file.close();
}

bool STATIC_TCONTROLLER::contains(const string& element) {
    return tconst.find(element) != tconst.end();
}

TABLE_TYPE STATIC_TCONTROLLER::search(const string& element) {
    return static_cast<TABLE_TYPE>(tconst[element]);
}