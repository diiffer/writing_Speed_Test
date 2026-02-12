#pragma once
#include <string>
#include <vector>

class WordGenerator {
private:
    std::vector<std::string> words_;
    int prev_index_ = -1;

public:
    WordGenerator(const std::vector<std::string>& words);

    std::string generate(int word_count);
    void reset();  // сбросить предыдущий индекс
};