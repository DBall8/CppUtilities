#include "LowPassFilter.hpp"

namespace Filter
{

  LowPassFilter::LowPassFilter(int filterSize, float initialValue)
  {
    this->filterSize_ = filterSize;
    this->value = initialValue;
    this->alpha_ = ((float)filterSize_ - 1.0f) / (float)filterSize_;
  }

  LowPassFilter::~LowPassFilter()
  {
  }

  int LowPassFilter::getSize(){ return filterSize_; } 

  void LowPassFilter::addSample(int sample)
  {
    addSample((float)sample);
  }

  int LowPassFilter::getValueInt()
  {
    return (int)value;    
  }

  void LowPassFilter::addSample(float sample)
  {
    float prev = value * alpha_;
    float next = (1.0f - alpha_) * sample;
    value = prev + next;
  }

  float LowPassFilter::getValueFloat()
  {
    return value;    
  }
}
