#pragma once  

#include <iostream> 
#include <fstream>     
#include <vector>        
#include <set>          

#include "tvariable.h"  
#include "hashmap/hashmap.h"  

using namespace std;  

// ========================== STATIC TABLES ==============================
enum TABLE_TYPE {
    ALPHABET = 10,   // Таблица алфавита
    WORDS = 20,      // Таблица слов
    OPERATORS = 30,  // Таблица операторов
    SYMBOLS = 40     // Таблица символов
};

// Класс для управления статическими таблицами
class STATIC_TCONTROLLER {
public:
    // Бинарный поиск элемента в отсортированной таблице
    int binary_search(const vector<string>& table, const string& element);

    // Загрузка статической таблицы из файла
    void load_static_table(TABLE_TYPE ttype, const string& filename);

    // Поиск элемента в статической таблице без флага
    int search(TABLE_TYPE ttype, const string& element);

    // Поиск элемента в статической таблице с флагом успешности
    int search(TABLE_TYPE ttype, const string& element, bool& found);

    // Проверка наличия элемента в статической таблице
    bool contains(TABLE_TYPE ttype, const string& element);

private:
    vector<string> alphabet;   // Таблица алфавита
    vector<string> words;      // Таблица слов
    vector<string> operators;  // Таблица операторов
    vector<string> symbols;    // Таблица символов

    // Получение ссылки на таблицу по типу
    vector<string>& get_table(TABLE_TYPE type);
};

// ========================== DYNAMIC TABLES ==============================
class DYNAMIC_TCONTROLLER {
public:
    // Настройка файла для хранения динамических переменных
    void setup_file(string file_name);

    // Модификация существующей переменной
    void modify(string name, BASE_TYPE new_type, unsigned long new_scope);

    // Инициализация новой переменной
    void init(string name, BASE_TYPE type, unsigned long scope);

    // Поиск переменной по имени
    TVARIABLE& search(const string& element);

    // Поиск переменной по имени с флагом успешности
    TVARIABLE& search(const string& element, bool& found);

    // Проверка наличия переменной
    bool contains(const string& element);

    // Сохранение изменений в файл
    void save(const string& filename, const string& name);

private:
    HASHMAP<TVARIABLE> tvariables;  // Хеш-таблица для хранения динамических переменных
    fstream file;                   // Файл для хранения данных
    unsigned long last_index = 0;   // Счетчик для уникальных индексов переменных
    bool insert_mode = true;        // Флаг режима вставки
};

// ============================ CONTROLLER =================================
// Класс для объединения управления статическими и динамическими таблицами
class TCONTROLLER {
public:
    STATIC_TCONTROLLER statics;  // Управление статическими таблицами
    DYNAMIC_TCONTROLLER dynamics;  // Управление динамическими таблицами
};