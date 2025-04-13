#include "tcontroller/tcontroller.h"
#include <iostream>
#include <stdio.h>

void menu() {
    TCONTROLLER tcontroller;

    tcontroller.statics.load_static_table(TABLE_TYPE::ALPHABET, "tables/alphabet.txt");
    tcontroller.statics.load_static_table(TABLE_TYPE::WORDS, "tables/words.txt");
    tcontroller.statics.load_static_table(TABLE_TYPE::OPERATORS, "tables/operators.txt");
    tcontroller.statics.load_static_table(TABLE_TYPE::SYMBOLS, "tables/symbols.txt");
    tcontroller.dynamics.setup_file("tables/variables.txt");

    int mode = 0;
    int n;
    int index;
    string key;
    string text;

    while (true) {
        switch (mode) {
        case 0:
            cout << "Select tables to work with:\n 1. Statics\n 2. Dynamics\n> ";
            cin >> n;
            if (n == 1) mode = 1;
            else if (n == 2) mode = 2;
            else cout << "Error" << endl;
            break;
        case 1:
            cout << "Operation:\n 1. Search\n 0. Menu\n > ";
            cin >> n;
            if (n == 0) mode = 0;
            else if (n == 1) mode = 3;
            else cout << "Error" << endl;
            break;
        case 2:
            cout << "Operations:\n 1. Add\n 2. Modify\n 3. Search\n 0. Menu\n > ";
            cin >> n;
            if (n == 0) mode = 0;
            else if (n == 1) mode = 4;
            else if (n == 2) mode = 5;
            else if (n == 3) mode = 6;
            else cout << "Error\n";
            break;
        case 3:
            cout << "[hint] Table types: "
                << "ALPHABET: " << TABLE_TYPE::ALPHABET << ", "
                << "WORDS: " << TABLE_TYPE::WORDS << ", "
                << "OPERATORS: " << TABLE_TYPE::OPERATORS << ", "
                << "SYMBOLS: " << TABLE_TYPE::SYMBOLS << "." << endl;
            cout << "Table type:\n > ";
            cin >> n;
            if (n == 10 || n == 20 || n == 30 || n == 40) {
                cout << "What search:\n > ";
                cin.ignore();
                getline(cin, text);
                bool res;
                index = tcontroller.statics.search(static_cast<TABLE_TYPE>(n), text, res);
                if (res) cout << "Index: " << index;
                else cout << "Not found";
                cout << endl;
            } else cout << "Error\n";
            mode = 0;
            break;
        case 4:
            cout << "Write in one line:\n [KEY] [TYPE] [SCOPE]\nwhere:\n"
                << " [KEY] - key" << endl
                << " [TYPE] - " << BASE_TYPE::BOOL << " (bool), " << BASE_TYPE::FLOAT << " (float) or " << BASE_TYPE::CHAR << " (char)" << endl
                << " [SCOPE] - scope" << endl;
            int type, scope;
            cin >> key >> type >> scope;
            try {
                tcontroller.dynamics.init(key, static_cast<BASE_TYPE>(type), scope);
                cout << "Added" << endl;
            }
            catch (const exception& e) {
                cerr << e.what() << endl;
            }
            mode = 2;
            break;
        case 5:
            cout << "Write in one line: [KEY] [NEW_TYPE] [NEW_SCOPE]\nwhere:\n"
                << " [KEY] - key" << endl
                << " [NEW_TYPE] - " << BASE_TYPE::BOOL << " (bool), " << BASE_TYPE::FLOAT << " (float) or " << BASE_TYPE::CHAR << " (char)" << endl
                << " [NEW_SCOPE] - scope" << endl;
            int new_type, new_scope;
            cin >> key >> new_type >> new_scope;
            try {
                tcontroller.dynamics.modify(key, static_cast<BASE_TYPE>(new_type), new_scope);
            }
            catch (const exception& e) {
                cerr << e.what() << endl;
            }
            mode = 2;
            break;
        case 6:
            cout << "Enter key:\n > ";
            cin >> text;
            bool found;
            TVARIABLE& variable = tcontroller.dynamics.search(text, found);
            if (found) cout << "Found: " << text << ": " << variable.to_string();
            else cout << "Not found";
            cout << endl;
            mode = 2;
            break;
        }
    }
}

int main() {
    menu();
}
