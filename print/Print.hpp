#ifndef PRINT_HPP
#define PRINT_HPP

#include "drivers/uart/IUart.hpp"
#include <stdarg.h>

#define PRINTLN(x, ...) PrintHandler::print(x, true, ##__VA_ARGS__)
#define PRINT(x, ...) PrintHandler::print(x, false, ##__VA_ARGS__)
#define PRINT_FLUSH() PrintHandler::flushUart()

#ifdef DEBUG
#define DEBUG_PRINTLN(x, ...) PrintHandler::print(x, true, ##__VA_ARGS__)
#define DEBUG_PRINT(x, ...) PrintHandler::print(x, false, ##__VA_ARGS__)
#else
#define DEBUG_PRINTLN(x, ...)
#define DEBUG_PRINT(x, ...)
#endif

class PrintHandler
{
    public:
        static void initialize(Uart::IUart* pUart);
        static void print(const char* format, bool newline, ...);
        static void flushUart(){ pUart_->flush(); }

    private:
        static Uart::IUart* pUart_;

        const static uint16_t MAX_STRING_LENGTH = 255;
        static char outputStr[];

        static void parseArguement(char* ouputStr, va_list* pList, const char* selectorStr);
};

#endif