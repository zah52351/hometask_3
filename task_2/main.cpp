#include "task_2.hpp"
#include <vector>

int main() {
    ForwardList<int> lst(5, 12);
    ForwardList<double> lst2{1,3,6};
    std::vector<int> v{1,2,3};
    //ForwardList<int> lst3(v.begin(), v.end());
    //ForwardList<int> lst4(lst.begin(), lst.end());
    for(auto& c : lst) {
        std::cout << c << '\n';
    }
    
    
    

}