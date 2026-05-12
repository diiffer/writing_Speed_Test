#pragma once
#include <string>
#include <vector>
#include "WordGenerator.hpp"
#include "Difficulty.hpp"

struct TestState {
    int mistakes;
    bool is_finished;
    std::string reference;
    std::string current_input;
    std::vector<bool> correctness; // true if character at index is correct
};

class TypingTest {
private:
    WordGenerator generator_;
    std::string reference_;
    std::string input_;
    int mistakes_ = 0;

public:
    explicit TypingTest(Difficulty difficulty);

    void start(int word_count);
    TestState update(const std::string& current_input);

    const std::string& getReference() const { return reference_; }
    const std::string& getInput() const { return input_; }
    int getMistakes() const { return mistakes_; }
};