#ifndef FILTER_HPP
#define FILTER_HPP

namespace filter
{
  class Filter
  {
    public:
      Filter(){};
      ~Filter(){};

      virtual void addSample(int sample) = 0;
      virtual int getValueInt() = 0;

      virtual void addSample(float sample) = 0;
      virtual float getValueFloat() = 0;
  };
}
#endif
