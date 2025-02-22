#ifndef LOADER
#define LOADER

#include <iostream>
#include <vector>
#include <map>

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
    TABLE_TYPE search(const string& element);
    bool contains(const string& element);
private:
    map<string, char> tconst;
};

// ========================== DYNAMIC TABLES ==============================
enum BASE_TYPE {
    BOOL    = 1,
    FLOAT   = 2,
    CHAR    = 3
};

typedef struct TVARIABLE {
    const BASE_TYPE type;
    const unsigned long index;

    TVARIABLE(BASE_TYPE type, unsigned long index) : type(type), index(index) {};
    TVARIABLE() : type(BASE_TYPE::BOOL), index(0) {};
} TVARIABLE;

class DYNAMIC_TCONTROLLER {
public:
    void init(string name, BASE_TYPE type);
    const TVARIABLE& search(const string& element);
    bool contains(const string& element);
private:
    map<string, TVARIABLE> tvariables;
    unsigned long last_index = 0;
};

// ============================ CONTROLLER =================================
class TCONTROLLER {
public:
    STATIC_TCONTROLLER statics;
    DYNAMIC_TCONTROLLER dynamics;
};

#endif
