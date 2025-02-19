#include "tcontroller.h"
#include <fstream>
#include <algorithm>

#include <iostream>
#include <filesystem>

void TCONTROLLER::load_static_table(TABLE_TYPE ttype, const string& filename) {
    ifstream file(filename);
    vector<string>& table = get_table_by_type(ttype);
    string line;
    while (getline(file, line)) {
        table.push_back(line);
    }
    file.close();
}

bool TCONTROLLER::search(TABLE_TYPE ttype, const string& element) {
    vector<string>& table = get_table_by_type(ttype);

    return binary_search(table.begin(), table.end(), element);
}

vector<string> &TCONTROLLER::get_table_by_type(TABLE_TYPE &table) {
    switch (table) {
    case ALPHABET:
        return tconst.alphabet;
    case WORDS:
        return tconst.words;
    case SYMBOLS:
        return tconst.symbols;
    case OPERATORS:
        return tconst.operators;
    }
    return tconst.words;
}