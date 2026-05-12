#pragma once
#include <string>
#include <vector>
#include "Difficulty.hpp"

class WordGenerator {
private:
    std::vector<std::string> words_;
    int prev_index_ = -1;

    void initializeWords(Difficulty difficulty);

public:
    WordGenerator(Difficulty difficulty);

    std::string generate(int word_count);
    void reset();
};