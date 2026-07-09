#pragma once

#include <cstddef>
#include <unordered_map>
#include <utility>

#include "common/dataset_types.hpp"
#include "common/experiment_config.hpp"
#include "common/memory_utils.hpp"

namespace lab3 {

template <typename Key>
class UnorderedMapAdapter {
public:
    explicit UnorderedMapAdapter(
        std::size_t = config::kInitialCapacity,
        double = config::kMaxLoadFactor) {}

    void increment(const Key& key) {
        ++map_[key];
    }

    bool contains(const Key& key) const {
        return map_.find(key) != map_.end();
    }

    bool get(const Key& key, TweetCount& count) const {
        auto it = map_.find(key);
        if (it == map_.end()) {
            return false;
        }
        count = it->second;
        return true;
    }

    std::size_t size() const {
        return map_.size();
    }

    std::size_t capacity() const {
        return map_.bucket_count();
    }

    double load_factor() const {
        if (map_.bucket_count() == 0) {
            return 0.0;
        }
        return static_cast<double>(map_.size()) / static_cast<double>(map_.bucket_count());
    }







    std::size_t memory_bytes() const {
        constexpr std::size_t kNodeOverhead = 3 * sizeof(void*);
        std::size_t total = sizeof(*this);
        total += sizeof(void*) * map_.bucket_count();
        total += map_.size() * (kNodeOverhead + sizeof(std::pair<const Key, TweetCount>));

        for (const auto& kv : map_) {
            total += dynamic_key_memory_bytes(kv.first);
        }

        return total;
    }

    void clear() {
        map_.clear();
    }

private:
    std::unordered_map<Key, TweetCount> map_;
};

}
