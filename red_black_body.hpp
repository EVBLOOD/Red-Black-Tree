/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_body.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 18:06:02 by sakllam           #+#    #+#             */
/*   Updated: 2022/08/23 10:42:43 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cstdlib>
#include <memory>
#include <sys/_types/_size_t.h>
#define red true
#define black false
#define root 1
#define l 2
#define r 3
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
        int           position;
        bool          color; // red == true; black == false
        RedBlackTree() : value(type_name()), left(NULL), right(NULL), parent(NULL), color(red) {}
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
        size_amount             size;
        
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
        void    recoloring(RedBlackTree<type_name> *paint)
        {
            do {
                if (paint->left)
                    paint->left->color = !(paint->left->color);
                if (paint->right)
                    paint->right->color = !(paint->right->color);
                if (paint->parent->color == root)
                    break;
                paint->parent->color = !(paint->parent->color);
                paint->parent = paint->parent->parent;
            }
            while (1);
        }
        // void retation
        void    insert(RedBlackTree<type_name> **head, RedBlackTree<type_name> *nv, int position)
        {
            if (*head == NULL)
            {
                *head = nv;
                nv->position = position;
                if (!size)
                    nv->color = black;
                return;
            }
            if (cmpr(nv->value, (*head)->value))
                insert(&((*head)->left), nv, r);
            else
                insert(&((*head)->right), nv, l);
            if ((*head)->left)
                (*head)->left->parent = *head;
            if ((*head)->right)
                (*head)->right->parent = *head;
            if ((*head)->color == red)
            {
               if (position == r)
               {
                   if ((*head)->parent->left && (*head)->parent->left->color == red)
                        recoloring((*head)->parent);
                   else
                        rotation((*head)->parent);
               }
               else
               {
                    if ((*head)->parent->left && (*head)->parent->left->color == red)
                        recoloring((*head)->parent);
                    else
                        rotation((*head)->parent);
               }
            }
        }
        public:
            RBT() : head(NULL), size(0) {}
            void insert(type_name value)
            {
                insert(&head, newnode(value), root);
                size++;
            }
    };
}