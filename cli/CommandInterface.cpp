#include "CommandInterface.hpp"

#include "utilities/strings/Strings.hpp"
#include "utilities/print/Print.hpp"

using namespace Serial;
using namespace Strings;

const char NEWLINE = '\n';
const char CR = '\r';

namespace Cli
{
    char CommandInterface::inputBuffer_[MAX_LINE_LENGTH];

    CommandInterface::CommandInterface(ISerial* pSerial,
                                       Command* commands,
                                       uint16_t numCommands):
        pSerial_(pSerial),
        commands_(commands),
        numCommands_(numCommands),
        bufferIndex_(0),
        enabled_(false)
    {

    }

    void CommandInterface::enable()
    {
        enabled_ = true;
    }

    void CommandInterface::disable()
    {
        enabled_ = false;
    }

    void CommandInterface::update()
    {
        if (!enabled_) return;

        if (pSerial_->isDataAvailable())
        {
            uint16_t remainingSpace = MAX_LINE_LENGTH - bufferIndex_;
            uint8_t* nextBuffPos = (uint8_t*)&(inputBuffer_[bufferIndex_]);

            uint16_t bytesReceived = pSerial_->read(nextBuffPos, remainingSpace);
            bufferIndex_ += bytesReceived;

            parseInputs();
        }
    }

    void CommandInterface::parseInputs()
    {
        uint16_t lineEndIndex = 0;
        for (uint16_t i=0; i< bufferIndex_; i++)
        {
            if (inputBuffer_[i] == NEWLINE)
            {
                lineEndIndex = i;
                break;
            }
        }

        if (lineEndIndex > 0)
        {
            inputBuffer_[lineEndIndex] = '\0';
            ArgV argv;
            uint16_t argc = 0;
            
            char* token = strtok(inputBuffer_, ' ');

            if (token != nullptr)
            {
                do{
                    if (argc >= MAX_NUM_PARAMS) break;

                    // Remove any trailing CR
                    uint16_t tokenLength = strlen(token);
                    if (token[tokenLength - 1] == '\r')
                    {
                        token[tokenLength - 1] = '\0';
                    }
                    
                    strncpy(argv[argc], token, MAX_PARAM_LENGTH);
                    argc++;
                } while((token = strtok(nullptr, ' ')) != nullptr);
            }

            if (lineEndIndex < bufferIndex_)
            {
                // More data in the buffer, move it to the front
                // (Plus 1 is to not copy the newline)
                uint16_t numRemainingBytes = bufferIndex_ - lineEndIndex - 1;
                copy(inputBuffer_, &(inputBuffer_[lineEndIndex + 1]), numRemainingBytes);
                bufferIndex_ = numRemainingBytes;
            }
            else
            {
                bufferIndex_ = 0;
            }

            if (argc > 0)
            {
                execute(argc, argv);
            }
        }
    }

    void CommandInterface::execute(uint16_t argc, ArgV argv)
    {
        if (argc <= 0) return;

        const char* commandName = argv[0];

        for (uint16_t i=0; i<numCommands_; i++)
        {
            if (strcompare(commandName, commands_[i].name))
            {
                commands_[i].function(argc, argv);
                return;
            }
        }

        PRINTLN("Command not supported.");
    }
}