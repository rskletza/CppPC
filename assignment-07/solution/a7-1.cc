#include <vector>
#include <array>
#include <iterator>
#include <cmath>
#include <iostream>
#include <unordered_set>

//the google example has a complexity of O(n), so my example has the same average case complexity but is vastly better to parallelize

template<class BiIt>
bool hasSum(BiIt front, BiIt end, int sum)
{
    --end;
    while (front != end)
    {
        auto tmp = *front + *end;
        std::cout << "front: " << *front << ", end: " << *end << ", sum: " << tmp << "\n";
        if (tmp == sum)
            return true;
        if (tmp > sum)
            --end;
        else 
            ++front;
    }
    return false;
}

    //average case complexity (without parallelization): n+1+n = 2n + 1 = O(n)
    //worst case complexity (without parallelization): n^2 + 2n + n^2 = O(n^2 + n)
template<class BiIt>
bool hasSumUnordered(BiIt front, BiIt end, int sum)
{
//    std::cout << "sum: " << sum << "\n";
    //fill an unordered multiset (elements can exist several times)
    //can be parallelized
    //complexity n (average case), n^2 (worst case)
    auto complements = std::unordered_multiset<int>(); //TODO make type T, use unordered set to avoid a huge set if there are many duplicates
    for (auto it = front;it != end; ++it)
    {
        complements.insert(*it);
    }

    //check if there are two equal elements that each equal exactly half of the sum
    //complexity 1 (average), 2n (worst case)
    auto half = complements.find(sum/2);
    if( half != complements.end())
    {
        if(complements.count(*half) > 1)
        {
//            std::cout << "count of half: " << complements.count(*half) << "\n";
//            std::cout << "sum of: " << *half <<", " << *half << "\n";
            return true;
    
        }
        //make sure half is not incorrectly found later
        else
            complements.erase(*half);
    }

    //iterate over every element and see if its complement is in the map
    //can be parallelized
    //complexity: n (average), n^2 (worst)
    for (auto it = front; it != end; ++it)
    {
        if (complements.find(sum - *it) != complements.end())
        {

//           std::cout << "sum of: " << *complements.find(sum - *it) <<", " << *it << "\n";
            return true;
        }
    }

    return false;
}

int main()
{
//    std::vector<int> v1{ 1,2,3,9 };
//    std::vector<int> v2{ 1,2,4,4 };
//    std::array<int,9> a1{ 1,2,3,5,5,6,7,8,9};
//    std::array<int,8> a2{ 1,1,1,9,9,9,10,11 };
//
//
//    std::cout << "v1: " << hassum(v1.begin(), v1.end(), 8) << "\n";
//    std::cout << "v2: " << hassum(v2.begin(), v2.end(), 8) << "\n";
//    std::cout << "a1: " << hassum(a1.begin(), a1.end(), 13) << "\n";
//    std::cout << "a2: " << hassum(a2.begin(), a2.end(), 13) << "\n";
    
    std::vector<int> v1{ 1,3,5,2,4,6,3,5,2};
    std::vector<int> v2{ 5,3,6,8,4,2,3,6,8,4,1};
    std::vector<int> v3{ 5,2,6,3,5,2};
    std::vector<int> v4{ 5,2,6,3,3,5,2};
    std::vector<int> v5{ 6,8,3,6,8,4,1};
    std::array<int,9> a1{ 1,2,3,5,5,6,7,8,9};
    std::array<int,10> a2{ 4,5,5,43,2,4,6,77,5,3 };
    std::array<int,8> a3{ 4,5,43,2,4,6,77,3 };


    std::cout << "v1 (1): " << hasSumUnordered(v1.begin(), v1.end(), 8) << "\n";
    std::cout << "v2 (1): " << hasSumUnordered(v2.begin(), v2.end(), 8) << "\n";
    std::cout << "v3 (0): " << hasSumUnordered(v3.begin(), v3.end(), 6) << "\n";
    std::cout << "v4 (1): " << hasSumUnordered(v4.begin(), v4.end(), 6) << "\n";
    std::cout << "v5 (0): " << hasSumUnordered(v5.begin(), v5.end(), 8) << "\n";
    std::cout << "a1 (1): " << hasSumUnordered(a1.begin(), a1.end(), 13) << "\n";
    std::cout << "a2 (0): " << hasSumUnordered(a2.begin(), a2.end(), 44) << "\n";
    std::cout << "a3 (1): " << hasSumUnordered(a3.begin(), a3.end(), 10) << "\n";
}

