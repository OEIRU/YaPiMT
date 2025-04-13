#pragma once

#include <string>
#include <vector>

using namespace std;

template <typename T>
class HASHMAP {
private:
    struct NODE {
        string key;
        T value;
        NODE* next;

        NODE(const string& k, const T& v) : key(k), value(v), next(nullptr) {}

        string to_string();
    };

    vector<NODE*> buckets;
    int capacity;
    int size;
    const double LOAD_FACTOR = 0.7;

    int hash(const string& key);
    void rehash();
public:
    HASHMAP(int initialCapacity = 16)
        : capacity(initialCapacity), size(0) {
        buckets.resize(capacity);
    }

    void insert(const string& key, const T& value);
    bool contains(const string& key);
    T& get(const string& key);
    T* get(const string& key, bool& found);
    T& operator[](const string& key);
    bool remove(const string& key);
    void clear();
    string to_string();
};

