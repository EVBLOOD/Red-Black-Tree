#include "red_black_body.hpp"
#include <iterator>
#include <set>

int main()
{
    ft::RBT<int> name;
    std::map<int, int> name1;

    for (int i = 1; i < 100; i++)
    {
        name.insert(i);
        name1[i] = i;
    }
    // std::map<int, int>::reverse_iterator b = name1.rbegin();
    // std::map<int, int>::reverse_iterator end = name1.rend();
    ft::RedBlackTree<int> *pointer = name.begin();
    ft::RedBlackTree<int> *nav = name._prev(NULL);
    // if ()
    // b--;
        // std::cout << "set shit: " << end->second << std::endl;
    
    // b++
    // std::coty;
    // b--;
    while (1)
    {
        
        std::cout << nav->value << std::endl;
        // if (pointer == nav)
        //     break;
        nav = name._prev(nav);
    }
    // name.printing();
    // for (int i = 0; i < 1000000; i++)
    //     name.erase(i);
        // name.remove(i);
}