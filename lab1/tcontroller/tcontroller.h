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
    ALPHABET    = 10, 
    WORDS       = 20, 
    OPERATORS   = 30, 
    SYMBOLS     = 40
};

class STATIC_TCONTROLLER {
public:
    void load_static_table(TABLE_TYPE ttype, const string& filename);
    int search(TABLE_TYPE ttype, const string& element);
    int search(TABLE_TYPE ttype, const string& element, bool& found);
    bool contains(TABLE_TYPE ttype, const string& element);
private:
    vector<string> alphabet;
    vector<string> words;
    vector<string> operators;
    vector<string> symbols;

    vector<string>& get_table(TABLE_TYPE type);
};

// ========================== DYNAMIC TABLES ==============================
class DYNAMIC_TCONTROLLER {
public:
    void setup_file(string file_name);
    void init(string name, BASE_TYPE type, unsigned long scope);
    TVARIABLE& search(const string& element);
    TVARIABLE& search(const string& element, bool& found);
    bool contains(const string& element);
    void save();
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
    DYNAMIC_TCONTROLLER dynamics;
};

// #endif
