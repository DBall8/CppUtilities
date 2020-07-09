#include "Strings.hpp"

uint8_t ZERO_VAL = (uint8_t)'0';

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

char* int2str(int integer, char* dest)
{
    uint32_t index = 0;
    if (integer < 0)
    {
        dest[index++] = '-';
        integer *= -1;
    }

    do
    {
        dest[index++] = (char)((integer % 10) + ZERO_VAL);
        integer /= 10;
    } while (integer != 0);

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