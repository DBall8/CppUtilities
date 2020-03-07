#ifndef CONVERSIONS_HPP
#define CONVERSIONS_HPP

const static int ADC_MAX = 1024;
const static float VOLT_MAX = 5.0f;

float convertAdcToVoltage(int adc){
    return ((float)adc / (float)ADC_MAX) * VOLT_MAX;
}
#endif