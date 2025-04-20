#pragma once  

#include <string>  

using namespace std;  

// Перечисление базовых типов данных
enum BASE_TYPE {
    BOOL = 1,   // Логический тип (bool)
    FLOAT = 2,  // Вещественный тип (float)
    CHAR = 3    // Символьный тип (char)
};

// Структура для представления переменной
typedef struct TVARIABLE {
    BASE_TYPE type;         // Тип переменной (BOOL, FLOAT, CHAR)
    unsigned long index;    // Уникальный индекс переменной
    unsigned long scope;    // Область видимости переменной

    TVARIABLE() = default;  // Конструктор по умолчанию для инициализации без параметров

    // Метод для преобразования переменной в строку
    string to_string();
} TVARIABLE;

// Функция для преобразования строки в тип BASE_TYPE
BASE_TYPE type_from_string(const string& element);