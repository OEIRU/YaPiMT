#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <set>

#include "tvariable.h"
#include "hashmap/hashmap.h"

using namespace std;

// ========================== STATIC TABLES ==============================
enum TABLE_TYPE {
    ALPHABET = 10,
    NUMBERS = 20,
    WORDS = 30,
    OPERATORS = 40,
    SYMBOLS = 50,

    VARIABLES = 110,
    CONSTANTS = 120
};

class STATIC_TCONTROLLER {
public:
    int binary_search(const vector<string>& table, const string& element);
    void load_static_table(TABLE_TYPE ttype, const string& filename);
    int search(TABLE_TYPE ttype, const string& element);
    int search(TABLE_TYPE ttype, const string& element, bool& found);
    const string& get(TABLE_TYPE, int index);
    bool contains(TABLE_TYPE ttype, const string& element);
    vector<string>& get_table(TABLE_TYPE type);
private:
    vector<string> alphabet;
    vector<string> words;
    vector<string> operators;
    vector<string> symbols;
    vector<string> numbers;
};

// ========================== DYNAMIC TABLES ==============================
class DYNAMIC_TCONTROLLER {
public:
    void setup_file(string file_name);
    void modify(string name, BASE_TYPE new_type, unsigned long new_scope);
    void init(string name, BASE_TYPE type, unsigned long scope);
    TVARIABLE& init(string name, int index = -1);
    TVARIABLE& search(const string& element);
    TVARIABLE& search(const string& element, bool& found);
    bool contains(const string& element);
    void save(const string& filename, const string& name);
private:
    HASHMAP<TVARIABLE> tvariables;
    fstream file;
    unsigned long last_index = 0;
    bool insert_mode = true;
};

// ============================ CONTROLLER =================================
class TCONTROLLER {
public:
    STATIC_TCONTROLLER statics;
    DYNAMIC_TCONTROLLER variables;
    DYNAMIC_TCONTROLLER constants;
};
