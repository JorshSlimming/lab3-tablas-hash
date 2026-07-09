#include <cassert>
#include <cstddef>
#include <string>
#include <vector>

#include "closed/double_hash_table.hpp"
#include "common/dataset_types.hpp"
#include "common/hash_functions.hpp"

namespace {


struct CollisionHash {
    std::size_t operator()(const lab3::UserId&) const {
        return 0;
    }
};

void test_double_hash_insert_and_increment() {
    lab3::DoubleHashTable<lab3::UserScreenName> table;
    lab3::TweetCount count = 0;

    table.increment("alice");
    table.increment("bob");
    table.increment("alice");

    assert(table.size() == 2);
    assert(table.get("alice", count));
    assert(count == 2);
    assert(table.get("bob", count));
    assert(count == 1);
    assert(!table.contains("carla"));
}

void test_double_hash_forced_collisions() {
    lab3::DoubleHashTable<lab3::UserId, CollisionHash> table(5, 0.95);
    lab3::TweetCount count = 0;

    table.increment(1);
    table.increment(2);
    table.increment(3);
    table.increment(1);

    assert(table.size() == 3);
    assert(table.get(1, count));
    assert(count == 2);
    assert(table.get(2, count));
    assert(count == 1);
    assert(table.get(3, count));
    assert(count == 1);
}

void test_double_hash_rehash_preserves_counts() {
    lab3::DoubleHashTable<lab3::UserId> table(3, 0.50);
    lab3::TweetCount count = 0;

    for (lab3::UserId key = 1; key <= 30; ++key) {
        table.increment(key);
        table.increment(key);
    }

    assert(table.size() == 30);
    assert(table.capacity() > 3);
    for (lab3::UserId key = 1; key <= 30; ++key) {
        assert(table.get(key, count));
        assert(count == 2);
    }
}

void test_double_hash_clear() {
    lab3::DoubleHashTable<lab3::UserId> table;
    table.increment(10);
    table.increment(20);
    assert(table.size() == 2);

    table.clear();
    assert(table.size() == 0);

    lab3::TweetCount count = 0;
    assert(!table.get(10, count));
    assert(!table.get(20, count));
}

void test_double_hash_memory_bytes_nontrivial() {
    lab3::DoubleHashTable<lab3::UserScreenName> table;
    table.increment("hello");
    table.increment("world");


    assert(table.memory_bytes() > sizeof(table));
}

}

int main() {
    test_double_hash_insert_and_increment();
    test_double_hash_forced_collisions();
    test_double_hash_rehash_preserves_counts();
    test_double_hash_clear();
    test_double_hash_memory_bytes_nontrivial();
    return 0;
}
