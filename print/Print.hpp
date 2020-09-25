#ifndef PRINT_HPP
#define PRINT_HPP

#include "drivers/uart/IUart.hpp"
#include <stdarg.h>

#define PRINTLN(x, ...) PrintHandler::print(x, true, ##__VA_ARGS__)
#define PRINT(x, ...) PrintHandler::print(x, false, ##__VA_ARGS__)

class PrintHandler
{
    public:
        static void initialize(uart::IUart* pUart);
        static void print(const char* format, bool newline, ...);

    private:
        static uart::IUart* pUart_;

        const static uint16_t MAX_STRING_LENGTH = 255;
        static char outputStr[];

        static void parseArguement(char* ouputStr, va_list* pList, char* selectorStr);
};

#endif