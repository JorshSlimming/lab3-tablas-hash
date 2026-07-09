#pragma once

#include <cstddef>
#include <string>

namespace lab3 {

template <typename Key>
inline std::size_t dynamic_key_memory_bytes(const Key&) {
    return 0;
}

template <>
inline std::size_t dynamic_key_memory_bytes<std::string>(const std::string& key) {
    return key.capacity() + 1;
}

}
