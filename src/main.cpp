#include <iostream>
#include "HashTable.h"

int main() {
    HashTable<std::string, int> hashTable(10);

    hashTable.insert("apple", 1);
    hashTable.insert("banana", 2);
    hashTable.insert("orange", 3);

    std::cout << "Value for 'apple': " << hashTable.get("apple") << std::endl;
    std::cout << "Value for 'banana': " << hashTable.get("banana") << std::endl;
    std::cout << "Value for 'orange': " << hashTable.get("orange") << std::endl;

    hashTable.remove("banana");

    std::cout << "Value for 'banana' after removal: " << hashTable.get("banana") << std::endl;

    return 0;
}