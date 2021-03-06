
#include <iostream>
#include "HistInfo.h"

bool operator==(const SpJs::AxisInfo& lhs, const SpJs::AxisInfo& rhs)
{
  return ( (lhs.s_low==rhs.s_low)
            &&(lhs.s_high==rhs.s_high)
            &&(lhs.s_nbins&&rhs.s_nbins));
}

bool operator!=(const SpJs::AxisInfo& lhs, const SpJs::AxisInfo& rhs)
{
  return !(lhs==rhs);
}



bool operator==(const SpJs::HistInfo& lhs, const SpJs::HistInfo& rhs)
{
  bool flag=true;
  flag &= (lhs.s_name == rhs.s_name);
  flag &= (lhs.s_type == rhs.s_type);
  flag &= (lhs.s_params == rhs.s_params);

  size_t lSize = lhs.s_axes.size();
  size_t rSize = rhs.s_axes.size();
  flag &= (lSize == rSize);
  if (lSize!=rSize) {
    return false;
  } else {
    for (size_t i=0; i<lSize; ++i) {
      flag &= (lhs.s_axes.at(i) == rhs.s_axes.at(i));
    }
  }
  flag &= (lhs.s_chanType == rhs.s_chanType);

  return flag;
}

bool operator!=(const SpJs::HistInfo& lhs, const SpJs::HistInfo& rhs)
{
  return !(lhs==rhs);
}
