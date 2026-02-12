#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "TypingTest.hpp"

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Набор слов
    const std::vector<std::string> words = {
        "apple", "banana", "cherry", "dragon", "elephant",
        "forest", "guitar", "harmony", "island", "journey",
        "knight", "lemon", "mountain", "nebula", "ocean",
        "python", "quantum", "river", "sunshine", "tiger"
    };

    // Создаём и запускаем тест
    TypingTest test(words);
    test.start(5);          // 5 слов в тесте
    test.displayResults();

    return 0;
}