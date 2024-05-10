#ifndef HASH_ENTRY_H
#define HASH_ENTRY_H

template <typename K, typename V>
struct HashEntry {
    K key;
    V value;
    HashEntry* next;

    HashEntry(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
};

#endif