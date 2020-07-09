#include "Print.hpp"
#include "utilities/strings/Strings.hpp"
#include "drivers/assert/Assert.hpp"

using namespace uart;

const static char* NEWLINE = "\r\n\0";
const static uint8_t NEWLINE_LENGTH = strlen(NEWLINE) + 1;

IUart* PrintHandler::pUart_ = nullptr;
char PrintHandler::outputStr[MAX_STRING_LENGTH];

PrintHandler::PrintHandler(uart::IUart* pUart)
{
    PrintHandler::pUart_ = pUart;
}

void PrintHandler::parseArguement(char* ouputStr, va_list* pList, char* selectorStr)
{
    uint16_t outputLength = strlen(outputStr);
    switch (selectorStr[0])
    {
        case 'd':
        {
            int decVal = va_arg(*pList, int);
            int2str(decVal, &(outputStr[outputLength]));
            break;
        }

        case 'b':
        {
            int binVal = va_arg(*pList, int);
            bin2str(binVal, &(outputStr[outputLength]), 8);
            break;
        }
        
        default:
        {
            // Not actually a selector, so just add to the string
            outputStr[outputLength] = '%';
            outputStr[outputLength+1] = selectorStr[0];
            outputStr[outputLength+2] = '\0';
            break;
        }
    }
}

void PrintHandler::print(const char* format, bool newline, ...)
{
    va_list list;
    va_start(list, newline);

    outputStr[0] = '\0';

    bool selectorFound = false;
    uint16_t currStartIndex = 0;
    uint16_t formatLength = strlen(format);

    for (uint16_t i=0; i<formatLength; i++)
    {
        if (selectorFound)
        {
            parseArguement(outputStr, &list, &format[i]);

            currStartIndex = i+1;
            selectorFound = false;
        }
        else if (format[i] == '%')
        {
            // Add the string so far to the output
            uint16_t length = strlen(outputStr);
            strnconcat(outputStr, &(format[currStartIndex]), (i - currStartIndex));
            outputStr[length + i - currStartIndex] = '\0';
            selectorFound = true;
        }
    }

    if (currStartIndex < formatLength)
    {
        uint16_t length = strlen(outputStr);
        strnconcat(outputStr, &(format[currStartIndex]), (formatLength - currStartIndex));
        outputStr[length + formatLength - currStartIndex] = '\0';
    }

    if (newline)
    {
        strnconcat(outputStr, NEWLINE, NEWLINE_LENGTH);
    }

    uint32_t finalLength = strlen(outputStr);
    assert(finalLength < MAX_STRING_LENGTH, "Print string too long.");

    PrintHandler::pUart_->write((uint8_t*)outputStr, finalLength);

    va_end(list);
}