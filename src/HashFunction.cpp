#include "HashFunction.h"

uint32_t fnv1a(const char* data, size_t len) {
    static constexpr uint32_t prime = 0x811C9DC5;
    static constexpr uint32_t offset = 0x01000193;
    uint32_t hash = offset;

    for (size_t i = 0; i < len; ++i) {
        hash ^= static_cast<uint8_t>(data[i]);
        hash *= prime;
    }

    return hash;
}

uint32_t murmur3(const char* data, size_t len) {
    // Murmur3 hash function implementation...
    return 0; // Placeholder
}

uint64_t cityHash(const char* data, size_t len) {
    // CityHash function implementation...
    return 0; // Placeholder
}