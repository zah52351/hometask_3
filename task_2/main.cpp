#include <iostream>
#include "task_2.hpp"
#include <vector>

int main () {

    ForwardList<int> lst;
    ForwardList<double> lst2(5);
    ForwardList<std::string> lst3(7, "ss");
    ForwardList<int> lst4 {1,23,15};
    ForwardList<int> lst5(lst4.begin(), lst4.end());
}
