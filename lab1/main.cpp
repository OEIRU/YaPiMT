#include "tcontroller/tcontroller.h"
#include <iostream>
#include <stdio.h>

void menu() {
    // Создаем объект контроллера, который управляет статическими и динамическими таблицами
    TCONTROLLER tcontroller;

    // Загружаем статические таблицы из файлов
    tcontroller.statics.load_static_table(TABLE_TYPE::ALPHABET, "tables/alphabet.txt");   // Таблица алфавита
    tcontroller.statics.load_static_table(TABLE_TYPE::WORDS, "tables/words.txt");         // Таблица слов
    tcontroller.statics.load_static_table(TABLE_TYPE::OPERATORS, "tables/operators.txt"); // Таблица операторов
    tcontroller.statics.load_static_table(TABLE_TYPE::SYMBOLS, "tables/symbols.txt");     // Таблица символов

    // Настраиваем файл для динамической таблицы переменных
    tcontroller.dynamics.setup_file("tables/variables.txt");
    int mode = 0;  // Переменная для управления текущим режимом меню
    int n;         // Временная переменная для выбора опций
    int index;     // Для хранения индекса найденного элемента
    string key;    // Для хранения ключа
    string text;   // Для хранения текстовых данных

    while (true) {  // Бесконечный цикл для отображения меню и обработки команд
        switch (mode) {
        case 0:     // Главное меню: выбор между статическими и динамическими таблицами
            cout << "Select tables to work with:\n 1. Statics\n 2. Dynamics\n> ";
            cin >> n;
            if (n == 1) mode = 1;          // Переход в режим работы со статическими таблицами
            else if (n == 2) mode = 2;     // Переход в режим работы с динамическими таблицами
            else cout << "Error" << endl;
            break;

        case 1:     // Меню работы со статическими таблицами
            cout << "Operation:\n 1. Search\n 0. Menu\n > ";
            cin >> n;
            if (n == 0) mode = 0;          // Возврат в главное меню
            else if (n == 1) mode = 3;     // Переход в режим поиска в статических таблицах
            else cout << "Error" << endl; 
            break;

        case 2:     // Меню работы с динамическими таблицами
            cout << "Operations:\n 1. Add\n 2. Modify\n 3. Search\n 0. Menu\n > ";
            cin >> n;
            if (n == 0) mode = 0;          // Возврат в главное меню
            else if (n == 1) mode = 4;     // Переход в режим добавления переменной
            else if (n == 2) mode = 5;     // Переход в режим модификации переменной
            else if (n == 3) mode = 6;     // Переход в режим поиска переменной
            else cout << "Error\n";
            break;

        case 3:     // Поиск в статических таблицах
            cout << "[hint] Table types: "
                << "ALPHABET: " << TABLE_TYPE::ALPHABET << ", "
                << "WORDS: " << TABLE_TYPE::WORDS << ", "
                << "OPERATORS: " << TABLE_TYPE::OPERATORS << ", "
                << "SYMBOLS: " << TABLE_TYPE::SYMBOLS << "." << endl;
            cout << "Table type:\n > ";
            cin >> n;
            if (n == 10 || n == 20 || n == 30 || n == 40) { 
                                           // Проверка на корректный тип таблицы
                cout << "What search:\n > ";
                cin.ignore();              // Игнорируем остаток строки после предыдущего ввода
                getline(cin, text);        // Считываем строку для поиска
                bool res;                  // Переменная для хранения результата поиска
                index = tcontroller.statics.search(static_cast<TABLE_TYPE>(n), text, res);  
                                           // Выполняем поиск
                if (res) cout << "Index: " << index;  // Если найдено, выводим индекс
                else cout << "Not found";  // Если не найдено, выводим сообщение
                cout << endl;
            } else cout << "Error\n";      // Ошибка при неверном типе таблицы
            mode = 0;                      // Возврат в главное меню
            break;

        case 4:     // Добавление новой переменной в динамическую таблицу
            cout << "Write in one line:\n [KEY] [TYPE] [SCOPE]\nwhere:\n"
                << " [KEY] - key" << endl
                << " [TYPE] - " << BASE_TYPE::BOOL 
                << " (bool), " << BASE_TYPE::FLOAT 
                << " (float) or " << BASE_TYPE::CHAR 
                << " (char)" << endl
                << " [SCOPE] - scope" << endl;
            int type, scope;               // Переменные для хранения типа и области видимости
            cin >> key >> type >> scope;   // Считываем ключ, тип и область видимости
            try {
                                           // Добавляем переменную
                tcontroller.dynamics.init(key, static_cast<BASE_TYPE>(type), scope);             
                cout << "Added" << endl;   // Успешное добавление
            }
            catch (const exception& e) {
                cerr << e.what() << endl;  // Обработка ошибок при добавлении
            }
            mode = 2;                      // Возврат в меню работы с динамическими таблицами
            break;

        case 5:     // Модификация существующей переменной в динамической таблице
            cout << "Write in one line: [KEY] [NEW_TYPE] [NEW_SCOPE]\nwhere:\n"
                << " [KEY] - key" << endl
                << " [NEW_TYPE] - " << BASE_TYPE::BOOL 
                << " (bool), " << BASE_TYPE::FLOAT 
                << " (float) or " << BASE_TYPE::CHAR 
                << " (char)" << endl
                << " [NEW_SCOPE] - scope" << endl;
            int new_type, new_scope;       // Переменные для хранения нового типа и области видимости
            cin >> key >> new_type >> new_scope;  // Считываем ключ, новый тип и новую область видимости
            try {
                                           // Модифицируем переменную         
                tcontroller.dynamics.modify(key, static_cast<BASE_TYPE>(new_type), new_scope); 
            }
            catch (const exception& e) {
                cerr << e.what() << endl;  // Обработка ошибок при модификации
            }
            mode = 2;                      // Возврат в меню работы с динамическими таблицами
            break;

        case 6:     // Поиск переменной в динамической таблице
            cout << "Enter key:\n > ";
            cin >> text;                   // Считываем ключ для поиска
            bool found;                    // Переменная для хранения результата поиска
                                           // Выполняем поиск
            TVARIABLE& variable = tcontroller.dynamics.search(text, found);
                                           // Если найдено, выводим информацию
            if (found) cout << "Found: " << text << ": " << variable.to_string();
            else cout << "Not found";      // Если не найдено, выводим сообщение
            cout << endl;
            mode = 2;                      // Возврат в меню работы с динамическими таблицами
            break;
        }
    }
}

int main() {
    menu();     // Запуск меню
}