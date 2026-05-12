#include "TypingTest.hpp"
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>

// Конструктор теперь снова простой
TypingTest::TypingTest(Difficulty difficulty)
    : generator_(difficulty), duration_(0.0), mistakes_(0) {}

void TypingTest::start(int word_count) {
    // Генерация эталонной строки
    reference_ = generator_.generate(word_count);

    // Четкий вывод текста и отсчета
    std::cout << "--- Typing Test ---" << std::endl;
    std::cout << "Text to type:" << std::endl;
    std::cout << reference_ << std::endl << std::endl;

    std::cout << "Get ready..." << std::endl;
    for (int i = 3; i > 0; --i) {
        std::cout << "\r" << i << "..." << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "\rGo!        " << std::endl;

    // Перемещаем курсор на строку, где будет происходить ввод
    std::cout << "\x1B[A"; // Переместить курсор на одну строку вверх
    std::cout << "\r" << std::flush; // В начало строки

    // Запуск теста
    terminal_.enableRawMode();
    auto start_time = std::chrono::high_resolution_clock::now();
    runInput();
    auto end_time = std::chrono::high_resolution_clock::now();
    terminal_.disableRawMode();

    duration_ = std::chrono::duration<double>(end_time - start_time).count();
    countMistakes();

    std::cout << std::endl;
}

// Упрощенная версия, работающая с char
void TypingTest::runInput() {
    input_.clear();
    size_t pos = 0;

    while (pos < reference_.length()) {
        char c = terminal_.readChar();

        if (c == 127 || c == 8) { // Backspace
            if (pos > 0) {
                pos--;
                input_.pop_back();
                // Стираем символ с экрана
                std::cout << "\b \b" << std::flush;
            }
            continue;
        }

        // Игнорируем все, что не является печатным ASCII символом
        if (c < 32 || c > 126) {
            continue;
        }

        bool is_correct = (c == reference_[pos]);
        displayChar(c, is_correct);

        input_ += c;
        pos++;
    }
}

// Функция подсветки снова работает с char
void TypingTest::displayChar(char c, bool is_correct) {
    if (is_correct) {
        std::cout << "\x1B[32m" << c << "\033[0m" << std::flush; // Зеленый
    } else {
        std::cout << "\x1B[31m" << c << "\033[0m" << std::flush; // Красный
    }
}

// Подсчет ошибок снова простой
void TypingTest::countMistakes() {
    mistakes_ = 0;
    for (size_t i = 0; i < reference_.length(); ++i) {
        if (i >= input_.length() || reference_[i] != input_[i]) {
            mistakes_++;
        }
    }
}

void TypingTest::displayResults() const {
    std::cout << std::endl << std::endl;
    std::cout << "--- Results ---" << std::endl;
    std::cout << "Mistakes: " << mistakes_ << std::endl;
    std::cout << "Time: " << std::fixed << std::setprecision(2) << duration_ << " seconds" << std::endl;
}