#ifndef CONVERSIONS_HPP
#define CONVERSIONS_HPP

const static int ADC_MAX = 1024;
const static float VOLT_MAX = 5.0f;

const static float C_TO_F_MULTIPLIER = 9.0f/5.0f;
const static float C_TO_F_OFFSET = 32;

static float convertAdcToVoltage(int adc){
    return ((float)adc / (float)ADC_MAX) * VOLT_MAX;
}

static float degreesCToF(float degreesC) { return degreesC * C_TO_F_MULTIPLIER + C_TO_F_OFFSET; }
static float degreesFToC(float degreesF) { return (degreesF - C_TO_F_OFFSET) / C_TO_F_MULTIPLIER; }
#endif