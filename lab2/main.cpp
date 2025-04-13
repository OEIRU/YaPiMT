#include <iostream>
#include <stdio.h>

#include "tcontroller/tcontroller.h"
#include "lexical_analyzer/lexical_analyzer.h"

using namespace std;

void menu() {
    TCONTROLLER tcontroller;

    tcontroller.statics.load_static_table(TABLE_TYPE::ALPHABET, "tables/alphabet.txt");
    tcontroller.statics.load_static_table(TABLE_TYPE::WORDS, "tables/words.txt");
    tcontroller.statics.load_static_table(TABLE_TYPE::OPERATORS, "tables/operators.txt");
    tcontroller.statics.load_static_table(TABLE_TYPE::SYMBOLS, "tables/symbols.txt");
    tcontroller.statics.load_static_table(TABLE_TYPE::NUMBERS, "tables/numbers.txt");
    tcontroller.variables.setup_file("tables/variables.txt");
    tcontroller.constants.setup_file("tables/constants.txt");

    LEXICAL_ANALYZER lexical_analyzer(tcontroller.statics, tcontroller.variables, tcontroller.constants);

    string filename;
    // cout << "Source code filename: ";
    // cin >> filename;5
    // cout << lexical_analyzer.build_from_file(filename);
    cout << lexical_analyzer.build_from_file("CPP.txt");
}

int main() {
    menu();
}