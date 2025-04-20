#include <sstream>
#include <exception>

#include "hashmap.h" 
#include "../tvariable.h" 

using namespace std;

// Явное инстанцирование шаблона для типа TVARIABLE
template class HASHMAP<TVARIABLE>;

// Реализация метода hash: вычисляет хеш-значение для ключа
template <typename T>
int HASHMAP<T>::hash(const std::string& key) {
    return std::hash<std::string>{}(key) % capacity;  // Вычисляем хеш и нормализуем его по размеру таблицы
}

// Реализация метода rehash: увеличивает размер таблицы и перераспределяет элементы
template <typename T>
void HASHMAP<T>::rehash() {
    int new_capacity = capacity * 2;                  // Увеличиваем вместимость в два раза
    vector<NODE*> new_buckets(new_capacity, nullptr); // Создаем новый массив корзин

    // Перераспределяем элементы из старого массива в новый
    for (int i = 0; i < capacity; ++i) {
        NODE* node = buckets[i];      // Текущий узел в корзине
        while (node != nullptr) {     // Проходим по цепочке узлов
            NODE* next = node->next;  // Сохраняем ссылку на следующий узел
                                      // Вычисляем новую позицию
            int new_index = hash(node->key) % new_capacity;  

            // Вставляем узел в начало новой цепочки
            node->next = new_buckets[new_index];  
            new_buckets[new_index] = node;

            node = next;              // Переходим к следующему узлу
        }
    }

    buckets = move(new_buckets);      // Заменяем старый массив новым
    capacity = new_capacity;          // Обновляем вместимость
}

// Реализация метода insert: вставляет новую пару "ключ-значение" в таблицу
template <typename T>
void HASHMAP<T>::insert(const string& key, const T& value) {
    if (static_cast<double>(size) / capacity >= LOAD_FACTOR) {  // Проверяем коэффициент загрузки
        rehash();                     // Если превышен, выполняем рехеширование
    }

    int index = hash(key);            // Вычисляем индекс корзины
    NODE* current = buckets[index];   // Текущий узел в корзине

    // Проверяем, существует ли уже ключ
    while (current != nullptr) {
        if (current->key == key) {    // Если ключ найден, обновляем значение
            current->value = value;
            return;
        }
        current = current->next;      // Переходим к следующему узлу
    }

    // Если ключ не найден, создаем новый узел
    NODE* new_node = new NODE(key, value);
    new_node->next = buckets[index];  // Вставляем новый узел в начало цепочки
    buckets[index] = new_node;
    ++size;                           // Увеличиваем счетчик элементов
}

// Реализация метода contains: проверяет наличие ключа в таблице
template <typename T>
bool HASHMAP<T>::contains(const string& key) {
    bool found = false;               // Флаг успешности поиска
    get(key, found);                  // Используем метод get для поиска ключа
    return found;                     // Возвращаем результат
}

// Реализация метода get с флагом: возвращает указатель на значение или nullptr
template <typename T>
T* HASHMAP<T>::get(const string& key, bool& found) {
    int index = hash(key);            // Вычисляем индекс корзины
    NODE* current = buckets[index];   // Текущий узел в корзине

    // Проходим по цепочке узлов
    while (current != nullptr) {
        if (current->key == key) {    // Если ключ найден
            found = true;             // Устанавливаем флаг
            return &current->value;   // Возвращаем указатель на значение
        }
        current = current->next;      // Переходим к следующему узлу
    }

    found = false;   // Если ключ не найден, сбрасываем флаг
    return nullptr;  // Возвращаем nullptr
}

// Реализация метода get: возвращает значение или выбрасывает исключение
template <typename T>
T& HASHMAP<T>::get(const string& key) {
    bool found;                       // Флаг успешности поиска
    T* res = get(key, found);         // Ищем значение по ключу
    if (!found)                       // Если ключ не найден
        throw runtime_error("Variable \"" + key + "\" is not declared");  // Выбрасываем исключение
    return *res;                      // Возвращаем найденное значение
}

// Реализация оператора []: предоставляет доступ к значению по ключу
template <typename T>
T& HASHMAP<T>::operator[](const string& key) {
    return get(key);                  // Используем метод get для поиска значения
}

// Реализация метода remove: удаляет элемент по ключу
template <typename T>
bool HASHMAP<T>::remove(const string& key) {
    int index = hash(key);            // Вычисляем индекс корзины
    NODE* current = buckets[index];   // Текущий узел в корзине
    NODE* prev = nullptr;             // Предыдущий узел

    // Проходим по цепочке узлов
    while (current != nullptr) {
        if (current->key == key) {    // Если ключ найден
            if (prev) {               // Если есть предыдущий узел
                prev->next = current->next;  // Исключаем текущий узел из цепочки
            } else {                // Если текущий узел является первым в корзине
                buckets[index] = current->next;  // Обновляем начало цепочки
            }
            delete current;           // Освобождаем память
            --size;                   // Уменьшаем счетчик элементов
            return true;              // Возвращаем успех
        }
        prev = current;  // Переходим к следующему узлу
        current = current->next;
    }

    return false;  // Если ключ не найден, возвращаем false
}

// Реализация метода clear: очищает всю таблицу
template <typename T>
void HASHMAP<T>::clear() {
    for (int i = 0; i < capacity; ++i) {  // Проходим по всем корзинам
        NODE* current = buckets[i];       // Текущий узел в корзине
        while (current != nullptr) {      // Проходим по цепочке узлов
            NODE* next = current->next;   // Сохраняем ссылку на следующий узел
            delete current;               // Освобождаем память
            current = next;               // Переходим к следующему узлу
        }
        buckets[i] = nullptr;  // Обнуляем корзину
    }
    size = 0;  // Сбрасываем счетчик элементов
}

// Реализация метода to_string: преобразует содержимое таблицы в строку
template <typename T>
string HASHMAP<T>::to_string() {
    stringstream res;                     // Поток для формирования строки
    for (int i = 0; i < capacity; ++i) {  // Проходим по всем корзинам
        NODE* current = buckets[i];       // Текущий узел в корзине
        while (current != nullptr) {      // Проходим по цепочке узлов
            NODE* next = current->next;   // Сохраняем ссылку на следующий узел
            res << current->to_string() << endl;  // Добавляем строковое представление узла
            current = next;               // Переходим к следующему узлу
        }
    }
    return res.str();  // Возвращаем сформированную строку
}

// Реализация метода to_string для структуры NODE: преобразует узел в строку
template <typename T>
string HASHMAP<T>::NODE::to_string() {
    stringstream res;  // Поток для формирования строки
    res << key << " "  // Добавляем ключ
        << value.to_string();  // Добавляем строковое представление значения
    return res.str();  // Возвращаем сформированную строку
}