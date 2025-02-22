#include "tcontroller/tcontroller.h"
#include <iostream>


int main() {
    TCONTROLLER tcontroller;

    tcontroller.statics.load_static_table(TABLE_TYPE::ALPHABET, "tables/alphabet.txt");
    tcontroller.statics.load_static_table(TABLE_TYPE::WORDS, "tables/words.txt");
    tcontroller.statics.load_static_table(TABLE_TYPE::OPERATORS, "tables/operators.txt");
    tcontroller.statics.load_static_table(TABLE_TYPE::SYMBOLS, "tables/symbols.txt");

    // auto res = tcontroller.search("Xdjesf");
    // cout << res;
    // res;
    tcontroller.dynamics.init("x", BASE_TYPE::BOOL);
    tcontroller.dynamics.init("y", BASE_TYPE::FLOAT);
    auto var = tcontroller.dynamics.search("x");;
}