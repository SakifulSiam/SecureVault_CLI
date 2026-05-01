#pragma once
#include <iostream>
#include <string>
#include <cstdio>
#include <cctype>

#ifdef _WIN32
    #include <conio.h>

    inline char getch_cross() {
        return _getch();
    }

    inline void clear_stdin_buffer() {
        // nothing needed on Windows
    }

    constexpr char KEY_ENTER     = '\r';
    constexpr char KEY_BACKSPACE = '\b';

#else
    #include <termios.h>
    #include <unistd.h>
    #include <sys/select.h>

    inline void clear_stdin_buffer() {
        fd_set set;
        timeval tv{0, 0};
        char c;

        while (true) {
            FD_ZERO(&set);
            FD_SET(STDIN_FILENO, &set);
            if (select(STDIN_FILENO + 1, &set, nullptr, nullptr, &tv) <= 0)
                break;
            read(STDIN_FILENO, &c, 1);
        }
    }

    inline char getch_cross() {
        char ch;
        termios oldt{}, newt{};

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        read(STDIN_FILENO, &ch, 1);

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }

    constexpr char KEY_ENTER     = '\n';
    constexpr char KEY_BACKSPACE = 127;
#endif
