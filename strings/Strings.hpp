#ifndef STRINGS_HPP
#define STRINGS_HPP

#include <stdint.h>

namespace Strings
{
    uint32_t strlen(const char* str);
    char* strncpy(char* dest, const char* src, uint32_t num);
    char* strnconcat(char* dest, const char* src, uint32_t num);
    char* int2str(int integer, char* dest, uint16_t maxLength, uint8_t base = 10);
    char* uint2str(unsigned int integer, char* dest, uint16_t maxLength, uint8_t base = 10);
    char* bin2str(unsigned int integer, char* dest, uint8_t numPlaces);
    char* float2str(float value, char* dest, uint16_t maxLength, uint8_t numDecimalPlaces = 2);
    void reverse(char* str);
    bool isValidInteger(char charVal);
    uint8_t charToInt(char charVal);
    void copy(char* dest, const char* src, uint16_t numBytes);
    char* strtok(char* str, char delimeter);
    bool strcompare(const char* str1, const char* str2);
    int32_t str2int(const char* str);
    float str2float(const char* str);
    bool isDigit(char c);
}

#endif