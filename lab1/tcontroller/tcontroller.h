#ifndef LOADER
#define LOADER

#include <iostream>
#include <vector>

using namespace std;

typedef struct TCONSTANT {
    vector<string> alphabet;
    vector<string> words;
    vector<string> operators;
    vector<string> symbols;
} TCONSTANT;

enum TABLE_TYPE {
    ALPHABET, WORDS, OPERATORS, SYMBOLS
};

class TCONTROLLER {
public:
    void load_static_table(TABLE_TYPE ttype, const string& filename);
    bool search(TABLE_TYPE ttype, const string& element);
private:
    TCONSTANT tconst;

    vector<string> &get_table_by_type(TABLE_TYPE &table);
};

#endif
