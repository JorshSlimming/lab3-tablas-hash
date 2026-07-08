#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "benchmark/benchmark_runner.hpp"
#include "chaining/chaining_hash_table.hpp"
#include "closed/double_hash_table.hpp"
#include "common/dataset_reader.hpp"
#include "common/experiment_config.hpp"
#include "stl/unordered_map_adapter.hpp"

int main(int argc, char* argv[]) {
    const std::string dataset_path = argc >= 2 ? argv[1] : "auspol2019.csv";
    const std::string results_path =
        argc >= 3 ? argv[2] : "results/benchmark_results.csv";

    try {
        std::cout << "Reading dataset: " << dataset_path << '\n';
        const lab3::TweetKeys keys = lab3::read_tweet_keys_csv(dataset_path);
        std::cout << "Tweets loaded: " << keys.size() << '\n';

        std::ofstream output(results_path);
        if (!output) {
            throw std::runtime_error("could not create results file: " + results_path);
        }

        output << lab3::config::kResultHeader << '\n';

        lab3::run_benchmark<lab3::ChainingHashTable<lab3::UserId>>(
            keys.user_ids, "user_id", "open_hash", "chaining", output);
        lab3::run_benchmark<lab3::ChainingHashTable<lab3::UserScreenName>>(
            keys.user_screen_names, "user_screen_name", "open_hash", "chaining",
            output);

        lab3::run_benchmark<lab3::DoubleHashTable<lab3::UserId>>(
            keys.user_ids, "user_id", "closed_hash", "double_hashing", output);
        lab3::run_benchmark<lab3::DoubleHashTable<lab3::UserScreenName>>(
            keys.user_screen_names, "user_screen_name", "closed_hash",
            "double_hashing", output);

        lab3::run_benchmark<lab3::UnorderedMapAdapter<lab3::UserId>>(
            keys.user_ids, "user_id", "stl", "unordered_map", output);
        lab3::run_benchmark<lab3::UnorderedMapAdapter<lab3::UserScreenName>>(
            keys.user_screen_names, "user_screen_name", "stl", "unordered_map",
            output);

        std::cout << "Results written to: " << results_path << '\n';
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
