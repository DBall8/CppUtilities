#ifndef AVERAGE_FILTER_HPP
#define AVERAGE_FILTER_HPP

#include "utilities/filter/Filter.hpp"
#include <stdint.h>

namespace Filter
{
  class AverageFilter: public IFilter
  {
    private:
      uint32_t* samples;
      int filterSize;
      int valueInt;
      float valueFloat;

    public:
      AverageFilter(int filterSize);
      ~AverageFilter();

      int getSize();
      void addSample(int sample) override;
      int getValueInt() override;
      void addSample(float sample) override;
      float getValueFloat() override;
  };
}
#endif
