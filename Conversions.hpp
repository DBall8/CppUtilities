#ifndef CONVERSIONS_HPP
#define CONVERSIONS_HPP

#include <stdint.h>

const static int ADC_MAX = 1024;
const static float VOLT_MAX = 5.0f;

const static float C_TO_F_MULTIPLIER = 9.0f/5.0f;
const static float C_TO_F_OFFSET = 32;

const static float MAX_PERCENT_WHOLE = 100.0f;

static float convertAdcToVoltage(int adc){
    return ((float)adc / (float)ADC_MAX) * VOLT_MAX;
}

static float degreesCToF(float degreesC) { return degreesC * C_TO_F_MULTIPLIER + C_TO_F_OFFSET; }
static float degreesFToC(float degreesF) { return (degreesF - C_TO_F_OFFSET) / C_TO_F_MULTIPLIER; }
static float abs(float val)
{
    if (val < 0) val *= -1.0f;
    return val;
}

static int32_t round(float value)
{
    if (value >= 0)
    {
        // Positive values
        return (int32_t)(value + 0.5f);
    }
    else
    {
        // Negative values
        return (int32_t)(value + -0.5f);
    }
}

static int32_t exp(int32_t value, int8_t exponent)
{
    int32_t finalValue = 1;
    for (int i=0; i<exponent; i++)
    {
        finalValue *= value;
    }
    return finalValue;
}
#endif