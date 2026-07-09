#include "common/dataset_reader.hpp"

#include <fstream>
#include <stdexcept>

namespace lab3 {

namespace {

bool has_open_quote(const std::string& record) {
    bool in_quotes = false;
    for (std::size_t i = 0; i < record.size(); ++i) {
        if (record[i] == '"') {
            if (in_quotes && i + 1 < record.size() && record[i + 1] == '"') {
                ++i;
            } else {
                in_quotes = !in_quotes;
            }
        }
    }
    return in_quotes;
}

bool read_csv_record(std::istream& input, std::string& record) {
    record.clear();

    std::string line;
    if (!std::getline(input, line)) {
        return false;
    }

    record = line;
    while (has_open_quote(record) && std::getline(input, line)) {
        record.push_back('\n');
        record += line;
    }

    return true;
}

}

std::vector<std::string> parse_csv_line(const std::string& line) {
    std::vector<std::string> fields;
    std::string current;
    bool in_quotes = false;

    for (std::size_t i = 0; i < line.size(); ++i) {
        const char character = line[i];

        if (character == '"') {
            if (in_quotes && i + 1 < line.size() && line[i + 1] == '"') {
                current.push_back('"');
                ++i;
            } else {
                in_quotes = !in_quotes;
            }
        } else if (character == ',' && !in_quotes) {
            fields.push_back(current);
            current.clear();
        } else {
            current.push_back(character);
        }
    }

    fields.push_back(current);
    return fields;
}

TweetKeys read_tweet_keys_csv(const std::string& path, std::size_t limit) {
    std::ifstream input(path);
    if (!input) {
        throw std::runtime_error("could not open dataset: " + path);
    }

    std::string line;
    if (!read_csv_record(input, line)) {
        throw std::runtime_error("dataset is empty: " + path);
    }

    const std::vector<std::string> header = parse_csv_line(line);
    std::size_t user_id_index = header.size();
    std::size_t screen_name_index = header.size();

    for (std::size_t i = 0; i < header.size(); ++i) {
        if (header[i] == "user_id") {
            user_id_index = i;
        } else if (header[i] == "user_screen_name") {
            screen_name_index = i;
        }
    }

    if (user_id_index == header.size() || screen_name_index == header.size()) {
        throw std::runtime_error("dataset does not contain required user columns");
    }

    TweetKeys keys;
    if (limit > 0) {
        keys.user_ids.reserve(limit);
        keys.user_screen_names.reserve(limit);
    }

    while (read_csv_record(input, line)) {
        if (limit > 0 && keys.size() >= limit) {
            break;
        }
        if (line.empty()) {
            continue;
        }

        std::vector<std::string> fields = parse_csv_line(line);
        if (fields.size() <= user_id_index || fields.size() <= screen_name_index) {
            continue;
        }

        try {
            keys.user_ids.push_back(static_cast<UserId>(std::stoull(fields[user_id_index])));
        } catch (const std::exception&) {
            throw std::runtime_error("invalid user_id value: " + fields[user_id_index]);
        }
        keys.user_screen_names.push_back(fields[screen_name_index]);
    }

    return keys;
}

}
