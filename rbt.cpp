/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:53:44 by sakllam           #+#    #+#             */
/*   Updated: 2022/08/23 22:32:46 by sakllam          ###   ########.fr       */
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
    x.insert(17);
    // x.insert(15);
    x.printing();
}