#pragma once

#include <string>
#include <vector>

using namespace std;

// Шаблонный класс HASHMAP для реализации хеш-таблицы
// T - тип значения, который будет храниться в хеш-таблице
template <typename T>
class HASHMAP {
private:
    // Внутренняя структура NODE для представления элемента в хеш-таблице
    struct NODE {
        string key;   // Ключ элемента
        T value;      // Значение, связанное с ключом
        NODE* next;   // Указатель на следующий элемент в случае коллизии (цепочка)

        // Конструктор для инициализации NODE
        NODE(const string& k, const T& v) : key(k), value(v), next(nullptr) {}

        // Метод для преобразования NODE в строку (например, для отладки)
        string to_string();
    };

    vector<NODE*> buckets;       // Массив "корзин" (buckets), каждая корзина содержит цепочку элементов
    int capacity;                 // Текущая вместимость хеш-таблицы (количество корзин)
    int size;                      // Текущее количество элементов в хеш-таблице
    const double LOAD_FACTOR = 0.7; // Коэффициент загрузки для определения необходимости рехеширования

    // Приватные методы
    int hash(const string& key);   // Вычисляет хеш-значение для ключа
    void rehash();                 // Перехеширует таблицу при превышении коэффициента загрузки

public:
    // Конструктор для создания хеш-таблицы с начальной вместимостью
    HASHMAP(int initialCapacity = 16)
        : capacity(initialCapacity), size(0) {
        buckets.resize(capacity);  // Инициализируем массив корзин заданным размером
    }

    // Публичные методы
    void insert(const string& key, const T& value); // Вставка элемента в хеш-таблицу
    bool contains(const string& key);               // Проверка наличия ключа в хеш-таблице
    T& get(const string& key);                      // Получение значения по ключу (с выбросом исключения, если ключ не найден)
    T* get(const string& key, bool& found);         // Получение значения по ключу с флагом успешности
    T& operator[](const string& key);               // Оператор доступа к значению по ключу
    bool remove(const string& key);                 // Удаление элемента по ключу
    void clear();                                   // Очистка всей хеш-таблицы
    string to_string();                             // Преобразование хеш-таблицы в строку (например, для отладки)
};