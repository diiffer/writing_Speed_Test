#include "TerminalManager.hpp"
#include <cstdlib>
#include <iostream>

TerminalManager::TerminalManager() {
}

TerminalManager::~TerminalManager() {
    if (raw_mode_enabled_) disableRawMode();
}

void TerminalManager::enableRawMode() {
    if (raw_mode_enabled_) return;

    tcgetattr(STDIN_FILENO, &orig_termios_);
    struct termios raw = orig_termios_;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);

    raw_mode_enabled_ = true;
}

void TerminalManager::disableRawMode() {
    if (!raw_mode_enabled_) return;

    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios_);
    raw_mode_enabled_ = false;
}

char TerminalManager::readChar() const {
    return getchar();
}