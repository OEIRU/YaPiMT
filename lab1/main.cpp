#include "tcontroller/tcontroller.h"
#include <iostream>


int main() {
    TCONTROLLER tcontroller;

    tcontroller.load_static_table(TABLE_TYPE::ALPHABET, "tables/alphabet.txt");
    tcontroller.load_static_table(TABLE_TYPE::WORDS, "tables/words.txt");
    tcontroller.load_static_table(TABLE_TYPE::OPERATORS, "tables/operators.txt");
    tcontroller.load_static_table(TABLE_TYPE::SYMBOLS, "tables/symbols.txt");

    auto res = tcontroller.search(TABLE_TYPE::ALPHABET, "X");
    cout << res;
    res;
}