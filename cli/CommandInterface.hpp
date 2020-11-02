#ifndef COMMAND_INTERFACE_HPP
#define COMMAND_INTERFACE_HPP

#include "drivers/uart/IUart.hpp"

namespace Cli
{
    const static uint16_t MAX_LINE_LENGTH = 64;
    const static uint16_t MAX_PARAM_LENGTH = 32;
    const static uint16_t MAX_NUM_PARAMS = 12;

    typedef char CliParam[MAX_PARAM_LENGTH];
    typedef CliParam ArgV[MAX_NUM_PARAMS];

    struct Command
    {
        const char* name;
        void (*function)(uint16_t, ArgV);
    };

    class CommandInterface
    {
        public:
            CommandInterface(Uart::IUart* pUart,
                             Command* commands,
                             uint16_t numCommands);

            void enable();

            void disable();

            void update();

        private:
            static char inputBuffer_[MAX_LINE_LENGTH];

            Uart::IUart* pUart_;
            Command* commands_;
            uint16_t numCommands_;

            uint16_t bufferIndex_;
            bool enabled_;

            void parseInputs();

            void execute(uint16_t argc, ArgV argv);
    };
}

#endif