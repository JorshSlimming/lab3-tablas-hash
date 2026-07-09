#include <cassert>
#include <cstddef>
#include <string>

#include "common/dataset_types.hpp"
#include "stl/unordered_map_adapter.hpp"

namespace {

void test_adapter_increment_contract() {
    lab3::UnorderedMapAdapter<lab3::UserScreenName> table;
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

void test_adapter_user_id() {
    lab3::UnorderedMapAdapter<lab3::UserId> table;
    lab3::TweetCount count = 0;

    table.increment(100);
    table.increment(200);
    table.increment(100);

    assert(table.size() == 2);
    assert(table.get(100, count));
    assert(count == 2);
    assert(table.get(200, count));
    assert(count == 1);
}

void test_adapter_clear() {
    lab3::UnorderedMapAdapter<lab3::UserId> table;
    table.increment(1);
    table.increment(2);
    assert(table.size() == 2);

    table.clear();
    assert(table.size() == 0);
    assert(!table.contains(1));
}

void test_adapter_capacity_is_bucket_count() {
    lab3::UnorderedMapAdapter<lab3::UserId> table;
    table.increment(1);
    table.increment(2);
    table.increment(3);

    assert(table.capacity() > 0);
    assert(table.size() <= table.capacity());
}

void test_adapter_memory_estimate_nontrivial() {
    lab3::UnorderedMapAdapter<lab3::UserScreenName> table;
    table.increment("a_long_enough_string_to_allocate");
    table.increment("another_allocated_string_here");


    assert(table.memory_bytes() > sizeof(table));
    assert(table.memory_bytes() >
           sizeof(lab3::UnorderedMapAdapter<lab3::UserScreenName>));
}

}

int main() {
    test_adapter_increment_contract();
    test_adapter_user_id();
    test_adapter_clear();
    test_adapter_capacity_is_bucket_count();
    test_adapter_memory_estimate_nontrivial();
    return 0;
}
