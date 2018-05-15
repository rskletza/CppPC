#ifndef CPPPC__S03__HISTOGRAM_H__INCLUDED
#define CPPPC__S03__HISTOGRAM_H__INCLUDED

// Some headers you might find useful:
#include <unordered_map>
#include <set>
#include <algorithm>
#include <iterator>


template <class Iter>
inline Iter histogram(Iter first, Iter last) {
    typedef typename std::iterator_traits<Iter>::value_type      value_t;
    typedef typename std::iterator_traits<Iter>::difference_type index_t;

    // YOUR IMPLEMENTATION HERE
    //
    if (first == last)
	return first;

    std::unordered_map<value_t, size_t> aux;

    //remove all elements that appear several times and save their count to the map
    //save the pointer to the last new element in order to return it later
    auto ret = std::remove_if(first, last, [&aux, first, last](value_t &n){
	if(aux.find(n) == aux.end())
	{
	    aux.insert({n, std::count(first, last, n)});
	    return false;
	}
	return true; 
    });

    //replace the elements by their count in the original container
    std::for_each(first, ret, [&aux](value_t &n){ n = aux[n]; });

    return ret;
}

#endif // CPPPC__S03__HISTOGRAM_H__INCLUDED
