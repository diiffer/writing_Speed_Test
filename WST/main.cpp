#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "TypingTest.hpp"
#include "Difficulty.hpp"

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::cout << "Select difficulty level:" << std::endl;
    std::cout << "1. Easy" << std::endl;
    std::cout << "2. Medium" << std::endl;
    std::cout << "3. Hard" << std::endl;

    int choice;
    std::cin >> choice;

    Difficulty difficulty;
    switch (choice) {
        case 1:
            difficulty = Difficulty::Easy;
            break;
        case 2:
            difficulty = Difficulty::Medium;
            break;
        case 3:
            difficulty = Difficulty::Hard;
            break;
        default:
            std::cout << "Invalid choice. Defaulting to Medium." << std::endl;
            difficulty = Difficulty::Medium;
            break;
    }

    // Создаём и запускаем тест
    TypingTest test(difficulty);
    test.start(10); // 10 слов в тесте
    test.displayResults();

    return 0;
}