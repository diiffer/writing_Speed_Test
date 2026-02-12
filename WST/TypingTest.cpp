#include "TypingTest.hpp"
#include <iostream>
#include <iomanip>

TypingTest::TypingTest(const std::vector<std::string>& words)
    : generator_(words), duration_(0.0), mistakes_(0) {}

void TypingTest::start(int word_count) {
    // Генерация эталонной строки
    reference_ = generator_.generate(word_count);
    std::cout << reference_ << std::endl;

    // Запуск теста
    terminal_.enableRawMode();
    auto start = std::chrono::high_resolution_clock::now();
    runInput();
    auto end = std::chrono::high_resolution_clock::now();
    terminal_.disableRawMode();

    // Расчёт результатов
    duration_ = std::chrono::duration<double>(end - start).count();
    countMistakes();

    std::cout << std::endl;
}

void TypingTest::runInput() {
    input_.clear();
    int pos = 0;

    while (input_.length() < reference_.length()) {
        char c = terminal_.readChar();

        // Backspace
        if (c == 127 || c == 8) {
            if (!input_.empty()) {
                input_.pop_back();
                pos--;
                std::cout << "\b \b" << std::flush;
            }
            continue;
        }

        // Игнорируем управляющие символы
        if (c < 32) continue;

        input_ += c;

        // Визуализация символа
        bool is_correct = (pos < static_cast<int>(reference_.length()) &&
                          c == reference_[pos]);
        displayChar(c, is_correct);

        pos++;
    }
}

void TypingTest::displayChar(char c, bool is_correct) const {
    if (is_correct) {
        std::cout << "\x1B[32m" << c << "\033[0m" << std::flush;
    } else {
        std::cout << "\x1B[31m" << c << "\033[0m" << std::flush;
    }
}

void TypingTest::countMistakes() {
    mistakes_ = 0;
    for (size_t i = 0; i < reference_.length(); i++) {
        if (i >= input_.length() || reference_[i] != input_[i]) {
            mistakes_++;
        }
    }
}

void TypingTest::displayResults() const {
    std::cout << mistakes_ << " Ошибок"
              << "\t\t"
              << std::fixed << std::setprecision(2)
              << duration_ << " Секунд"
              << std::endl;
}