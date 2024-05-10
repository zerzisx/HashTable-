# HashTable-

This is a thread-safe implementation of a hash table data structure in C++. The hash table uses open addressing with quadratic probing for collision resolution. It supports concurrent insertions, lookups, and removals using a mutex for thread safety.

## Features

- **Thread-Safe**: The hash table is designed to be safe for concurrent access from multiple threads.
- **Open Addressing with Quadratic Probing**: Collisions are resolved using open addressing with quadratic probing.
- **Automatic Rehashing**: The hash table automatically resizes and rehashes when the load factor exceeds a certain threshold (0.7 in this implementation).
- **Separate Chaining**: The hash table uses separate chaining to handle collisions, allowing multiple key-value pairs to be stored at the same index.

## Files

1. `HashTable.h`: This header file contains the declaration of the `HashTable` class template.
2. `HashTable.cpp`: This file contains the implementation of the `HashTable` class template.
3. `HashFunction.h`: This header file declares various hash functions, including FNV-1a, Murmur3, and CityHash.
4. `HashFunction.cpp`: This file contains the implementations of the hash functions declared in `HashFunction.h`.
5. `HashEntry.h`: This header file defines the `HashEntry` struct, which represents a key-value pair in the hash table's separate chaining implementation.
6. `main.cpp`: This file contains a set of test cases to verify the correctness of the hash table implementation.

## Code

```cpp
// HashTable.h
#pragma once
#include <vector>
#include <utility>
#include <mutex>
#include "HashEntry.h"
#include "HashFunction.h"

template <typename Key, typename Value, typename Hash = fnv1a>
class HashTable {
public:
    HashTable(size_t initialCapacity = 16, const Hash& hasher = Hash());
    ~HashTable();

    bool insert(const Key& key, const Value& value);
    Value* find(const Key& key);
    bool remove(const Key& key);
    void clear();
    bool empty() const;
    size_t size() const;

    typename std::vector<std::pair<Key, Value>>::iterator begin();
    typename std::vector<std::pair<Key, Value>>::iterator end();

private:
    struct HashEntry {
        std::pair<Key, Value> entry;
        bool occupied;

        HashEntry() : occupied(false) {}
    };

    std::vector<HashEntry> table;
    size_t numEntries;
    Hash hasher;
    std::mutex mutex;

    size_t hashKey(const Key& key) const;
    void rehash(size_t newCapacity);
};

// HashTable.cpp
// Implementation omitted for brevity

// HashFunction.h
#pragma once
#include <cstdint>

uint32_t fnv1a(const char* data, size_t len);
uint32_t murmur3(const char* data, size_t len);
uint64_t cityHash(const char* data, size_t len);

// HashFunction.cpp
// Implementation omitted for brevity

// HashEntry.h
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

// main.cpp
#include "../src/HashTable.h"
#include <string>
#include <iostream>
#include <cassert>
#include <thread>
#include <vector>

// Test cases omitted for brevity

Usage
To use the hash table, include the HashTable.h header file in your C++ source file:
#include "HashTable.h"

avatar
UX Designer Assistant

Here's the complete README with all the code you provided:

MARKDOWN
# Hash Table Implementation

This is a thread-safe implementation of a hash table data structure in C++. The hash table uses open addressing with quadratic probing for collision resolution. It supports concurrent insertions, lookups, and removals using a mutex for thread safety.

## Features

- **Thread-Safe**: The hash table is designed to be safe for concurrent access from multiple threads.
- **Open Addressing with Quadratic Probing**: Collisions are resolved using open addressing with quadratic probing.
- **Automatic Rehashing**: The hash table automatically resizes and rehashes when the load factor exceeds a certain threshold (0.7 in this implementation).
- **Separate Chaining**: The hash table uses separate chaining to handle collisions, allowing multiple key-value pairs to be stored at the same index.

## Files

1. `HashTable.h`: This header file contains the declaration of the `HashTable` class template.
2. `HashTable.cpp`: This file contains the implementation of the `HashTable` class template.
3. `HashFunction.h`: This header file declares various hash functions, including FNV-1a, Murmur3, and CityHash.
4. `HashFunction.cpp`: This file contains the implementations of the hash functions declared in `HashFunction.h`.
5. `HashEntry.h`: This header file defines the `HashEntry` struct, which represents a key-value pair in the hash table's separate chaining implementation.
6. `main.cpp`: This file contains a set of test cases to verify the correctness of the hash table implementation.

## Code

```cpp
// HashTable.h
#pragma once
#include <vector>
#include <utility>
#include <mutex>
#include "HashEntry.h"
#include "HashFunction.h"

template <typename Key, typename Value, typename Hash = fnv1a>
class HashTable {
public:
    HashTable(size_t initialCapacity = 16, const Hash& hasher = Hash());
    ~HashTable();

    bool insert(const Key& key, const Value& value);
    Value* find(const Key& key);
    bool remove(const Key& key);
    void clear();
    bool empty() const;
    size_t size() const;

    typename std::vector<std::pair<Key, Value>>::iterator begin();
    typename std::vector<std::pair<Key, Value>>::iterator end();

private:
    struct HashEntry {
        std::pair<Key, Value> entry;
        bool occupied;

        HashEntry() : occupied(false) {}
    };

    std::vector<HashEntry> table;
    size_t numEntries;
    Hash hasher;
    std::mutex mutex;

    size_t hashKey(const Key& key) const;
    void rehash(size_t newCapacity);
};

// HashTable.cpp
// Implementation omitted for brevity

// HashFunction.h
#pragma once
#include <cstdint>

uint32_t fnv1a(const char* data, size_t len);
uint32_t murmur3(const char* data, size_t len);
uint64_t cityHash(const char* data, size_t len);

// HashFunction.cpp
// Implementation omitted for brevity

// HashEntry.h
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

// main.cpp
#include "../src/HashTable.h"
#include <string>
#include <iostream>
#include <cassert>
#include <thread>
#include <vector>

// Test cases omitted for brevity
Usage
To use the hash table, include the HashTable.h header file in your C++ source file:

CPP
#include "HashTable.h"
Then, you can create an instance of the HashTable class template by specifying the key and value types, as well as the hash function to be used:
HashTable<std::string, int, fnv1a> myTable;

Here, fnv1a is the hash function used for hashing string keys. You can choose from the available hash functions (fnv1a, murmur3, and cityHash) or provide your own custom hash function.

The HashTable class provides the following member functions:

insert(const Key& key, const Value& value): Inserts a key-value pair into the hash table.
find(const Key& key): Finds the value associated with the given key in the hash table.
remove(const Key& key): Removes the key-value pair associated with the given key from the hash table.
clear(): Removes all key-value pairs from the hash table.
empty(): Returns true if the hash table is empty, false otherwise.
size(): Returns the number of key-value pairs in the hash table.
You can also iterate over the key-value pairs in the hash table using a range-based for loop: for (const auto& entry : myTable) {
    std::cout << "Key: " << entry.first << ", Value: " << entry.second << std::endl;
}

Testing
The main.cpp file contains a set of test cases to verify the correctness of the hash table implementation. You can compile and run the tests using your preferred C++ compiler and build system.

Contributing
Contributions to this project are welcome. If you find any issues or have suggestions for improvements, please open an issue or submit a pull request on the project's GitHub repository.

License
This project is licensed under the MIT License.
