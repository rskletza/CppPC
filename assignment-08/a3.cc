#include <cmath>
#include <iostream>
#include <iterator>
#include <ctime>
#include <set>
#include <vector>
#include <list>
#include <cstdlib>

//enable_if is_integral
template <class T>
void log10(typename std::enable_if<std::is_integral<T>::value, T>::type x)
{
    std::cout << "it's an int! --> " << std::log10(x) << "\n";
}

//enable_if is_floating_point
template <class T>
void log10(typename std::enable_if<std::is_floating_point<T>::value, T>::type x)
{
    std::cout << "it's a float! --> " << std::log10(sqrt(x)) << "\n";
}

template <class RAIter>
void print_walk(RAIter begin, RAIter end, std::random_access_iterator_tag)
{
    std::cout << "it's a tap dance!\n";
    auto size = end - begin;
    std::set<short> visited;
    while(visited.size() != size)
    {
        int rand = (int) std::rand() % size;
//        std::cout << "rand: " << rand << "\n";
        if (visited.find(rand) == visited.end()) //not visited
        {
            auto it = begin;
            std::advance(it, rand);
            std::cout << *it << "\n";
            visited.insert(rand);
        }
    }
}

template <class InIter>
void print_walk(InIter begin, InIter end, std::input_iterator_tag)
{
    std::cout << "it's an input iterator!\n";
    for (;begin!=end;++begin)
    {
        std::cout << *begin << "\n";
    }
}

template <class BDIter>
void print_walk(BDIter begin, BDIter end, std::bidirectional_iterator_tag)
{
    std::cout << "it's a bidirectional iterator!\n";
    for (--end;end!=begin;--end)
    {
        std::cout << *end<< "\n";
    }
    std::cout << *end << "\n";
}

//why does this have to be at the bottom?
template <class Iter>
void print_walk(Iter begin, Iter end)
{
    print_walk(begin, end, typename std::iterator_traits<Iter>::iterator_category());
}

int main()
{
    //for some reason this is not working?? No compiler errors, no runtime errors and no output
    std::cout << "log10 test" << "\n";
    int a = 1;
    log10(a);
    log10(5.4);
    log10(1);
    log10('a');

    std::srand(std::time(nullptr));
    std::cout << "print_walk test" << "\n";
    std::vector<int> v = {0,1,2,3,4,5,6,7,8,9};
    std::list<int> l = {0,1,2,3,4,5,6,7,8,9};
    print_walk(v.begin(), v.end());
    print_walk(l.begin(), l.end());

    return 0;
}
