#ifndef LOW_PASS_FILTER_HPP
#define LOW_PASS_FILTER_HPP

#include "filter/Filter.hpp"

namespace FilterSpace
{
  class LowPassFilter: public Filter
  {
    private:
      int filterSize_;
      float value;
      float alpha_;

    public:
      LowPassFilter(int filterSize, float initialValue = 0);
      ~LowPassFilter();

      int getSize();
      void addSample(int sample) override;
      int getValueInt() override;

      void addSample(float sample) override;
      float getValueFloat() override;
  };
}
#endif
