#pragma once
#include <vector>
#include <functional>
#include <utility>
#include <mutex>
#include <iterator>
#include "HashEntry.h"
#include "HashFunction.h"

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class HashTable {
public:
    HashTable(size_t initialCapacity = 16, const Hash& hasher = Hash());
    ~HashTable();

    bool insert(const Key& key, const Value& value);
    bool remove(const Key& key);
    Value* find(const Key& key);
    void clear();

    size_t size() const;
    bool empty() const;

    class iterator;
    class const_iterator;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

private:
    std::vector<HashEntry<Key, Value>> table;
    size_t numEntries;
    Hash hasher;
    std::mutex mutex;

    size_t hashKey(const Key& key) const;
    void rehash(size_t newCapacity);
};