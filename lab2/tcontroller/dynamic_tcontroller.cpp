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
        int scope, index;

        // file >> key >> type >> scope;
        file >> key >> index;
        if (key != "")
            init(key, index);
            // init(key, type_from_string(type), scope);
    }
    file.clear();

    insert_mode = false;
}

void DYNAMIC_TCONTROLLER::modify(string name, BASE_TYPE new_type, unsigned long new_scope) {
    if (!contains(name)) {
        throw variable_exception("Variable '" + name + "' not found");
    }
    
    TVARIABLE& tvariable = tvariables[name];

    tvariable.type = new_type;
    tvariable.scope = new_scope;

    save("tables/variables.txt", name);
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
}

TVARIABLE& DYNAMIC_TCONTROLLER::init(string name, int index) {
    if (contains(name)) {
        throw variable_exception("cannot redeclare variable");
    }
    TVARIABLE tvariable;
    tvariable.index = index == -1 ? last_index : index;
    last_index += 1;

    tvariables.insert(name, tvariable);

    if (!insert_mode) {
        file << name << " " << tvariable.to_string() << endl;
        file.flush();
    }

    return tvariables.get(name);
}

bool DYNAMIC_TCONTROLLER::contains(const string& element) {
    return tvariables.contains(element);
}

TVARIABLE& DYNAMIC_TCONTROLLER::search(const string& element) {
    return tvariables[element];
}

TVARIABLE& DYNAMIC_TCONTROLLER::search(const string& element, bool& found) {
    return *tvariables.get(element, found);
}

void DYNAMIC_TCONTROLLER::save(const string& filename, const string& name) {
    if (insert_mode) return;

    vector<string> lines;
    string line;

    ifstream in_file(filename);
    if (in_file.is_open()) {
        while (getline(in_file, line)) {
            istringstream iss(line);
            string key;
            iss >> key;
            if (key == name) {
                TVARIABLE& tvariable = tvariables[name];
                line = name + " " + tvariable.to_string();
            }
            lines.push_back(line);
        }
        in_file.close();
    }

    ofstream out_file(filename, ios::trunc);
    for (const string& l : lines) {
        out_file << l << endl;
    }
    out_file.close();
}
