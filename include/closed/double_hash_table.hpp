#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

#include "common/dataset_types.hpp"
#include "common/experiment_config.hpp"
#include "common/hash_functions.hpp"
#include "common/memory_utils.hpp"
#include "common/prime_utils.hpp"

namespace lab3 {

template <typename Key, typename Hash = PrimaryHash<Key>>
class DoubleHashTable {
public:
    explicit DoubleHashTable(
        std::size_t initial_capacity = config::kInitialCapacity,
        double max_load_factor = config::kMaxLoadFactor)
        : slots_(next_prime(initial_capacity)),
          max_load_factor_(max_load_factor) {
        if (max_load_factor_ <= 0.0) {
            throw std::invalid_argument("max_load_factor must be positive");
        }
    }

    void increment(const Key& key) {
        std::size_t idx;
        if (find_existing(key, idx)) {
            ++slots_[idx].count;
            return;
        }

        if (would_exceed_load_factor(unique_count_ + 1)) {
            rehash(next_prime(capacity() * 2));
        }

        std::size_t h1 = hash_(key) % capacity();
        std::size_t step = double_hash_step(key, capacity());

        for (std::size_t i = 0; i < capacity(); ++i) {
            std::size_t probe = (h1 + i * step) % capacity();
            if (!slots_[probe].occupied) {
                slots_[probe].key = key;
                slots_[probe].count = 1;
                slots_[probe].occupied = true;
                ++unique_count_;
                return;
            }
        }

        // Pathological: all slots probed without finding a home — rehash and retry
        rehash(next_prime(capacity() * 2));
        increment(key);
    }

    bool contains(const Key& key) const {
        std::size_t ignored;
        return find_existing(key, ignored);
    }

    bool get(const Key& key, TweetCount& count) const {
        std::size_t idx;
        if (!find_existing(key, idx)) {
            return false;
        }
        count = slots_[idx].count;
        return true;
    }

    std::size_t size() const {
        return unique_count_;
    }

    std::size_t capacity() const {
        return slots_.size();
    }

    double load_factor() const {
        if (capacity() == 0) {
            return 0.0;
        }
        return static_cast<double>(unique_count_) / static_cast<double>(capacity());
    }

    std::size_t memory_bytes() const {
        std::size_t total = sizeof(*this);
        total += slots_.capacity() * sizeof(Slot);
        for (const Slot& slot : slots_) {
            if (slot.occupied) {
                total += dynamic_key_memory_bytes(slot.key);
            }
        }
        return total;
    }

    void clear() {
        for (Slot& slot : slots_) {
            slot.occupied = false;
            slot.count = 0;
        }
        unique_count_ = 0;
    }

private:
    struct Slot {
        Key key{};
        TweetCount count = 0;
        bool occupied = false;
    };

    std::vector<Slot> slots_;
    std::size_t unique_count_ = 0;
    double max_load_factor_ = config::kMaxLoadFactor;
    Hash hash_;

    bool find_existing(const Key& key, std::size_t& out_idx) const {
        std::size_t h1 = hash_(key) % capacity();
        std::size_t step = double_hash_step(key, capacity());

        for (std::size_t i = 0; i < capacity(); ++i) {
            std::size_t probe = (h1 + i * step) % capacity();
            if (!slots_[probe].occupied) {
                return false;
            }
            if (slots_[probe].key == key) {
                out_idx = probe;
                return true;
            }
        }
        return false;
    }

    bool would_exceed_load_factor(std::size_t next_size) const {
        return static_cast<double>(next_size) / static_cast<double>(capacity()) >
               max_load_factor_;
    }

    void rehash(std::size_t new_cap) {
        std::vector<Slot> old_slots = std::move(slots_);
        slots_.assign(next_prime(new_cap), Slot{});
        unique_count_ = 0;

        for (const Slot& slot : old_slots) {
            if (!slot.occupied) {
                continue;
            }
            std::size_t h1 = hash_(slot.key) % capacity();
            std::size_t step = double_hash_step(slot.key, capacity());

            for (std::size_t i = 0; i < capacity(); ++i) {
                std::size_t probe = (h1 + i * step) % capacity();
                if (!slots_[probe].occupied) {
                    slots_[probe].key = slot.key;
                    slots_[probe].count = slot.count;
                    slots_[probe].occupied = true;
                    ++unique_count_;
                    break;
                }
            }
        }
    }
};

}  // namespace lab3
