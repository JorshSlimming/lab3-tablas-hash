#include <cassert>
#include <cstddef>
#include <string>
#include <vector>

#include "chaining/chaining_hash_table.hpp"
#include "common/dataset_reader.hpp"
#include "common/hash_functions.hpp"

namespace {

struct ConstantHash {
    std::size_t operator()(const lab3::UserId&) const {
        return 0;
    }
};

void test_csv_parser_handles_quotes_and_commas() {
    const std::vector<std::string> fields =
        lab3::parse_csv_line("1,\"hello, world\",\"likes \"\"quotes\"\"\",last");

    assert(fields.size() == 4);
    assert(fields[0] == "1");
    assert(fields[1] == "hello, world");
    assert(fields[2] == "likes \"quotes\"");
    assert(fields[3] == "last");

    const std::vector<std::string> multiline =
        lab3::parse_csv_line("1,\"hello\nworld\",last");
    assert(multiline.size() == 3);
    assert(multiline[1] == "hello\nworld");
}

void test_dataset_reader_extracts_required_keys() {
    const lab3::TweetKeys keys = lab3::read_tweet_keys_csv("data/sample_tweets.csv");

    assert(keys.size() == 4);
    assert(keys.user_ids[0] == 100);
    assert(keys.user_ids[2] == 100);
    assert(keys.user_screen_names[1] == "bob");
    assert(keys.user_screen_names[2] == "alice");
}

void test_hash_functions_are_stable() {
    const std::size_t id_hash = lab3::PrimaryHash<lab3::UserId>{}(12345);
    const std::size_t same_id_hash = lab3::PrimaryHash<lab3::UserId>{}(12345);
    const std::size_t name_hash = lab3::PrimaryHash<lab3::UserScreenName>{}("alice");

    assert(id_hash == same_id_hash);
    assert(name_hash == lab3::PrimaryHash<lab3::UserScreenName>{}("alice"));
    assert(lab3::double_hash_step<lab3::UserId>(12345, 101) >= 1);
}

void test_chaining_insert_and_increment() {
    lab3::ChainingHashTable<lab3::UserScreenName> table;
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

void test_chaining_forced_collisions() {
    lab3::ChainingHashTable<lab3::UserId, ConstantHash> table(5, 0.95);
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

void test_chaining_rehash_preserves_counts() {
    lab3::ChainingHashTable<lab3::UserId> table(3, 0.50);
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

}

int main() {
    test_csv_parser_handles_quotes_and_commas();
    test_dataset_reader_extracts_required_keys();
    test_hash_functions_are_stable();
    test_chaining_insert_and_increment();
    test_chaining_forced_collisions();
    test_chaining_rehash_preserves_counts();
    return 0;
}
