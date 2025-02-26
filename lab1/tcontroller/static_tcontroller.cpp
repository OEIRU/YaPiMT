#include <fstream>
#include <algorithm>
#include <iostream>
#include <filesystem>

#include "tcontroller.h"

int binary_search(const std::vector<std::string>& table, const std::string& element) {
    int low = 0;
    int high = table.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (table[mid] == element)
            return mid;
        else if (table[mid] < element)
            low = mid + 1; 
        else
            high = mid - 1;
    }
    return -1;
}

void STATIC_TCONTROLLER::load_static_table(TABLE_TYPE ttype, const string& filename) {
    ifstream file(filename);
    vector<string>& table = get_table(ttype);
    string line;
    while (getline(file, line)) {
        table.push_back(line);
    }
    file.close();
}

bool STATIC_TCONTROLLER::contains(TABLE_TYPE ttype, const string& element) {
    bool found = false;
    search(ttype, element, found);
    return found;
}

int STATIC_TCONTROLLER::search(TABLE_TYPE ttype, const string& element) {
    vector<string>& table = get_table(ttype);
    return binary_search(table, element);
}

int STATIC_TCONTROLLER::search(TABLE_TYPE ttype, const string& element, bool& found) {
    vector<string>& table = get_table(ttype);
    int distance = search(ttype, element);
    found = distance != -1;
    return distance;
}

vector<string>& STATIC_TCONTROLLER::get_table(TABLE_TYPE ttype) {
    switch (ttype) {
        case TABLE_TYPE::ALPHABET: return alphabet;
        case TABLE_TYPE::WORDS: return words;
        case TABLE_TYPE::OPERATORS: return operators;
        case TABLE_TYPE::SYMBOLS: return symbols;
    }

    throw runtime_error("Unknown table");
}