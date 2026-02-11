#include <iostream>
#include <string>
#include <time.h>
#include <chrono>
#include <iomanip>
#include <termios.h>  // для управления терминалом
#include <unistd.h>   // для STDIN_FILENO

// Сохраняем оригинальные настройки терминала для восстановления
static struct termios orig_termios;

void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disable_raw_mode);  // автоматически восстановим настройки при выходе

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);  // отключаем canonical mode и эхо
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

const std::string words[] = {"apple", "banana", "cherry", "dragon",
                            "elephant", "forest", "guitar", "harmony",
                            "island", "journey", "knight", "lemon",
                            "mountain", "nebula", "ocean", "python",
                            "quantum", "river", "sunshine", "tiger"};

void create_ref_str(std::string &ref_str) {
    ref_str = "";
    int n = 2;
    int col_words = sizeof(words)/sizeof(words[0]);
    int id_prev = -1;
    for (int i = 0; i < n; i++) {
        int id_new = rand() % col_words;
        while (id_new == id_prev) {
            id_new = rand() % col_words;
        }
        ref_str += words[id_new];
        if (i < n - 1) {
            ref_str += " ";
        }
        id_prev = id_new;
    }

}

void count_mistakes(std::string ref_str, std::string cust_str, int &mis) {
    mis = 0;
    for (int i = 0; i < ref_str.length(); i++) {
        if (cust_str[i] != ref_str[i]) {
            mis++;
        }
    }
}

int main() {
    srand(time(nullptr));
    std::string ref_str;
    create_ref_str(ref_str);
    std::cout << ref_str << std::endl;

    // Включаем raw mode для посимвольного ввода
    enable_raw_mode();

    std::string cust_str;

    auto start = std::chrono::high_resolution_clock::now();

    int sim_num = 0;

    // Читаем ровно столько символов, сколько в эталоне
    while (cust_str.length() < ref_str.length()) {
        char c = getchar();  // getchar() работает без буферизации в raw mode

        // Обработка Backspace (опционально)
        if (c == 127 || c == 8) {  // 127 = DEL, 8 = Backspace
            if (!cust_str.empty()) {
                cust_str.pop_back();
                sim_num--;
                std::cout << "\b \b" << std::flush;  // стереть символ с экрана
            }
            continue;
        }

        // Игнорируем управляющие символы (кроме Backspace)
        if (c < 32) continue;

        cust_str += c;
          // ручной эхо-вывод (т.к. ECHO отключён)
        if (c != ref_str[sim_num]) {
            std::cout << "\x1B[31m" << c << "\033[0m" << std::flush;
        } else {
            std::cout << "\x1B[32m" << c << "\033[0m" << std::flush;
        }
        sim_num++;
    }

    auto end = std::chrono::high_resolution_clock::now();

    int mis;
    count_mistakes(ref_str, cust_str, mis);

    double sec = std::chrono::duration<double>(end - start).count();
    std::cout << std::endl << mis << " Ошибок" << "\t\t" << std::fixed << std::setprecision(2) << sec << " Секунд" << std::endl;

    return 0;
}
