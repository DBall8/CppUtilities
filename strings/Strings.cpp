#include "Strings.hpp"
#include "utilities/Conversions.hpp"

namespace StringUtilities
{
    uint8_t ZERO_VAL = (uint8_t)'0';
    uint8_t A_VAL = (uint8_t)'A';
    uint8_t MAX_NUMERICAL_DIGIT = 10;

    uint32_t strlen(const char* str)
    {
        uint32_t counter = 0;
        while (str[counter] != '\0')
        {
            counter++;
        }

        return counter;
    }

    char* strncpy(char* dest, const char* src, uint32_t num)
    {
        for (uint32_t i=0; i<num; i++)
        {
            dest[i] = src[i];
            if (src[i] == '\0')
            {
                break;
            }
        }

        return dest;
    }

    char* strnconcat(char* dest, const char* src, uint32_t num)
    {
        uint32_t startIndex = strlen(dest);
        for (uint32_t i=0; i<num; i++)
        {
            dest[i+startIndex] = src[i];
            if (src[i] == '\0')
            {
                break;
            }
        }

        return dest;
    }

    char* int2str(int integer, char* dest, uint16_t maxLength, uint8_t base)
    {
        uint32_t index = 0;
        bool negative = false;

        if ((integer < 0) && (base <= MAX_NUMERICAL_DIGIT))
        {
            negative = true;
            integer *= -1;
        }

        do
        {
            uint8_t nextVal = (integer % base);
            if (nextVal < MAX_NUMERICAL_DIGIT)
            {
                // Falls with 0-9, use one of those characters
                dest[index++] = (char)(nextVal + ZERO_VAL);
            }
            else
            {
                // Digit is greater than 9, use an alpha digit instead
                nextVal -= MAX_NUMERICAL_DIGIT;
                dest[index++] = (char)(nextVal + A_VAL);
            }
            integer /= base;
        } while ((integer != 0) && (index < maxLength));

        if (negative)
        {
            dest[index++] = '-';
        }

        dest[index] = '\0';

        reverse(dest);
        return dest;
    }

    char* uint2str(unsigned int integer, char* dest, uint16_t maxLength, uint8_t base)
    {
        uint32_t index = 0;

        do
        {
            uint8_t nextVal = (integer % base);
            if (nextVal < MAX_NUMERICAL_DIGIT)
            {
                // Falls with 0-9, use one of those characters
                dest[index++] = (char)(nextVal + ZERO_VAL);
            }
            else
            {
                // Digit is greater than 9, use an alpha digit instead
                nextVal -= MAX_NUMERICAL_DIGIT;
                dest[index++] = (char)(nextVal + A_VAL);
            }
            integer /= base;
        } while ((integer != 0) && (index < maxLength));

        dest[index] = '\0';

        reverse(dest);
        return dest;
    }

    char* bin2str(unsigned int integer, char* dest, uint8_t numPlaces)
    {
        for (uint8_t i=0; i<numPlaces; i++)
        {
            dest[i] = ((integer >> (numPlaces-i-1)) & 0x1) ? '1' : '0';
        }

        // uint8_t index = 0;

        // do
        // {
        //     dest[index++] = (integer & 0x1) ? '1' : '0';
        //     integer = integer >> 1;
        // } while (integer != 0);
        
        dest[numPlaces] = '\0';

        return dest;
    }

    char* float2str(float value, char* dest, uint16_t maxLength, uint8_t numDecimalPlaces)
    {
        // Place the string for the whole number portion into the string buffer
        int32_t wholeValue = (int32_t)value;
        int2str(wholeValue, dest, maxLength);

        // Move the current operating string to the end of the whole value string
        uint16_t strLength = strlen(dest);
        char* decimalStr = &(dest[strLength]);

        if (strLength >= maxLength) return dest;

        // Make positive, since we would have already written a negative sign in int2str
        if (value < 0) value *= -1.0f;

        // Write the decimal place
        decimalStr[0] = '.';

        uint16_t i = 1;
        while ((i <= numDecimalPlaces) &&
               (strLength < maxLength-1))   // Leave space for null terminator
        {
            uint32_t multiplier = exp(10, i);
            uint32_t digit = (uint32_t)(value * multiplier) % 10;
            decimalStr[i] = (char)(digit + ZERO_VAL);

            i++;
            strLength++;
        }

        decimalStr[numDecimalPlaces+1] = '\0';

        return dest;
    }

    void reverse(char* str)
    {
        uint32_t length = strlen(str);
        for (uint32_t i=0; i<length/2; i++)
        {
            char temp = str[i];
            str[i] = str[length-i-1];
            str[length-i-1] = temp;
        }
    }

    bool isValidInteger(char charVal)
    {
        uint8_t intVal = charVal - ZERO_VAL;
        return (intVal >= 0) && (intVal < 9);
    }

    uint8_t charToInt(char charVal)
    {
        if (!isValidInteger(charVal))
        {
            return 0;
        }
        return charVal - ZERO_VAL;
    }

    void copy(char* dest, const char* src, uint16_t numBytes)
    {
        while (numBytes > 0)
        {
            *dest = *src;
            dest++;
            src++;
            numBytes--;
        }
    }

    static char* lastPosition;
    char* strtok(char* str, char delimeter)
    {
        // Use last successful call to strtok's string if input was nullptr
        if (str == nullptr)
        {
            if (lastPosition == nullptr) return nullptr; // No string saved
            str = lastPosition + 1;
        }

        char* strStart = str;

        while (*str != '\0')
        {
            if (*str == delimeter)
            {
                *str = '\0';
                lastPosition = str;
                return strStart;
            }

            str++;
        }

        lastPosition = nullptr;
        return strStart;
    }

    bool strcompare(const char* str1, const char* str2)
    {
        while ((*str1 != '\0') && (*str2 != '\0'))
        {
            if (*str1 != *str2)
            {
                return false;
            }

            str1++;
            str2++;
        }

        if ((*str1 == '\0') && (*str2 == '\0'))
        {
            return true;
        }

        return false;
    }

    int32_t str2int(const char* str)
    {
        int32_t value = 0;
        bool isNegative = (str[0] == '-');

        if (isNegative) str++;

        while (isDigit(*str))
        {
            value *= 10;
            value += *str - ZERO_VAL;
            str++;
        }

        if (isNegative) value *= -1;

        return value;
    }

    float str2float(const char* str)
    {
        float value = 0;
        bool isNegative = (str[0] == '-');

        if (isNegative) str++;

        while (isDigit(*str))
        {
            value *= 10;
            value += *str - ZERO_VAL;
            str++;
        }

        if (*str != '.')
        {
            // Non-digit and non decimal value encountered, end parsing
            if (isNegative) value *= -1;
            return value;
        }

        // Skip the decimal point
        str++;

        // Determine the length of the remaining value string
        uint16_t decimalLength = strlen(str);
        float decimalValue = 0;

        // Parse the decimal portion separately
        for (int16_t i=(decimalLength-1); i>=0; i--)
        {
            decimalValue += (float)(str[i] - ZERO_VAL);
            decimalValue /= 10;
           
        }
        
        // Add the decimal value to the whole value
        value += decimalValue;

        if (isNegative) value *= -1;

        return value;
    }

    bool isDigit(char c)
    {
        uint32_t digitVal = c - ZERO_VAL;
        return (digitVal >= 0) && (digitVal <= 9);
    }

    bool isWhitespace(char c)
    {
        return (c == ' ') ||
               (c == '\r') ||
               (c == '\t') ||
               (c == '\n');
    }

    void trim(char* str)
    {
        if (str == nullptr) return;
        if (*str == '\0') return;
        
        char* lastChar = str;
        while (*str != '\0')
        {
            if (!isWhitespace(*str))
            {
                lastChar = str;
            }
            str++;
        }

        lastChar++;
        *lastChar = '\0';
    }
}