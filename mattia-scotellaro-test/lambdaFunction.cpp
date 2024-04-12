#include <iostream>
#include <vector>
#include <algorithm>
int main()
{
    int num = 3;
    std::vector<int> v = {1, 2, 3, 4};
    std::transform(v.begin(), v.end(), v.begin(), [num] (const int& e) { return e * num; });
    
    for (auto e : v)
        std::cout << e << "\n";

    return 0;
}
