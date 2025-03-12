#include <sstream>
#include <exception>

#include "hashmap.h"
#include "../tvariable.h"

using namespace std;

template class HASHMAP<TVARIABLE>;

template <typename T>
size_t HASHMAP<T>::hash(const std::string& key) {
    return std::hash<std::string>{}(key) % capacity;
}

template <typename T>
void HASHMAP<T>::rehash() {
    size_t new_capacity = capacity * 2;
    vector<NODE*> new_buckets(new_capacity, nullptr);

    for (int i = 0; i < capacity; ++i) {
        NODE* node = buckets[i];
        while (node != nullptr) {
            NODE* next = node->next;
            int new_index = hash(node->key) % new_capacity;

            node->next = new_buckets[new_index];
            new_buckets[new_index] = node;

            node = next;
        }
    }

    buckets = move(new_buckets);
    capacity = new_capacity;
}

template <typename T>
void HASHMAP<T>::insert(const string& key, const T& value) {
    if (static_cast<double>(size) / capacity >= LOAD_FACTOR) {
        rehash();
    }

    size_t index = hash(key);
    NODE* current = buckets[index];

    while (current != nullptr) {
        if (current->key == key) {
            current->value = value;
            return;
        }
        current = current->next;
    }

    NODE* new_node = new NODE(key, value);
    new_node->next = buckets[index];
    buckets[index] = new_node;
    ++size;
}

template <typename T>
bool HASHMAP<T>::contains(const string& key) {
    bool found = false;
    get(key, found);
    return found;
}

template <typename T>
T& HASHMAP<T>::get(const string& key, bool& found) {
    T empty_res;
    size_t index = hash(key);
    NODE* current = buckets[index];

    while (current != nullptr) {
        if (current->key == key) {
            found = true;
            return current->value;
        }
        current = current->next;
    }
    found = false;
    return empty_res;
}

template <typename T>
T& HASHMAP<T>::get(const string& key) {
    bool found;
    T& res = get(key, found);
    if (!found) 
        throw runtime_error("Variable \"" + key + "\" is not declared");
    return res;
}

template <typename T>
T& HASHMAP<T>::operator[](const string& key) {
    return get(key);
}

template <typename T>
bool HASHMAP<T>::remove(const string& key) {
    size_t index = hash(key);
    NODE* current = buckets[index];
    NODE* prev = nullptr;

    while (current != nullptr) {
        if (current->key == key) {
            if (prev) {
                prev->next = current->next;
            } else {
                buckets[index] = current->next;
            }
            delete current;
            --size;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

template <typename T>
void HASHMAP<T>::clear() {
    for (size_t i = 0; i < capacity; ++i) {
        NODE* current = buckets[i];
        while (current != nullptr) {
            NODE* next = current->next;
            delete current;
            current = next;
        }
        buckets[i] = nullptr;
    }
    size = 0;
}

template <typename T>
string HASHMAP<T>::to_string() {
    stringstream res;
    for (size_t i = 0; i < capacity; ++i) {
        NODE* current = buckets[i];
        while (current != nullptr) {
            NODE* next = current->next;
            res << current->to_string() << endl;
            current = next;
        }
        buckets[i] = nullptr;
    }
    return res.str();
}

template <typename T>
string HASHMAP<T>::NODE::to_string() {
    stringstream res;
    res << key                  << " "
        << value.to_string();
    return res.str();
}
