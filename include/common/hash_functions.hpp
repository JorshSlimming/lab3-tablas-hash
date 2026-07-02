#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

#include "common/dataset_types.hpp"

namespace lab3 {

inline std::uint64_t splitmix64(std::uint64_t value) {
    value += 0x9e3779b97f4a7c15ULL;
    value = (value ^ (value >> 30)) * 0xbf58476d1ce4e5b9ULL;
    value = (value ^ (value >> 27)) * 0x94d049bb133111ebULL;
    return value ^ (value >> 31);
}

inline std::uint64_t fnv1a64(const std::string& text) {
    std::uint64_t hash = 14695981039346656037ULL;
    for (unsigned char character : text) {
        hash ^= character;
        hash *= 1099511628211ULL;
    }
    return hash;
}

template <typename Key>
struct PrimaryHash;

template <>
struct PrimaryHash<UserId> {
    std::size_t operator()(UserId key) const {
        return static_cast<std::size_t>(splitmix64(key));
    }
};

template <>
struct PrimaryHash<UserScreenName> {
    std::size_t operator()(const UserScreenName& key) const {
        return static_cast<std::size_t>(fnv1a64(key));
    }
};

template <typename Key>
struct SecondaryHash;

template <>
struct SecondaryHash<UserId> {
    std::size_t operator()(UserId key) const {
        return static_cast<std::size_t>(splitmix64(key ^ 0xd6e8feb86659fd93ULL));
    }
};

template <>
struct SecondaryHash<UserScreenName> {
    std::size_t operator()(const UserScreenName& key) const {
        std::uint64_t hash = 1099511628211ULL;
        for (unsigned char character : key) {
            hash ^= static_cast<unsigned char>(character + 31U);
            hash *= 14695981039346656037ULL;
        }
        return static_cast<std::size_t>(hash);
    }
};

template <typename Key>
inline std::size_t double_hash_step(const Key& key, std::size_t capacity) {
    if (capacity <= 2) {
        return 1;
    }
    return 1 + (SecondaryHash<Key>{}(key) % (capacity - 1));
}

}  // namespace lab3
