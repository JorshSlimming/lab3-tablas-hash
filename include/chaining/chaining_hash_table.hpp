#pragma once

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
class ChainingHashTable {
public:
    explicit ChainingHashTable(
        std::size_t initial_capacity = config::kInitialCapacity,
        double max_load_factor = config::kMaxLoadFactor)
        : buckets_(next_prime(initial_capacity)),
          max_load_factor_(max_load_factor) {
        if (max_load_factor_ <= 0.0) {
            throw std::invalid_argument("max_load_factor must be positive");
        }
    }

    void increment(const Key& key) {
        const std::size_t current_index = bucket_index(key);
        for (Entry& entry : buckets_[current_index]) {
            if (entry.key == key) {
                ++entry.count;
                return;
            }
        }

        if (would_exceed_load_factor(element_count_ + 1)) {
            rehash(next_prime(capacity() * 2));
        }

        buckets_[bucket_index(key)].push_back(Entry{key, 1});
        ++element_count_;
    }

    bool contains(const Key& key) const {
        TweetCount ignored = 0;
        return get(key, ignored);
    }

    bool get(const Key& key, TweetCount& count) const {
        const std::size_t index = bucket_index(key);
        for (const Entry& entry : buckets_[index]) {
            if (entry.key == key) {
                count = entry.count;
                return true;
            }
        }
        return false;
    }

    std::size_t size() const {
        return element_count_;
    }

    std::size_t capacity() const {
        return buckets_.size();
    }

    double load_factor() const {
        if (capacity() == 0) {
            return 0.0;
        }
        return static_cast<double>(element_count_) / static_cast<double>(capacity());
    }

    std::size_t memory_bytes() const {
        std::size_t total = sizeof(*this);
        total += buckets_.capacity() * sizeof(Bucket);

        for (const Bucket& bucket : buckets_) {
            total += bucket.capacity() * sizeof(Entry);
            for (const Entry& entry : bucket) {
                total += dynamic_key_memory_bytes(entry.key);
            }
        }

        return total;
    }

    void clear() {
        for (Bucket& bucket : buckets_) {
            bucket.clear();
        }
        element_count_ = 0;
    }

private:
    struct Entry {
        Key key;
        TweetCount count;
    };

    using Bucket = std::vector<Entry>;

    std::vector<Bucket> buckets_;
    std::size_t element_count_ = 0;
    double max_load_factor_ = config::kMaxLoadFactor;
    Hash hash_;

    std::size_t bucket_index(const Key& key) const {
        return hash_(key) % buckets_.size();
    }

    bool would_exceed_load_factor(std::size_t next_size) const {
        return static_cast<double>(next_size) / static_cast<double>(capacity()) >
               max_load_factor_;
    }

    void rehash(std::size_t requested_capacity) {
        std::vector<Bucket> old_buckets = std::move(buckets_);
        buckets_.assign(next_prime(requested_capacity), Bucket{});
        element_count_ = 0;

        for (const Bucket& bucket : old_buckets) {
            for (const Entry& entry : bucket) {
                insert_existing(entry.key, entry.count);
            }
        }
    }

    void insert_existing(const Key& key, TweetCount count) {
        buckets_[bucket_index(key)].push_back(Entry{key, count});
        ++element_count_;
    }
};

}  // namespace lab3
