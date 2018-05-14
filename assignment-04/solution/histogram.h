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
    if (first = last)
	return first;

    set<value_t> aux;
    std::copy(first, last, aux.first, aux.last);
    
//    bool isfirst = true;
//    int occurs = 0;
//    std::for_each(first, last, [&isfirst, &occurs](value_t &n){
//	++occurs;
//	if (isfirst)
//	    isfirst = false;
//	else
//	    }
}

#endif // CPPPC__S03__HISTOGRAM_H__INCLUDED
