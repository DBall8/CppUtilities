#ifndef STRINGS_HPP
#define STRINGS_HPP

#include <stdint.h>

uint32_t strlen(const char* str);
char* strncpy(char* dest, const char* src, uint32_t num);
char* strnconcat(char* dest, const char* src, uint32_t num);
char* int2str(int integer, char* dest);
char* bin2str(unsigned int integer, char* dest, uint8_t numPlaces);
void reverse(char* str);
bool isValidInteger(char charVal);
uint8_t charToInt(char charVal);

#endif