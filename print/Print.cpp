#include "Print.hpp"
#include "utilities/strings/Strings.hpp"
#include "drivers/assert/Assert.hpp"

using namespace Serial;
using namespace Strings;

const static char* NEWLINE = "\r\n";
const static uint8_t NEWLINE_LENGTH = strlen(NEWLINE) + 1;

ISerial* PrintHandler::pSerial_ = nullptr;
char PrintHandler::outputStr[MAX_STRING_LENGTH + 1];

void PrintHandler::initialize(Serial::ISerial* pSerial)
{
    PrintHandler::pSerial_ = pSerial;
    // Safety terminator to prevent overflows
    outputStr[MAX_STRING_LENGTH] = '\0';
}

void PrintHandler::parseArguement(char* ouputStr, va_list* pList, const char* selectorStr)
{
    uint16_t outputLength = strlen(outputStr);
    switch (selectorStr[0])
    {
        case 'x':
        case 'X':
        {
            int decVal = va_arg(*pList, int);
            int16_t remainingSpace = MAX_STRING_LENGTH - outputLength;
            uint2str(decVal, &(outputStr[outputLength]), remainingSpace, 16);
            break;
        }

        case 'd':
        {
            int decVal = va_arg(*pList, int);
            int16_t remainingSpace = MAX_STRING_LENGTH - outputLength;
            int2str(decVal, &(outputStr[outputLength]), remainingSpace);
            break;
        }

        case 'u':
        {
            unsigned int decVal = va_arg(*pList, unsigned int);
            int16_t remainingSpace = MAX_STRING_LENGTH - outputLength;
            uint2str(decVal, &(outputStr[outputLength]), remainingSpace);
            break;
        }

        case 'b':
        {
            int binVal = va_arg(*pList, int);
            bin2str(binVal, &(outputStr[outputLength]), 8);
            break;
        }

        case 'f':
        {
            double floatVal = va_arg(*pList, double);
            int16_t remainingSpace = MAX_STRING_LENGTH - outputLength;
            float2str(floatVal, &(outputStr[outputLength]), remainingSpace);
            break;
        }

        case 's':
        {
            // Get the string from the arguement list
            const char* strVal = va_arg(*pList, char*);
            uint16_t strLength = strlen(strVal);

            // Cut string off early if there is not enough space to fit the full string
            int16_t spaceRemaining = MAX_STRING_LENGTH - outputLength;
            if (strLength > spaceRemaining) strLength = spaceRemaining;

            // Copy to output
            copy(&(outputStr[outputLength]), strVal, strLength);
            outputStr[outputLength + strLength] = '\0';
            break;
        }

        case 'c':
        {
            int charVal = va_arg(*pList, int);
            int16_t remainingSpace = MAX_STRING_LENGTH - outputLength;
            if (remainingSpace > 0)
            {
                outputStr[outputLength] = (char)charVal;
                outputStr[outputLength+1] = '\0';
            }
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

    PrintHandler::pSerial_->write((uint8_t*)outputStr, finalLength);

    va_end(list);
}