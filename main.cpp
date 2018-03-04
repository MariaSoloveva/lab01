#include <algorithm>
#include <iostream>
#include <iterator>
#include <functional>
#include "sort.hpp"

int main()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dis(0, 9);
    std::vector<int> v1(10), v2(10), v3(10), v4(10);
    std::generate(v1.begin(), v1.end(), std::bind(dis, std::ref(mt)));
    std::generate(v2.begin(), v2.end(), std::bind(dis, std::ref(mt)));
    std::generate(v3.begin(), v3.end(), std::bind(dis, std::ref(mt)));
    std::generate(v4.begin(), v4.end(), std::bind(dis, std::ref(mt)));
    std::cout << "v1 : ";
    std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    merge_sort(v1.begin(), v1.end());
    std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    std::cout << "v2 : ";
    std::copy(v2.begin(), v2.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    quick_sort(v2.begin(), v2.end());
    std::copy(v2.begin(), v2.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    std::cout << "v3 : ";
    std::copy(v3.begin(), v3.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    insertion_sort(v3.begin(), v3.end());
    std::copy(v3.begin(), v3.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    std::cout << "v4 : ";
    std::copy(v4.begin(), v4.end(), std::ostream_iterator<int>(std::cout, " "));
    heap_sort(v1.begin(), v1.end());
    std::cout << std::endl;
    std::copy(v4.begin(), v4.end(), std::ostream_iterator<int>(std::cout, " "));
    std::vector<int> sumVec;
    merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(sumVec));
    std::copy(sumVec.begin(), sumVec.end(), std::ostream_iterator<int>(std::cout, " "));
    return 0;
}
