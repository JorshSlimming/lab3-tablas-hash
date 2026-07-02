#pragma once

#include <cstddef>
#include <cstdint>

namespace lab3::config {

constexpr std::size_t kInitialCapacity = 101;
constexpr double kMaxLoadFactor = 0.60;
constexpr std::size_t kBenchmarkStep = 10000;
constexpr std::size_t kBenchmarkMaxTweets = 180000;
constexpr std::uint32_t kBenchmarkRuns = 20;

constexpr const char* kResultHeader =
    "run;key_type;structure;strategy;n_tweets;unique_users;time_us;memory_bytes;capacity";

}  // namespace lab3::config
