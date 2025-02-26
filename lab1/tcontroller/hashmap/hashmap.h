#pragma once

#include <string>
#include <vector>

using namespace std;

template <typename T>
class HASHMAP {
private:
    struct Node {
        string key;
        T value;
        Node* next;

        Node(const string& k, const T& v) : key(k), value(v), next(nullptr) {}

        string to_string();
    };

    vector<Node*> buckets;
    size_t capacity;
    size_t size;
    const double LOAD_FACTOR = 0.7;

    size_t hash(const string& key);
    void rehash();
public:
    HASHMAP(size_t initialCapacity = 16)
        : capacity(initialCapacity), size(0) {
        buckets.resize(capacity);
    }

    void insert(const string& key, const T& value);
    bool contains(const string& key);
    T& get(const string& key);
    T& get(const string& key, bool& found);
    T& operator[](const string& key);
    bool remove(const string& key);
    void clear();
    string to_string();

    size_t getSize() const { return size; }
    size_t getCapacity() const { return capacity; }
};
