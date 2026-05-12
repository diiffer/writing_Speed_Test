#include "TypingTest.hpp"
#include <algorithm>

TypingTest::TypingTest(Difficulty difficulty)
    : generator_(difficulty) {}

void TypingTest::start(int word_count) {
    reference_ = generator_.generate(word_count);
    input_.clear();
    mistakes_ = 0;
}

TestState TypingTest::update(const std::string& current_input) {
    input_ = current_input;

    // Calculate mistakes based on current input compared to reference
    mistakes_ = 0;
    std::vector<bool> correctness;
    correctness.reserve(input_.length());

    for (size_t i = 0; i < input_.length(); ++i) {
        if (i < reference_.length()) {
            bool is_correct = (input_[i] == reference_[i]);
            correctness.push_back(is_correct);
            if (!is_correct) {
                mistakes_++;
            }
        } else {
            // Input longer than reference is also a mistake
            correctness.push_back(false);
            mistakes_++;
        }
    }

    // Any missing characters from reference are also mistakes
    if (input_.length() < reference_.length()) {
        mistakes_ += (reference_.length() - input_.length());
    }

    bool is_finished = (input_.length() >= reference_.length());

    return {
        mistakes_,
        is_finished,
        reference_,
        input_,
        correctness
    };
}
