#include <fstream>         
#include <algorithm>       
#include <iostream>        
#include <filesystem>    

#include "tcontroller.h" 

// Бинарный поиск элемента в отсортированной таблице
int STATIC_TCONTROLLER::binary_search(const std::vector<std::string>& table, const std::string& element) {
    int low = 0;                          // Нижняя граница поиска
    int high = table.size() - 1;          // Верхняя граница поиска

    while (low <= high) {                 // Пока диапазон поиска не пуст
        int mid = low + (high - low) / 2; // Вычисляем середину диапазона
        if (table[mid] == element)        // Если элемент найден
            return mid;                   // Возвращаем его индекс
        else if (table[mid] < element)    // А если элемент больше среднего
            low = mid + 1;                // Сужаем диапазон до правой части
        else                              // И если элемент меньше среднего
            high = mid - 1;               // Сужаем диапазон до левой части
    }
    return -1;
}

// Загрузка статической таблицы из файла
void STATIC_TCONTROLLER::load_static_table(TABLE_TYPE ttype, const string& filename) {
    ifstream file(filename);               // Открываем файл для чтения
    vector<string>& table = get_table(ttype); // Получаем ссылку на соответствующую таблицу
    string line;
    while (getline(file, line)) {             // Читаем файл построчно
        table.push_back(line);          // Добавляем строки в таблицу
    }
    file.close();                            // Закрываем файл после чтения
}

// Поиск элемента в статической таблице без флага
int STATIC_TCONTROLLER::search(TABLE_TYPE ttype, const string& element) {
    vector<string>& table = get_table(ttype); // Получаем ссылку на соответствующую таблицу
    return binary_search(table, element);     // Используем бинарный поиск для поиска элемента
}

// Поиск элемента в статической таблице с флагом успешности
int STATIC_TCONTROLLER::search(TABLE_TYPE ttype, const string& element, bool& found) {
    vector<string>& table = get_table(ttype); // Получаем ссылку на соответствующую таблицу
    int distance = search(ttype, element);    // Ищем элемент
    found = distance != -1;                   // Устанавливаем флаг успешности
    return distance;                          // Возвращаем результат поиска
}

// Получение ссылки на таблицу по типу
vector<string>& STATIC_TCONTROLLER::get_table(TABLE_TYPE ttype) {
    switch (ttype) {                        // Определяем тип таблицы
        case TABLE_TYPE::ALPHABET: return alphabet;   // Возвращаем таблицу алфавита
        case TABLE_TYPE::WORDS: return words;         // Возвращаем таблицу слов
        case TABLE_TYPE::OPERATORS: return operators; // Возвращаем таблицу операторов
        case TABLE_TYPE::SYMBOLS: return symbols;     // Возвращаем таблицу символов
    }

    throw runtime_error("Unknown table");  // Если тип таблицы неизвестен, выбрасываем исключение
}