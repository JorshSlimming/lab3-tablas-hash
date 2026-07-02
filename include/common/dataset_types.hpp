#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace lab3 {

using UserId = std::uint64_t;
using UserScreenName = std::string;
using TweetCount = std::uint32_t;

struct TweetKeys {
    std::vector<UserId> user_ids;
    std::vector<UserScreenName> user_screen_names;

    std::size_t size() const {
        return user_ids.size();
    }
};

}  // namespace lab3
