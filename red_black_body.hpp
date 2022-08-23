/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_body.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 18:06:02 by sakllam           #+#    #+#             */
/*   Updated: 2022/08/23 11:48:47 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cstdlib>
#include <memory>
#include <sys/_types/_size_t.h>
#include <iostream>
#define red true
#define black false
#define rt 1
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
            newnode->color = red;
            return newnode;
        }
        size_amount max(size_amount a, size_amount b)
        {
            if (a > b)
                return a;
            return b;
        }
        // size_amount hight(RedBlackTree<type_name> *head)
        // {
        //     if (head == NULL)
        //         return 0;
        //     if (head->color == false)
        //         return max(hight(head->color), hight(head->right)) + 1;
        //     return max(hight(head->color), hight(head->right));
        // }
        void    recoloring(RedBlackTree<type_name> *paint)
        {
            do {
                if (paint->left)
                    paint->left->color = !(paint->left->color);
                if (paint->right)
                    paint->right->color = !(paint->right->color);
                if (paint->parent->color == rt)
                    break;
                paint->parent->color = !(paint->parent->color);
                paint->parent = paint->parent->parent;
            }
            while (1);
        }
        void    right_rotation(RedBlackTree<type_name> **root)
        {
            RedBlackTree<type_name> *roottmp = *root;
            *root = (*root)->left;
            RedBlackTree<type_name> *righttmp = (*root)->right;
            (*root)->right = roottmp;
            roottmp->left = righttmp;
            (*root)->color = black;
            (*root)->left->color = red;
            (*root)->right->color = red;
        }
        void    left_rotation(RedBlackTree<type_name> **root)
        {
            RedBlackTree<type_name> *roottmp = *root;
            *root = (*root)->right;
            RedBlackTree<type_name> *righttmp = (*root)->left;
            (*root)->left = roottmp;
            roottmp->right = righttmp;
            (*root)->color = black;
            (*root)->left->color = red;
            (*root)->right->color = red;
        }
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
                insert(&((*head)->right), nv, l);
            else
                insert(&((*head)->left), nv, r);
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
                   {
                        if (((*head)->parent)->right->right)
                            left_rotation(head);
                        else
                        {
                         right_rotation(head);
                         left_rotation(head);
                        }
                   }
               }
               else if (position == l)
               {
                    if ((*head)->parent->left && (*head)->parent->left->color == red)
                        recoloring((*head)->parent);
                    else
                    {
                        if (((*head)->parent)->left->left)
                            right_rotation(head);
                        else
                        {
                            left_rotation(head);
                            right_rotation(head);
                        }
                    }
               }
            }
        }
        void    printing(RedBlackTree<type_name> *root, int level)
        {
            if (!root)
                return;
            std::cout << level << "\t";
            if (root->position == rt)
                std::cout << "position: root ";
            else if (root->position == r)
                std::cout << "position: right ";
            else
                std::cout << "position: left ";
            if (root->color == red)
                std::cout << "color: red ";
            else
                std::cout << "color: black ";
            std::cout << " | the number: " << root->value << "\n";
            printing(root->right, level + 1);
            printing(root->left, level + 1);
        }
        public:
            RBT() : head(NULL), size(0) {}
            void insert(type_name value)
            {
                insert(&head, newnode(value), rt);
                size++;
            }
            void  printing()
            {
                printing(this->head, 0);
            }
    };
}