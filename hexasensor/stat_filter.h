#ifndef STAT_FILTER_H
#define STAT_FILTER_H

/*==============================================================================

Stat_Filter
author: Ethan Lew

Stat_Filter is descriptive statistics filter class implemented in templates. It
is used to filter noisy sensor data.

==============================================================================*/

template <typename T, int N>
class Stat_Filter
{
public:
  Stat_Filter();
  Stat_Filter(T);

  void add_reading(T);

  T get_mean();
  T get_range();

private:
  T data[N];
  int idx;
};

#endif
