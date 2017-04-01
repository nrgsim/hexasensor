#ifndef STAT_FILTER_CPP
#define STAT_FILTER_CPP

#include "stat_filter.h"

template <typename T, int N>
Stat_Filter<T, N>::Stat_Filter() : idx(0)
{
  for(int i = 0; i < N; i++)
    data[i] = 0;
}

template <typename T, int N>
Stat_Filter<T, N>::Stat_Filter(T init) : idx(0)
{
  for(int i = 0; i < N; i++)
    data[i] = init;
}

template <typename T, int N>
void Stat_Filter<T, N>::add_reading(T read)
{
  data[idx] = read;

  if(idx >= N-1)
    idx = 0;
  else
    idx++;
}

template <typename T, int N>
T Stat_Filter<T, N>::get_mean()
{
  T ans = T(0);
  for(int i = 0; i < N; i++)
    ans += data[i];

  return ans/N;
}

template <typename T, int N>
T Stat_Filter<T, N>::get_range()
{
  T min, max = 0;
  for(int i = 0; i < N; i++)
  {
    if(data[i]> max)
      max = data[i];
    else if (data[i] < min)
      min = data[i];
    else;
  }

  return max-min;
}

template class Stat_Filter<float, 4>;
template class Stat_Filter<float, 8>;

#endif
