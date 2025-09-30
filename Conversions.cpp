#include "Conversions.hpp"

float convertAdcToVoltage(int adc){
    return ((float)adc / (float)ADC_MAX) * VOLT_MAX;
}

float degreesCToF(float degreesC) { return degreesC * C_TO_F_MULTIPLIER + C_TO_F_OFFSET; }
float degreesFToC(float degreesF) { return (degreesF - C_TO_F_OFFSET) / C_TO_F_MULTIPLIER; }

int32_t round(float value)
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

int32_t exp(int32_t value, int8_t exponent)
{
    int32_t finalValue = 1;
    for (int i=0; i<exponent; i++)
    {
        finalValue *= value;
    }
    return finalValue;
}