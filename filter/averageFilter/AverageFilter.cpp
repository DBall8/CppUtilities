#include "AverageFilter.hpp"

namespace Filter
{

  AverageFilter::AverageFilter(int filterSize)
  {
    this->filterSize = filterSize;
    this->valueInt = 0;
    this->valueFloat = 0.0f;
    
    samples = new uint32_t[filterSize];
    for (int i=0; i<filterSize; i++)
    {
      samples[i] = (uint32_t)0;
    }
  }

  AverageFilter::~AverageFilter()
  {
    delete(samples);
  }

  int AverageFilter::getSize(){ return filterSize; } 

  void AverageFilter::addSample(int sample)
  {
    // Shift all values up 1, and accumulate a sum of all current samples
    valueInt = 0;
    for (int i=filterSize-1; i>0; i--)
    {
      samples[i] = samples[i-1];
      valueInt += (int)samples[i];
    }

    // Add sample to filter and to sum
    samples[0] = sample;
    valueInt += sample;

    // Average all samples by dividing sum
    valueInt /= filterSize;
  }

  int AverageFilter::getValueInt()
  {
    return valueInt;    
  }

  void AverageFilter::addSample(float sample)
  {
    // Shift all values up 1, and accumulate a sum of all current samples
    valueFloat = 0;
    for (int i=filterSize-1; i>0; i--)
    {
      samples[i] = samples[i-1];
      valueFloat += (float)samples[i];
    }

    // Add sample to filter and to sum
    samples[0] = sample;
    valueFloat += sample;

    // Average all samples by dividing sum
    valueFloat = valueFloat / filterSize;
  }

  float AverageFilter::getValueFloat()
  {
    return valueFloat;    
  }
}
