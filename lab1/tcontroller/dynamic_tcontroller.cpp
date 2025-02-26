#include <fstream>
#include <algorithm>
#include <iostream>
#include <filesystem>

#include "tcontroller.h"
#include "exceptions/exceptions.h"

void DYNAMIC_TCONTROLLER::setup_file(string file_name) {
    if (insert_mode == false) return;

    file.open(file_name);
    while (file.peek() != EOF) {
        string key, type;
        int scope;

        file >> key >> type >> scope;
        if (key != "")
            init(key, type_from_string(type), scope);
    }
    file.clear();

    insert_mode = false;
}

void DYNAMIC_TCONTROLLER::init(string name, BASE_TYPE type, unsigned long scope) {
    if (contains(name)) {
        throw variable_exception("cannot redeclare variable");
    }
    TVARIABLE tvariable;
    tvariable.index = last_index++;
    tvariable.scope = scope;
    tvariable.type = type;

    tvariables.insert(name, tvariable);
    
    last_index += 1;

    if (!insert_mode) {
        file << name << " " << tvariable.to_string() << endl;
        file.flush();
    }
    // save();
}

bool DYNAMIC_TCONTROLLER::contains(const string& element) {
    return tvariables.contains(element);
}

TVARIABLE& DYNAMIC_TCONTROLLER::search(const string& element) {
    return tvariables[element];
}

TVARIABLE& DYNAMIC_TCONTROLLER::search(const string& element, bool& found) {
    return tvariables.get(element, found);
}

void DYNAMIC_TCONTROLLER::save() {
    if (insert_mode == true) return;
    file.clear();
    file << tvariables.to_string();
}
