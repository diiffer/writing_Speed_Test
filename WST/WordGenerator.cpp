#include "WordGenerator.hpp"
#include <cstdlib>
#include <algorithm>

WordGenerator::WordGenerator(const std::vector<std::string>& words)
    : words_(words) {}

std::string WordGenerator::generate(int word_count) {
    std::string result;
    prev_index_ = -1;  // сброс перед генерацией

    for (int i = 0; i < word_count; i++) {
        int new_index;
        do {
            new_index = std::rand() % words_.size();
        } while (new_index == prev_index_ && words_.size() > 1);

        result += words_[new_index];
        if (i < word_count - 1) result += " ";

        prev_index_ = new_index;
    }

    return result;
}

void WordGenerator::reset() {
    prev_index_ = -1;
}