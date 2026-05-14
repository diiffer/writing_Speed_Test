#pragma once
#include <string>
#include <vector>
#include <chrono>
#include "TypingTest.hpp"
#include "Difficulty.hpp"

class GuiManager {
private:
    TypingTest* test_ = nullptr;
    std::string input_buffer_;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;
    bool is_running_ = false;
    bool is_finished_ = false;
    float wpm_ = 0.0f;
    int mistakes_ = 0;
    Difficulty current_difficulty_ = Difficulty::Medium;
    int word_count_ = 10;

public:
    GuiManager() = default;
    ~GuiManager() { delete test_; }

    void render();
    void startTest();
    void stopTest();
    void updateLogic();
};
