#pragma once
#include <cstdint>

// FNV-1a hash function
uint32_t fnv1a(const char* data, size_t len);

// Murmur3 hash function
uint32_t murmur3(const char* data, size_t len);

// CityHash function
uint64_t cityHash(const char* data, size_t len);