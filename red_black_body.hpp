/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_body.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 18:06:02 by sakllam           #+#    #+#             */
/*   Updated: 2022/08/23 23:19:49 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cstdio>
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
            // if (paint->left)
            //     paint->left->color = black;
            // if (paint->right)
            //     paint->right->color = black;
            // if (corr->left)
            //     if (corr->left->value == value)
            //     {
            //         corr->left->color = red;
            //         return ;
            //     }
            // if (corr->right)
            //     if (corr->right->value == value)
            //         corr->right->color = red;
            if (paint->position == rt)
                return ;
            // paint->color = !(paint->color);
            recoloring(paint->parent);
        }
        //      void    right_rotation(RedBlackTree<type_name> **root)
        // {
        //     RedBlackTree<type_name> *roottmp = *root;
        //     *root = (*root)->left;
        //     RedBlackTree<type_name> *righttmp = (*root)->right;
        //     (*root)->right = roottmp;
        //     roottmp->left = righttmp;
        // }
        // void    left_rotation(RedBlackTree<type_name> **root)
        // {
        //     RedBlackTree<type_name> *roottmp = *root;
        //     *root = (*root)->right;
        //     RedBlackTree<type_name> *righttmp = (*root)->left;
        //     (*root)->left = roottmp;
        //     roottmp->right = righttmp;
        // }
        // void    right_rotation(RedBlackTree<type_name> **root)
        // {
        //     RedBlackTree<type_name> *roottmp = *root;
        //     *root = (*root)->left; // new root
        //     (*root)->parent = roottmp->parent;
        //     (*root)->position = roottmp->position;
        //     RedBlackTree<type_name> *righttmp = (*root)->right;
        //     (*root)->right = roottmp; //new right is ex root
        //     if (roottmp)
        //     {
        //         roottmp->parent = *root;
        //         roottmp->position = r;
        //     }
        //     roottmp->left = righttmp; // new left for right to keep childs
        //     if (righttmp)
        //     {
        //         righttmp->position = l;
        //         righttmp->parent = roottmp;
        //     }
        // }
        // void    left_rotation(RedBlackTree<type_name> **root) // deleted all coloring shit
        // {
        //     RedBlackTree<type_name> *roottmp = *root;
        //     *root = (*root)->right; // new root
        //     (*root)->position = roottmp->position;
        //     (*root)->parent = roottmp->parent;
        //     RedBlackTree<type_name> *righttmp = (*root)->left;
        //     (*root)->left = roottmp; // new left is the old root
        //     if (roottmp)
        //     {
        //         (*root)->left->parent = *root;
        //         roottmp->position = l;
        //     }
        //     roottmp->right = righttmp; // new right is the old left of the first left
        //     if (righttmp)
        //     {
        //         righttmp->position = r;
        //         righttmp->parent = roottmp;
        //     }
        // }
        void    left_rotation(RedBlackTree<type_name> **root)
        {
            type_name tmprootvalue = (*root)->value;
            (*root)->value = (*root)->right->value;
            (*root)->right->value = tmprootvalue;
            RedBlackTree<type_name> *tmpright = (*root)->right;
            (*root)->right = (*root)->right->right;
            if ((*root)->right)
            {
                (*root)->right->position = r;
                (*root)->right->parent = *root;
            }
            RedBlackTree<type_name> *leftwight = (*root)->left;
            (*root)->left = tmpright;
            if ((*root)->left)
            {
                (*root)->left->position = l;
                (*root)->left->parent = *root;
            }
            tmpright->left = leftwight;
            if (leftwight)
            {
                leftwight->parent = tmpright;
                leftwight->position = l;
            }
        }
        void    right_rotation(RedBlackTree<type_name> **root)
        {
            type_name tmprootvalue = (*root)->value;
            (*root)->value = (*root)->left->value;
            (*root)->left->value = tmprootvalue;
            RedBlackTree<type_name> *tmpleft = (*root)->left;
            (*root)->left = (*root)->left->left;
            if ((*root)->left)
            {
                (*root)->left->position = l;
                (*root)->left->parent = *root;
            }
            RedBlackTree<type_name> *rightwight = (*root)->right;
            (*root)->right = tmpleft;
            if ((*root)->right)
            {
                (*root)->right->position = r;
                (*root)->right->parent = *root;
            }
            tmpleft->left = rightwight;
            if (rightwight)
            {
                rightwight->parent = tmpleft;
                rightwight->position = l;
            }
        }
        void    balancing(RedBlackTree<type_name> **head, int position)
        {
            if (position == r)
            {
                puts("right");
                if ((*head)->right->right)
                    return puts("right right"), left_rotation(head);
                right_rotation(&((*head)->right));
                left_rotation(head);
                puts("right left");
                return;
            }
            if ((*head)->left->left)
                return puts("left left"), right_rotation(head);
            puts("left right");
            left_rotation(&((*head)->left));
            right_rotation(head);
        }
        int    recentlyadded(RedBlackTree<type_name> *x, type_name value)
        {
            if (x->left && x->left->value == value)
                return (l);
            return r;
        }
        void    insert(RedBlackTree<type_name> **head, RedBlackTree<type_name> *nv, int position)
        {
            if (*head == NULL)
            {
                if (position == rt)
                    puts("1");
                *head = nv;
                nv->position = position;
                if (position == rt)
                    nv->color = black;
                return;
            }
            if (cmpr(nv->value, (*head)->value))
                std::cout << ("left ") << (*head)->value << " " << nv->value << '\n'    , insert(&((*head)->left), nv, l);
            else
                std::cout << ("right ") << (*head)->value << " " << nv->value << '\n'    , insert(&((*head)->right), nv, r);
            if ((*head)->left)
                (*head)->left->parent = *head;
            if ((*head)->right)
                (*head)->right->parent = *head;
            if ((*head)->color == black)
                return;
            if ((*head)->position == r) // parent
            {
                if ((*head)->parent->left && (*head)->parent->left->color == red)
                    return puts("recoloring"), recoloring((*head)->parent);
                return puts("balancing"), balancing(&((*head)->parent), (*head)->position);
            }
            if ((*head)->parent->right && (*head)->parent->right->color == red)
                return recoloring((*head)->parent);
            balancing(&((*head)->parent), (*head)->position);  
        }
        void    printing(RedBlackTree<type_name> *root, int level)
        {
            if (!root)
                return;
            printing(root->right, level + 1);
            printing(root->left, level + 1);
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