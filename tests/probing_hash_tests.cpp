#include <cassert>
#include <string>
#include <vector>

#include "closed/probing_hash_table.hpp"
#include "common/dataset_types.hpp"

namespace {

struct ConstantHash {
    std::size_t operator()(const lab3::UserId&) const {
        return 3;
    }
};

void test_linear_probing_handles_collisions_and_counts() {
    lab3::ProbingHashTable<lab3::UserId, lab3::ProbeStrategy::Linear, ConstantHash>
        table(101);

    table.increment(10);
    table.increment(20);
    table.increment(30);
    table.increment(20);

    lab3::TweetCount count = 0;
    assert(table.size() == 3);
    assert(table.get(10, count) && count == 1);
    assert(table.get(20, count) && count == 2);
    assert(table.get(30, count) && count == 1);
    assert(!table.contains(40));
}

void test_quadratic_probing_handles_collisions_and_counts() {
    lab3::ProbingHashTable<lab3::UserId, lab3::ProbeStrategy::Quadratic, ConstantHash>
        table(101);

    table.increment(100);
    table.increment(200);
    table.increment(300);
    table.increment(100);
    table.increment(300);
    table.increment(300);

    lab3::TweetCount count = 0;
    assert(table.size() == 3);
    assert(table.get(100, count) && count == 2);
    assert(table.get(200, count) && count == 1);
    assert(table.get(300, count) && count == 3);
}

void test_probing_tables_rehash_and_preserve_counts() {
    lab3::ProbingHashTable<lab3::UserId, lab3::ProbeStrategy::Linear> linear(5);
    lab3::ProbingHashTable<lab3::UserId, lab3::ProbeStrategy::Quadratic> quadratic(5);

    for (lab3::UserId key = 0; key < 200; ++key) {
        linear.increment(key);
        quadratic.increment(key);
    }
    for (lab3::UserId key = 0; key < 200; key += 2) {
        linear.increment(key);
        quadratic.increment(key);
    }

    lab3::TweetCount count = 0;
    assert(linear.size() == 200);
    assert(quadratic.size() == 200);
    assert(linear.capacity() > 5);
    assert(quadratic.capacity() > 5);
    assert(linear.get(42, count) && count == 2);
    assert(quadratic.get(42, count) && count == 2);
    assert(linear.get(43, count) && count == 1);
    assert(quadratic.get(43, count) && count == 1);
}

void test_probing_tables_support_screen_names_and_clear() {
    lab3::ProbingHashTable<lab3::UserScreenName, lab3::ProbeStrategy::Linear>
        linear_names;
    lab3::ProbingHashTable<lab3::UserScreenName, lab3::ProbeStrategy::Quadratic>
        quadratic_names;

    const std::vector<std::string> names = {"alice", "bob", "alice", "carla"};
    for (const std::string& name : names) {
        linear_names.increment(name);
        quadratic_names.increment(name);
    }

    lab3::TweetCount count = 0;
    assert(linear_names.size() == 3);
    assert(quadratic_names.size() == 3);
    assert(linear_names.get("alice", count) && count == 2);
    assert(quadratic_names.get("alice", count) && count == 2);
    assert(linear_names.memory_bytes() > sizeof(linear_names));
    assert(quadratic_names.memory_bytes() > sizeof(quadratic_names));

    linear_names.clear();
    quadratic_names.clear();
    assert(linear_names.size() == 0);
    assert(quadratic_names.size() == 0);
    assert(!linear_names.contains("alice"));
    assert(!quadratic_names.contains("alice"));
}

}

int main() {
    test_linear_probing_handles_collisions_and_counts();
    test_quadratic_probing_handles_collisions_and_counts();
    test_probing_tables_rehash_and_preserve_counts();
    test_probing_tables_support_screen_names_and_clear();
    return 0;
}
