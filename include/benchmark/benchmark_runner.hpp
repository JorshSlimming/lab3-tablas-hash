#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <string>
#include <vector>

#include "common/experiment_config.hpp"

namespace lab3 {

template <typename Table, typename Key>
void run_benchmark(
    const std::vector<Key>& keys,
    const std::string& key_type,
    const std::string& structure,
    const std::string& strategy,
    std::ofstream& output) {
    const std::size_t max_n =
        std::min<std::size_t>(config::kBenchmarkMaxTweets, keys.size());

    for (std::uint32_t run = 1; run <= config::kBenchmarkRuns; ++run) {
        for (std::size_t n = config::kBenchmarkStep; n <= max_n;
             n += config::kBenchmarkStep) {
            Table table;

            const auto start = std::chrono::steady_clock::now();
            for (std::size_t i = 0; i < n; ++i) {
                table.increment(keys[i]);
            }
            const auto end = std::chrono::steady_clock::now();

            const auto time_us =
                std::chrono::duration_cast<std::chrono::microseconds>(end - start)
                    .count();

            output << run << ';'
                   << key_type << ';'
                   << structure << ';'
                   << strategy << ';'
                   << n << ';'
                   << table.size() << ';'
                   << time_us << ';'
                   << table.memory_bytes() << ';'
                   << table.capacity() << '\n';
        }
    }
}

}
