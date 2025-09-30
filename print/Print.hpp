#ifndef PRINT_HPP
#define PRINT_HPP

#include "drivers/serial/ISerial.hpp"
#include <stdarg.h>

#ifndef NO_PRINT
#define PRINTLN(x, ...) PrintHandler::getInstance().print(x, true, ##__VA_ARGS__)
#define PRINT(x, ...) PrintHandler::getInstance().print(x, false, ##__VA_ARGS__)
#define PRINT_FLUSH() PrintHandler::getInstance().flushUart()

#ifdef DEBUG
#define DEBUG_PRINTLN(x, ...) PrintHandler::getInstance().print(x, true, ##__VA_ARGS__)
#define DEBUG_PRINT(x, ...) PrintHandler::getInstance().print(x, false, ##__VA_ARGS__)
#else
#define DEBUG_PRINTLN(x, ...)
#define DEBUG_PRINT(x, ...)
#endif
#else

// No Prints
#define PRINTLN(x, ...)
#define PRINT(x, ...)
#define PRINT_FLUSH()
#define DEBUG_PRINTLN(x, ...)
#define DEBUG_PRINT(x, ...)
#endif

const static uint16_t MAX_PRINT_LENGTH = 128;

class PrintHandler
{
    public:
        PrintHandler(PrintHandler const&) = delete;
        void operator=(PrintHandler const&) = delete;

        static PrintHandler& getInstance()
        {
            static PrintHandler instance;
            return instance;
        }

        void initialize(SerialComm::ISerial* pSerial);
        void print(const char* format, bool newline, ...);
        void flushUart(){ pSerial_->flush(); }

    private:
        SerialComm::ISerial* pSerial_;

        char outputStr[MAX_PRINT_LENGTH + 1];

        PrintHandler(){};
        void parseArguement(char* ouputStr, va_list* pList, const char* selectorStr);
};

#endif