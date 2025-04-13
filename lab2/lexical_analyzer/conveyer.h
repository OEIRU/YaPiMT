#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "../tcontroller/tcontroller.h"
#include "exceptions/exceptions.h"

using namespace std;

enum STATE {
    START,

    WORD,
    SEPARATOR,
    NUMBER, DOUBLE,
    OPERATOR,
    SPACE,

    ERROR_WRONG_NUMBER
};

struct TRANSITION {
    STATE to;
    set<char> possible_chars;
    bool excluding;
    bool is_error;;
    bool is_end;

    TRANSITION(
        STATE to,
        set<char> possible_chars,
        bool excluding = false,
        bool is_end = false,
        bool is_error = false
    ) : 
        to(to),
        possible_chars(possible_chars),
        excluding(excluding),
        is_error(is_error),
        is_end(is_end)
    {};
};

template <typename T>
std::set<T> operator+(const std::set<T>& lhs, const std::set<T>& rhs) {
    std::set<T> result = lhs;
    result.insert(rhs.begin(), rhs.end());
    return result;
}

class CONVEYER {
private:
    map<STATE, vector<TRANSITION>> states;
    STATE current_state = START;
    istringstream input_stream;

    STATIC_TCONTROLLER& tstatic;
    DYNAMIC_TCONTROLLER& tvariables;
    DYNAMIC_TCONTROLLER& tconstants;

    STATE get_next_state(char symbol);

    vector<char> collected_characters;
public:
    CONVEYER(
        const string& input_string, 
        STATIC_TCONTROLLER& tstatic,
        DYNAMIC_TCONTROLLER& tvariables,
        DYNAMIC_TCONTROLLER& tconstants
    ) : tstatic(tstatic), tvariables(tvariables), tconstants(tconstants) {
        input_stream = istringstream(input_string);

        set<char> alphabet;
        set<char> numbers;
        set<char> separator;
        set<char> number_separators = {'.'};
        set<char> spaces = {' ', '\n', '\t'};
        set<char> empty_set;

        vector<string>& talphabet = tstatic.get_table(ALPHABET);
        vector<string>& tnumbers = tstatic.get_table(NUMBERS);
        vector<string>& tseparators = tstatic.get_table(SYMBOLS);

        for (auto it : talphabet) alphabet.insert(it[0]);
        for (auto it : tnumbers) numbers.insert(it[0]);
        for (auto it : tseparators) separator.insert(it[0]);
        
        // ... excluding?, is_error?, is_end?
        states = {
            {START, {
                TRANSITION(WORD,        alphabet),
                TRANSITION(SEPARATOR,   separator),
                TRANSITION(SPACE,       spaces),
                TRANSITION(NUMBER,      numbers),
                TRANSITION(OPERATOR,    alphabet + separator + spaces + numbers, true)
            }},
            {WORD, {
                TRANSITION(WORD,    alphabet + numbers),
                TRANSITION(START,   alphabet + numbers, true, true)
            }},
            {SEPARATOR, {
                TRANSITION(START,   empty_set, true, true)
            }},
            {NUMBER, {
                TRANSITION(NUMBER,  numbers),
                TRANSITION(DOUBLE,  number_separators),
                TRANSITION(START,   number_separators + numbers, true, true)
            }},
            {DOUBLE, {
                TRANSITION(DOUBLE,              numbers),
                TRANSITION(ERROR_WRONG_NUMBER,  number_separators, false, false, true),
                TRANSITION(START,               number_separators + numbers, true, true)
            }},
            {OPERATOR, {
                TRANSITION(OPERATOR,    alphabet + separator + spaces, true),
                TRANSITION(START,       alphabet + separator + spaces, false, true)
            }},
            {SPACE, {
                TRANSITION(START,   empty_set, true, true)
            }}
        };
    };

    string build();
};