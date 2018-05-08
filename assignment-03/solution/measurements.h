#ifndef CPPPC__A03__MEASUREMENTS_H__INCLUDED
#define CPPPC__A03__MEASUREMENTS_H__INCLUDED

#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <algorithm>

namespace cpppc {

template <typename T>
class Measurements
{

  typedef Measurements<T>                                   self_t;
  typedef T                                                value_t;

  typedef       T &                                      reference;
  typedef const T &                                const_reference;
  typedef typename std::vector<T>::iterator               iterator;
  typedef typename std::vector<T>::const_iterator   const_iterator;

public:

  // YOUR IMPLEMENTATION HERE
  Measurements<value_t>() = default;

  bool operator==(const self_t & other) const
  {
      if (this == &other)
	  return true;
      else if (size() != other.size())
	  return false;
      else if (size() != 0)
      {
	  for (int i = 0; i < size(); ++i)
	  {
	      if ((*this)[i] != other[i])
		      return false;
	  }
      }
     
      return true;
  }

  bool operator!=(const self_t & other) const
  {
      return !(*this == other);
  }

  //insert(T), insert(iterator, iterator)
  void insert(const value_t val)
  {
      _values.push_back(val);
  }

  void insert(const_iterator first, const_iterator last)
  {
      _values.insert(_values.end(), first, last);
  }
  
  //operator[]
  const_reference operator[](size_t index) const
  {
      return _values[index];
  }

  reference operator[](size_t index)
  {
      return _values[index];
  }

  //size
  size_t size() const
  {
      return _values.size();
  }

  //end
  iterator end()
  {
      return _values.end();
  }

  //begin
  iterator begin()
  {
      return _values.begin();
  }
  
  //empty
  bool empty() const
  {
      return _values.empty();
  }

  //front
  const_reference front()
  {
      return _values.front();
  }

  //back
  const_reference back()
  {
      return _values.back();
  }

  //clear
  void clear()
  {
      _values.clear();
  }

  //mean
  double mean() const
  {
      if (empty())
	  return 0.0;

      double sum = 0.0;
      for (size_t i = 0; i<size(); ++i)
      {
	  sum += (*this)[i];
      }
      return (sum / size());
  }

  //median
  double median() const
  {
      if (empty())
	  return 0.0;
      std::vector<value_t> aux = _values;
      std::sort(aux.begin(),aux.end());

      if(size()%2 != 0)
	  return (aux[size()/2]);
      else
	  return ((aux[size()/2] + aux[(size()/2) + 1]) / 2);
  }

  //variance
  double variance() const
  {
      if (empty())
	  return 0.0;

      double sum = 0.0;
      double mn = mean();

      for (size_t i = 0; i<size(); ++i)
      {
	  sum+= pow(((*this)[i]-mn), 2);
      }

      return (sum / size());
  }
  
  //sigma
  double sigma() const
  {
      return sqrt(variance());
  }

private:

  std::vector<T> _values;

};

} // namespace cpppc

#endif // CPPPC__A03__MEASUREMENTS_H__INCLUDED
