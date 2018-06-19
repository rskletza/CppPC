//compares lhs.first with rhs.first and lhs.second with rhs.second
//--> comparison is dependent on the types A and B of pair<A,B>
//
//in order to specify comparison between pair<A0,B0> and pair<A1,B1>, comparisons between elements of type A0 and A1, and B0 and B1 need to be defined
//
//my first thought would be that the difference between pair.first vs std::get is that the former is member access whereas the latter is a function
//get returns a reference, but this doesn't help in the case below
//looking into the compiler explorer, get requires more operations, however:
//it calls tuple_element --> provides compile-time indexed access to the types of the elements of the tuple
//  call std::tuple_element<
//                          0ul, 
//                          std::pair<
//                              int, 
//                              std::__cxx11::basic_string<..> 
//                          > 
//                         >::type& std::get<
//                              0ul, 
//                              int, 
//                              std::__cxx11::basic_string<...> 
//                         >(std::pair<int, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >&)
//
//Why don't we always use std::get?
//good question. Maybe because it takes more operations and an extra function call which makes it less performant?

#include <utility>
#include <string>
#include <iostream>
#include <vector>
#include <iterator>

template<class T>
void printpair(T pair)
{
    std::cout << "first: " << pair.first << " , second: " << pair.second ;
}

namespace std
{
    template <class Iter,
              class = typename std::iterator_traits<Iter>::iterator_category>
    pair<Iter, int> make_pair<Iter,int>(Iter && it, int offset)
    {
        cout << "specialized make_pair";
        return pair<Iter, int>(it, offset);
    }

    template <class Iter,
              class = typename std::iterator_traits<Iter>::iterator_category>
    decltype(auto) begin(pair<Iter,int> p)
    {
        return std::get<0>(p);
    }

    template <class Iter,
              class = typename std::iterator_traits<Iter>::iterator_category>
    decltype(auto) end(pair<Iter,int> p)
    {
        return std::advance(std::get<0>(p), std::get<1>(p));
    }
}

int main()
{
    std::vector<std::string> v {"Monday", "Tuesday", "Wednesday", "Thursday", "Brainfryday", "Saturday", "Sunday"};

    auto range = std::make_pair(v.begin(), 6);

    for (const auto & value : range) 
    {
        std::cout << value << "\n";
    }
//    std::vector<std::pair<int,std::string>> v1;
//    v1.push_back(std::make_pair(1,"hello"));
//    v1.push_back(std::make_pair(1,"hello"));
//    v1.push_back(std::pair<int,std::string>(2,"world"));
//    v1.push_back(std::pair<int,std::string>(0,"world"));
//
//    std::pair<int,std::string> p(0,"world");
//
//    std::cout << p.first << std::get<0>(p);
//        
//    for(auto e : v1)
//    {
//        printpair(e);
//        std::cout << "\n";
//    }

    

//    for(int i = 0; i<v1.size()-1; ++i)
//    {
//        std::cout << "pair " << i << " ";
//        if(v1[i] == v1[i+1])
//            std::cout << "==";
//        if(v1[i] > v1[i+1])
//            std::cout << ">";
//        if(v1[i] < v1[i+1])
//            std::cout << "<";
//
//        std::cout << " pair " << i+1;
//        std::cout << "\n";
//    }
}
