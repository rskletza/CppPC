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

    std::cout << "(";
    std::for_each(first, last, [](value_t &n){
	    std::cout <<" "<< n;
	    });
    std::cout << ")\n";

    std::unordered_map<value_t, size_t> aux;
//    std::for_each(first, last, [&aux](value_t &n){
//	if(aux.find(n) == aux.end())
//	    aux.insert({n, std::count(first, last, n)});
//	else
//	    
//	    })
    std::remove_if(first, last, [&aux, first, last](value_t &n){
	if(aux.find(n) == aux.end())
	{
	    aux.insert({n, std::count(first, last, n)});
	    std::cout << "new element " << n <<"\n";
	    return false;
	}
	std::cout << "remove element " << n << "\n";
	return true; 
    });

    for(const auto& n : aux)
    {
	std::cout << n.first << ":" << n.second << ", ";
    }
    std::cout << "\n";

    std::cout << "(";
    std::for_each(first, last, [](value_t &n){
	    std::cout <<" "<< n;
	    });
    std::cout << ")\n";

    return first;
}

#endif // CPPPC__S03__HISTOGRAM_H__INCLUDED
