#include <cassert>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

#include "benchmark/benchmark_runner.hpp"
#include "chaining/chaining_hash_table.hpp"
#include "closed/double_hash_table.hpp"
#include "common/experiment_config.hpp"
#include "stl/unordered_map_adapter.hpp"

namespace {

std::vector<lab3::UserId> make_user_ids(std::size_t total, std::size_t modulo) {
    std::vector<lab3::UserId> keys;
    keys.reserve(total);
    for (std::size_t i = 0; i < total; ++i) {
        keys.push_back(static_cast<lab3::UserId>(i % modulo));
    }
    return keys;
}

std::vector<std::string> split_semicolon_line(const std::string& line) {
    std::vector<std::string> fields;
    std::string current;
    for (char ch : line) {
        if (ch == ';') {
            fields.push_back(current);
            current.clear();
        } else {
            current.push_back(ch);
        }
    }
    fields.push_back(current);
    return fields;
}

void test_benchmark_runner_writes_expected_csv_format() {
    const std::string path = "results/benchmark_test_output.csv";
    const std::vector<lab3::UserId> keys =
        make_user_ids(lab3::config::kBenchmarkStep, 123);

    {
        std::ofstream output(path);
        assert(output.good());
        output << lab3::config::kResultHeader << '\n';
        lab3::run_benchmark<lab3::ChainingHashTable<lab3::UserId>>(
            keys, "user_id", "open_hash", "chaining", output);
    }

    std::ifstream input(path);
    assert(input.good());

    std::string header;
    std::getline(input, header);
    assert(header == lab3::config::kResultHeader);

    std::string row;
    assert(std::getline(input, row));
    const std::vector<std::string> fields = split_semicolon_line(row);
    assert(fields.size() == 9);
    assert(fields[0] == "1");
    assert(fields[1] == "user_id");
    assert(fields[2] == "open_hash");
    assert(fields[3] == "chaining");
    assert(fields[4] == std::to_string(lab3::config::kBenchmarkStep));
    assert(fields[5] == "123");

    std::remove(path.c_str());
}

void test_unique_user_count_matches_across_structures() {
    const std::vector<lab3::UserId> keys =
        make_user_ids(lab3::config::kBenchmarkStep, 257);

    lab3::ChainingHashTable<lab3::UserId> chaining;
    lab3::DoubleHashTable<lab3::UserId> double_hashing;
    lab3::UnorderedMapAdapter<lab3::UserId> unordered;

    for (const lab3::UserId key : keys) {
        chaining.increment(key);
        double_hashing.increment(key);
        unordered.increment(key);
    }

    assert(chaining.size() == 257);
    assert(double_hashing.size() == chaining.size());
    assert(unordered.size() == chaining.size());
}

}  // namespace

int main() {
    test_benchmark_runner_writes_expected_csv_format();
    test_unique_user_count_matches_across_structures();
    return 0;
}
