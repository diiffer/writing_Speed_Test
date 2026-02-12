#pragma once
#include <termios.h>
#include <unistd.h>

class TerminalManager {
private:
    struct termios orig_termios_;
    bool raw_mode_enabled_ = false;

public:
    TerminalManager();
    ~TerminalManager();
    
    void enableRawMode();
    void disableRawMode();
    char readChar() const;  // getchar() с защитой
};