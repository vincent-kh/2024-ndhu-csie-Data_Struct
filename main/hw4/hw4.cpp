#include <iostream>
#include <vector>

template <typename T>
T sum(const std::vector<T>& v) 
{
    T total = 0;
    for(auto it = v.begin(); it != v.end(); ++it) {
        total += *it;
    }
    return total;
}

int main() {
    std::vector<int> intVec = {1, 2, 3, 4, 5};
    std::cout << "Sum of intVec: " << sum(intVec) << std::endl;

    std::vector<double> doubleVec = {1.5, 2.5, 3.5};
    std::cout << "Sum of doubleVec: " << sum(doubleVec) << std::endl;

    std::vector<long> longVec = {100000L, 200000L, 300000L};
    std::cout << "Sum of longVec: " << sum(longVec) << std::endl;

    return 0;
}