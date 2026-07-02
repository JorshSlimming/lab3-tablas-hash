#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "chaining/chaining_hash_table.hpp"
#include "common/dataset_reader.hpp"
#include "common/experiment_config.hpp"

namespace {

template <typename Key>
void run_chaining_benchmark(
    const std::vector<Key>& keys,
    const std::string& key_type,
    std::ofstream& output) {
    const std::size_t max_n =
        std::min<std::size_t>(lab3::config::kBenchmarkMaxTweets, keys.size());

    for (std::uint32_t run = 1; run <= lab3::config::kBenchmarkRuns; ++run) {
        for (std::size_t n = lab3::config::kBenchmarkStep; n <= max_n;
             n += lab3::config::kBenchmarkStep) {
            lab3::ChainingHashTable<Key> table;

            const auto start = std::chrono::steady_clock::now();
            for (std::size_t i = 0; i < n; ++i) {
                table.increment(keys[i]);
            }
            const auto end = std::chrono::steady_clock::now();

            const auto time_us =
                std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            output << run << ';'
                   << key_type << ';'
                   << "open_hash" << ';'
                   << "chaining" << ';'
                   << n << ';'
                   << table.size() << ';'
                   << time_us << ';'
                   << table.memory_bytes() << ';'
                   << table.capacity() << '\n';
        }
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    const std::string dataset_path = argc >= 2 ? argv[1] : "auspol2019.csv";
    const std::string results_path =
        argc >= 3 ? argv[2] : "results/chaining_results.csv";

    try {
        std::cout << "Reading dataset: " << dataset_path << '\n';
        const lab3::TweetKeys keys = lab3::read_tweet_keys_csv(dataset_path);
        std::cout << "Tweets loaded: " << keys.size() << '\n';

        std::ofstream output(results_path);
        if (!output) {
            throw std::runtime_error("could not create results file: " + results_path);
        }

        output << lab3::config::kResultHeader << '\n';
        run_chaining_benchmark(keys.user_ids, "user_id", output);
        run_chaining_benchmark(keys.user_screen_names, "user_screen_name", output);

        std::cout << "Results written to: " << results_path << '\n';
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
