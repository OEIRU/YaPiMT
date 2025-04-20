#include <fstream>         
#include <algorithm>       
#include <iostream>       
#include <filesystem>    

#include "tcontroller.h"  
#include "exceptions/exceptions.h" 

// Настройка файла для хранения динамических переменных
void DYNAMIC_TCONTROLLER::setup_file(string file_name) {
    if (insert_mode == false) return;  // Если режим вставки выключен, завершаем выполнение

    file.open(file_name);              // Открываем файл для чтения
    while (file.peek() != EOF) {       // Читаем файл до конца
        string key, type;
        int scope;

        file >> key >> type >> scope;  // Считываем ключ, тип и область видимости
        if (key != "")                 // Если ключ не пустой
            init(key, type_from_string(type), scope);  // Инициализируем переменную
    }
    file.clear();                      // Очищаем флаги файла

    insert_mode = false;               // Выключаем режим вставки после загрузки
}

// Модификация существующей переменной
void DYNAMIC_TCONTROLLER::modify(string name, BASE_TYPE new_type, unsigned long new_scope) {
    if (!contains(name)) {    // Если переменная не существует
        throw variable_exception("Variable '" + name + "' not found");  // Выбрасываем исключение
    }

    TVARIABLE& tvariable = tvariables[name];  // Получаем ссылку на переменную

    tvariable.type = new_type;   // Обновляем тип
    tvariable.scope = new_scope; // Обновляем область видимости

    save("tables/variables.txt", name);  // Сохраняем изменения в файл
}

// Инициализация новой переменной
void DYNAMIC_TCONTROLLER::init(string name, BASE_TYPE type, unsigned long scope) {
    if (contains(name)) {  // Если переменная уже существует
        throw variable_exception("cannot redeclare variable");  // Выбрасываем исключение
    }

    TVARIABLE tvariable;  // Создаем новую переменную
    tvariable.index = last_index++;  // Присваиваем уникальный индекс
    tvariable.scope = scope;         // Устанавливаем область видимости
    tvariable.type = type;           // Устанавливаем тип

    tvariables.insert(name, tvariable);  // Вставляем переменную в хеш-таблицу

    last_index += 1;  // Увеличиваем счетчик индексов

    if (!insert_mode) {  // Если режим вставки выключен
        file << name << " " << tvariable.to_string() << endl;  // Записываем переменную в файл
        file.flush();  // Сбрасываем буфер в файл
    }
}

// Проверка наличия переменной
bool DYNAMIC_TCONTROLLER::contains(const string& element) {
    return tvariables.contains(element);  // Проверяем наличие ключа в хеш-таблице
}

// Поиск переменной по имени
TVARIABLE& DYNAMIC_TCONTROLLER::search(const string& element) {
    return tvariables[element];  // Возвращаем переменную по ключу (выбрасывает исключение, если ключа нет)
}

// Поиск переменной по имени с флагом успешности
TVARIABLE& DYNAMIC_TCONTROLLER::search(const string& element, bool& found) {
    return *tvariables.get(element, found);  // Используем метод get для поиска с флагом
}

// Сохранение изменений в файл
void DYNAMIC_TCONTROLLER::save(const string& filename, const string& name) {
    if (insert_mode) return;  // Если режим вставки включен, пропускаем сохранение

    vector<string> lines;  // Вектор для хранения строк файла
    string line;

    ifstream in_file(filename);  // Открываем файл для чтения
    if (in_file.is_open()) {     // Если файл успешно открыт
        while (getline(in_file, line)) {  // Читаем файл построчно
            istringstream iss(line);      // Разбираем строку
            string key;
            iss >> key;                   // Извлекаем ключ
            if (key == name) {            // Если ключ совпадает с именем переменной
                TVARIABLE& tvariable = tvariables[name];    // Получаем переменную
                line = name + " " + tvariable.to_string();  // Формируем новую строку
            }
            lines.push_back(line);  // Добавляем строку в вектор
        }
        in_file.close();  // Закрываем файл
    }

    ofstream out_file(filename, ios::trunc);  // Открываем файл для записи (очищаем содержимое)
    for (const string& l : lines) {           // Записываем строки обратно в файл
        out_file << l << endl;
    }
    out_file.close();  // Закрываем файл
}