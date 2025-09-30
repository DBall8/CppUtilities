#ifndef CONVERSIONS_HPP
#define CONVERSIONS_HPP

#include <stdint.h>

const static int ADC_MAX = 1024;
const static float VOLT_MAX = 5.0f;

const static float C_TO_F_MULTIPLIER = 9.0f/5.0f;
const static float C_TO_F_OFFSET = 32;

const static float MAX_PERCENT_WHOLE = 100.0f;

float convertAdcToVoltage(int adc);
float degreesCToF(float degreesC);
float degreesFToC(float degreesF);
int32_t round(float value);
int32_t exp(int32_t value, int8_t exponent);
#endif