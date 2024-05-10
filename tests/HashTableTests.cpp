#include "../src/HashTable.h"
#include <string>
#include <iostream>
#include <cassert>
#include <thread>
#include <vector>

void testInsertAndFind() {
    HashTable<std::string, int> table;

    assert(table.insert("apple", 10));
    assert(table.insert("banana", 20));
    assert(table.insert("orange", 30));

    int* value = table.find("banana");
    assert(value != nullptr && *value == 20);

    value = table.find("grape");
    assert(value == nullptr);
}

void testRemove() {
    HashTable<std::string, int> table;

    table.insert("apple", 10);
    table.insert("banana", 20);
    table.insert("orange", 30);

    assert(table.remove("banana"));
    assert(table.find("banana") == nullptr);
    assert(!table.remove("grape"));
}

void testClear() {
    HashTable<std::string, int> table;

    table.insert("apple", 10);
    table.insert("banana", 20);
    table.insert("orange", 30);

    table.clear();
    assert(table.empty());
}

void testIterators() {
    HashTable<std::string, int> table;

    table.insert("apple", 10);
    table.insert("banana", 20);
    table.insert("orange", 30);

    std::vector<std::pair<std::string, int>> entries;
    for (const auto& entry : table) {
        entries.push_back(entry);
    }

    assert(entries.size() == 3);
    assert(std::find(entries.begin(), entries.end(), std::make_pair("apple", 10)) != entries.end());
    assert(std::find(entries.begin(), entries.end(), std::make_pair("banana", 20)) != entries.end());
    assert(std::find(entries.begin(), entries.end(), std::make_pair("orange", 30)) != entries.end());
}

void testThreadSafety() {
    HashTable<int, int> table;

    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&table, i]() {
            for (int j = 0; j < 1000; ++j) {
                table.insert(i * 1000 + j, i * 1000 + j);
            }
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    assert(table.size() == 10000);
}

int main() {
    testInsertAndFind();
    testRemove();
    testClear();
    testIterators();
    testThreadSafety();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}