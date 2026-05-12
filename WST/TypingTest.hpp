#pragma once
#include <string>
#include <chrono>
#include "TerminalManager.hpp"
#include "WordGenerator.hpp"
#include "Difficulty.hpp"

class TypingTest {
private:
    TerminalManager terminal_;
    WordGenerator generator_;
    std::string reference_;
    std::string input_;
    double duration_;
    int mistakes_;

    void runInput();
    void countMistakes();
    // Возвращаем простую сигнатуру
    static void displayChar(char c, bool is_correct);

public:
    // Убираем язык из конструктора
    TypingTest(Difficulty difficulty);

    void start(int word_count);
    void displayResults() const;

    // Геттеры для тестирования
    const std::string& getReference() const { return reference_; }
    const std::string& getInput() const { return input_; }
    double getDuration() const { return duration_; }
    int getMistakes() const { return mistakes_; }
};