#include "HashTable.h"

template <typename Key, typename Value, typename Hash>
HashTable<Key, Value, Hash>::HashTable(size_t initialCapacity, const Hash& hasher)
    : table(initialCapacity), numEntries(0), hasher(hasher) {}

template <typename Key, typename Value, typename Hash>
HashTable<Key, Value, Hash>::~HashTable() {}

template <typename Key, typename Value, typename Hash>
bool HashTable<Key, Value, Hash>::insert(const Key& key, const Value& value) {
    std::lock_guard<std::mutex> lock(mutex);
    size_t index = hashKey(key);
    size_t startIndex = index;
    size_t probeCount = 0;

    while (table[index].occupied && table[index].entry.first != key) {
        index = (index + probeCount * probeCount) % table.size();
        probeCount++;
        if (index == startIndex) {
            return false; // Table is full
        }
    }

    if (!table[index].occupied) {
        table[index].entry = std::make_pair(key, value);
        table[index].occupied = true;
        numEntries++;
        if (numEntries > table.size() * 0.7) {
            rehash(table.size() * 2);
        }
        return true;
    } else {
        table[index].entry.second = value;
        return true;
    }
}

// Implementations for other member functions...

template <typename Key, typename Value, typename Hash>
size_t HashTable<Key, Value, Hash>::hashKey(const Key& key) const {
    return hasher(key) % table.size();
}

template <typename Key, typename Value, typename Hash>
void HashTable<Key, Value, Hash>::rehash(size_t newCapacity) {
    std::vector<HashEntry<Key, Value>> oldTable = std::move(table);
    table.resize(newCapacity);
    numEntries = 0;

    for (const auto& entry : oldTable) {
        if (entry.occupied) {
            insert(entry.entry.first, entry.entry.second);
        }
    }
}