#ifndef COMMAND_INTERFACE_HPP
#define COMMAND_INTERFACE_HPP

#include "drivers/serial/ISerial.hpp"

namespace Cli
{
    const static uint16_t MAX_LINE_LENGTH = 64;
    const static uint16_t MAX_NUM_PARAMS = 8;

    typedef char* ArgV[MAX_NUM_PARAMS];

    struct Command
    {
        const char* name;
        void (*function)(uint16_t, ArgV);
    };

    enum class CommandError : uint8_t
    {
        INVALID_VALUE,
        INVALID_NUM_PARAMS
    };

    class CommandInterface
    {
        public:
            CommandInterface(SerialComm::ISerial* pUart,
                             const Command* commands,
                             uint16_t numCommands);

            void enable();

            void disable();

            void update();

            static void printError(CommandError error);

        private:
            static char inputBuffer_[MAX_LINE_LENGTH];

            SerialComm::ISerial* pSerial_;
            const Command* commands_;
            uint16_t numCommands_;

            uint16_t bufferIndex_;
            bool enabled_;

            void parseInputs();

            void execute(uint16_t argc, ArgV argv);
    };
}

#endif