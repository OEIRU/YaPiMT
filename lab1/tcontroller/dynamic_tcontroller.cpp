#include "tcontroller.h"
#include "exceptions/exceptions.h"
#include <fstream>
#include <algorithm>

#include <iostream>
#include <filesystem>

void DYNAMIC_TCONTROLLER::init(string name, BASE_TYPE type) {
    if (contains(name)) {
        throw variable_exception("cannot redeclare variable");
    }
    TVARIABLE tvariable(
        type,
        last_index
    );

    tvariables.insert(make_pair(name, tvariable));
    
    last_index += 1;
}

bool DYNAMIC_TCONTROLLER::contains(const string& element) {
    return tvariables.find(element) != tvariables.end();
}

const TVARIABLE& DYNAMIC_TCONTROLLER::search(const string& element) {
    return tvariables[element];
}
