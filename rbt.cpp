/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:53:44 by sakllam           #+#    #+#             */
/*   Updated: 2022/08/27 20:31:19 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "red_black_body.hpp"
// start : for checker
#include <set>
#include <random>
#include <algorithm>
// end
int main()
{
    ft::RBT<int> x;
    // generating random numbers also {made by: jalalium}
    std::set<int> st;
	srand(time(0));
	while(st.size() < 10)
	{
		st.insert(rand()%100);
	}
	std::vector<int> v(st.begin(), st.end());
	random_shuffle(v.begin(), v.end());
    std::cout << " numbers to insert : \n";	
	for (int z : v)
		std::cout << z << " " ;	
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    for (int z : v)
		x.insert(z); 
    // x.insert(10);
    // x.insert(5);
    // x.insert(20);
    // x.insert(15);
    // x.insert(16);
    // x.insert(12);
    // x.insert(11);
    // x.insert(19);
    // x.insert(18);
    // x.insert(17);
    // x.insert(50);
    // x.insert(32);
    // x.insert(64);
    // x.insert(8);
    // x.insert(51);
    // x.insert(52);
    // x.insert(40);
    // x.insert(45);
    // x.insert(0);
    // x.insert(21);
    // x.insert(13);
    // x.insert(37);
    // x.printing();
    int i = 0;
    for (int z : v)
    {
      if (i == 3)
        break;
		  x.remove(z); 
      // x.printing();
      i++;
    }
      x.printing();
}