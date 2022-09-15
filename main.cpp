#include "red_black_body.hpp"
#include <set>

int main()
{
    ft::RBT<int> name;
    // std::set<int> name;

    for (int i = 0; i < 1000000; i++)
        name.insert(i);
    for (int i = 0; i < 1000000; i++)
    //     // name.erase(i);
        name.remove(i);
}