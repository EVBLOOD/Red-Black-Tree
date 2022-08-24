/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:53:44 by sakllam           #+#    #+#             */
/*   Updated: 2022/08/24 22:09:37 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "red_black_body.hpp"

int main()
{
    ft::RBT<int> x;

    x.insert(10);
    x.insert(5);
    x.insert(20);
    x.insert(15);
    x.insert(16);
    x.insert(12);
    x.insert(11);
    x.insert(19);
    x.insert(18);
    x.insert(17);
    x.insert(50);
    x.insert(32);
    x.insert(64);
    x.insert(8);
    x.insert(51);
    x.insert(52);
    x.insert(40);
    x.insert(45);
    x.insert(0);
    x.insert(21);
    x.insert(13);
    x.insert(37);
    x.printing();
}