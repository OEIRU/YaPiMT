#include <sstream>

#include "tcontroller.h"

using namespace std;

// Преобразование строки в тип BASE_TYPE
BASE_TYPE type_from_string(const string& element) {
    if (element == "bool") return BOOL;   // Если строка "bool", возвращаем соответствующий тип
    if (element == "float") return FLOAT; // Если строка "float", возвращаем соответствующий тип
    if (element == "char") return CHAR;   // Если строка "char", возвращаем соответствующий тип
}

// Преобразование типа BASE_TYPE в строку
string type_to_string(BASE_TYPE type) {
    switch (type) {                      // Определяем тип и возвращаем соответствующую строку
        case BOOL: return "bool";        // Для BOOL возвращаем "bool"
        case FLOAT: return "float";      // Для FLOAT возвращаем "float"
        case CHAR: return "char";        // Для CHAR возвращаем "char"
    }
}

// Преобразование объекта TVARIABLE в строку
string TVARIABLE::to_string() {
    stringstream res;  // Создаем поток строк для формирования результата
    res << type_to_string(type) << " "      // Добавляем тип переменной
        // << index                 << " "  // Индекс закомментирован (не используется)
        << scope;                           // Добавляем область видимости
    return res.str();                       // Возвращаем сформированную строку
}