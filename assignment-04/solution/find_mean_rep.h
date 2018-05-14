#ifndef CPPPC__S03__FIND_MEAN_REP_H__INCLUDED
#define CPPPC__S03__FIND_MEAN_REP_H__INCLUDED

// Some headers you might find useful:
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>

namespace cpppc {

template <class Iter>
Iter find_mean_rep(Iter first, Iter last) {
  typedef typename std::iterator_traits<Iter>::value_type value_t;

  if (first == last)
      return first;

  // YOUR IMPLEMENTATION HERE
  
  float mean = std::accumulate(first, last, 0)/std::distance(first, last);  
  
  value_t closest = *first;
  //search container for element with smallest difference to mean
  //for_each cannot return the value of f --> side effect to change value of closest
  std::for_each(first, last, [mean, &closest](value_t &n){if(std::abs(n-mean) < closest) {closest = n;}});

  //return iterator to the first element with the closest value
  return std::find(first, last, closest);

}

} // namespace cpppc

#endif // CPPPC__S03__FIND_MEAN_REP_H__INCLUDED
