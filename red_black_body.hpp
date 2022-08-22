/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_body.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 18:06:02 by sakllam           #+#    #+#             */
/*   Updated: 2022/08/22 18:34:40 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cstdlib>
#include <memory>
#include <sys/_types/_size_t.h>
namespace ft
{
    template <class T>
        struct RedBlackTree
    {
        typedef T type_name;

        type_name value;
        RedBlackTree *left;
        RedBlackTree *right;
        RedBlackTree *parent;
        bool          color; // red == true; black == false
        RedBlackTree() : value(type_name()), left(NULL), right(NULL), parent(NULL), color(true) {}
    };

    template <class T, class Compare = std::less<T>, class Alloc = std::allocator<RedBlackTree<T> > >
        class RBT
    {
        typedef Alloc   alloc;
        typedef T       type_name;
        typedef Compare cmpfun;
        typedef size_t  size_amount;

        alloc                   ac;
        RedBlackTree<type_name> *head;
        cmpfun                  cmpr;
        
        RedBlackTree<type_name> *newnode(type_name value)
        {
            RedBlackTree<T> *newnode = ac.allocate(1);
            newnode->value = value;
            return newnode;
        }
        size_amount max(size_amount a, size_amount b)
        {
            if (a > b)
                return a;
            return b;
        }
        size_amount hight(RedBlackTree<type_name> *head)
        {
            if (head == NULL)
                return 0;
            if (head->color == false)
                return max(hight(head->color), hight(head->right)) + 1;
            return max(hight(head->color), hight(head->right));
        }
        void    insert(RedBlackTree<type_name> **head, RedBlackTree<type_name> *nv)
        {
            if (*head == NULL)
            {
                *head = nv;
                return;
            }
            if (cmpr(nv->value, (*head)->value))
                insert(&((*head)->left), nv);
            else
                insert(&((*head)->right), nv);
            if (abs(hight((*head)->right) - hight((*head)->right)) > 0)  // check for balencing and colors
            {
                
            }
        }
        public:
            RBT() : head(NULL) {}
            void insert(type_name value)
            {
                insert(&head, newnode(value));
            }
    };
}