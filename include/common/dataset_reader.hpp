#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "common/dataset_types.hpp"

namespace lab3 {

std::vector<std::string> parse_csv_line(const std::string& line);

TweetKeys read_tweet_keys_csv(const std::string& path, std::size_t limit = 0);

}
