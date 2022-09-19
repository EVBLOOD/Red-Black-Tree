/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_body.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 18:06:02 by sakllam           #+#    #+#             */
/*   Updated: 2022/09/19 19:05:36 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
// for ckecker
#include <cstddef>
#include <ostream>
#include <queue>
#include <vector>
#include <map>
// end
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <sys/_types/_size_t.h>
#include <iostream>
namespace ft
{
    #define red true
    #define black false
    #define rt 1
    #define l 2
    #define r 3
    template <class T>
        struct RedBlackTree
    {
        typedef T type_name;

        type_name value;
        RedBlackTree *left;
        RedBlackTree *right;
        RedBlackTree *parent;
        int           position;
        bool          color;
        RedBlackTree(type_name value) : value(value), left(NULL), right(NULL), parent(NULL), color(red) {}
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
        // RedBlackTree<type_name> *ROOT;
        
        

        void swaping(RedBlackTree<type_name> *one, RedBlackTree<type_name> *two)
        {
            type_name   tmp = one->value;
            int         color = one->color;
            one->value = two->value;
            one->color = two->color;
            two->value = tmp;
            two->color = color;
        }
        void    right_rotation(RedBlackTree<type_name> **root, bool coloring = true)
        {
            swaping((*root)->left, *root);
            RedBlackTree<type_name> *tmpA = (*root)->left;
            (*root)->left = (*root)->left->left;
            if ((*root)->left)
            {
                (*root)->left->parent = *root;
                if (coloring)
                    (*root)->left->color = red;
            }
            tmpA->left = tmpA->right;
            if (tmpA->left)
            {
                tmpA->left->parent = tmpA;
                tmpA->left->position = l;
            }
            tmpA->right = (*root)->right;
            if (tmpA->right)
            {
                tmpA->right->position = r;
                tmpA->right->parent = tmpA;
            }
            (*root)->right = tmpA;
            tmpA->position = r;
            tmpA->parent = *root;
            if (coloring)
            {
                (*root)->color = black;
                tmpA->color = red;
            }
        }
        void    left_rotation(RedBlackTree<type_name> **root, bool coloring = true)
        {
            swaping((*root)->right, *root);
            RedBlackTree<type_name> *tmpA = (*root)->right;
            (*root)->right = (*root)->right->right;
            if ((*root)->right)
            {
                (*root)->right->parent = *root;
                (*root)->right->position = r;
                if (coloring)
                    (*root)->right->color = red;
            }
            tmpA->right = tmpA->left;
            if (tmpA->right)
            {
                tmpA->right->parent = tmpA;
                tmpA->right->position = r;
            }
            tmpA->left = (*root)->left;
            if (tmpA->left)
            {
                tmpA->left->position = l;
                tmpA->left->parent = tmpA;
            }
            (*root)->left = tmpA;
            tmpA->position = l;
            tmpA->parent = *root;
            if (coloring)
            {
                (*root)->color = black;
                tmpA->color = red;
            }
        }
        void    balancing(RedBlackTree<type_name> **head, int position)
        {
            if (position == r)
            {
                if ((*head)->right->right && (*head)->right->right->color == red)
                    return left_rotation(head);
                right_rotation(&((*head)->right), false);
                return left_rotation(head);
            }
            if ((*head)->left->left && (*head)->left->left->color == red)
                return right_rotation(head);
            left_rotation(&((*head)->left), false);
            return right_rotation(head);
        }
        RedBlackTree<type_name> *newnode(type_name value)
        {
            RedBlackTree<type_name> *newnode = ac.allocate(1);
            ac.construct(newnode, value);
            return newnode;
        }
        void    insert(RedBlackTree<type_name> **head, RedBlackTree<type_name> *nv, int position)
        {
            if ((*head) == NULL)
            {
                // if (position == rt)
                //      ROOT = nv;
                *head = nv;
                nv->position = position;
                if (position == rt)
                    nv->color = black;
                size = size + 1;
                return;
            }
            if (cmpr(nv->value, (*head)->value))
                insert(&((*head)->left), nv, l);
            else if (cmpr((*head)->value, nv->value))
                insert(&((*head)->right), nv, r);
            else
                return;
            if ((*head)->left && (*head)->left->value == nv->value)
                (*head)->left->parent = *head;
            else
                (*head)->right->parent = *head;
            if ((*head)->color == black ||
                    (((*head)->left == NULL || (*head)->left->color == black) && ((*head)->right == NULL || (*head)->right->color == black)))
                return;
            if ((*head)->position == r)
            {
                if ((*head)->parent->left && (*head)->parent->left->color == red)
                {
                    (*head)->parent->left->color = black;
                    if ((*head)->parent->position != rt)
                        (*head)->parent->color = red;
                    (*head)->color = black;
                    return;
                }
                return balancing(&((*head)->parent), r);
            }
            if ((*head)->parent->right && (*head)->parent->right->color == red)
            {
                (*head)->parent->right->color = black;
                if ((*head)->parent->position != rt)
                    (*head)->parent->color = red;
                (*head)->color = black;
                return;
            }
            return balancing(&((*head)->parent), l);
        }
        void    printing(RedBlackTree<type_name> *root, int level)
        {
            if (!root)
                return;
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
            printing(root->right, level + 1);
        }
        RedBlackTree<type_name> *thedeepest_left(RedBlackTree<type_name> *head)
        {
            if (head->left == NULL)
                return head;
            return thedeepest_left(head->left);
        }
        RedBlackTree<type_name> *next(RedBlackTree<type_name> *x, int position, RedBlackTree<type_name> *old)
        {
            if (x == NULL)
                return (NULL);
            std::cout <<  " deb : " << x->value << "\n";
            if (x->right && old != x->right)
                return thedeepest_left(x->right);
            if (x->position == l)
                    return x->parent;
            return next(x->parent, x->position, x);
        }
        RedBlackTree<type_name> *thedeepest_right(RedBlackTree<type_name> *head)
        {
            if (head->right == NULL)
                return head;
            return thedeepest_right(head->right);
        }
        RedBlackTree<type_name> *prev(RedBlackTree<type_name> *x, int position, RedBlackTree<type_name> *old)
        {
            if (x == NULL)
                return thedeepest_right(head);
            if (x->left && old != x)
                return prev(x->left, x->position, x);
            return x->parent;
        }
        // this part of code was writen by a student in 1337 and I'm leaving it here cause I appreciate his help!
        // void debug()
        // {
        //     if (this->size != 0)
        //     {
        //         std::queue<std::pair<RedBlackTree<type_name> *, int> >  kyou;
        //         kyou.push(std::make_pair(ROOT, 0));
        //         while(kyou.size())
        //         {
        //             std::pair<RedBlackTree<type_name>*, int>  front = kyou.front();
        //             kyou.pop();
        //             for (int i = 0; i < front.second; i++)
        //                 std::cout << "-";
        //             std::cout << " ";
        //             std::cout << front.first->value << " " << front.first->color << " "<< front.first->position << " " << front.first->parent << " " << front.first << std::endl;
        //             if (front.first->left)
        //                 kyou.push(std::make_pair(front.first->left, front.second+1));
        //             if (front.first->right)
        //                 kyou.push(std::make_pair(front.first->right, front.second+1));
        //         }
        //     }
        //     std::cout <<"-------------------------------" << std::endl;
        // }
        // checker {made by: jalalium}
        // bool check(RedBlackTree<type_name>* node, std::map<RedBlackTree<type_name>* , std::vector<int> > &mp)
		// {
		// 	bool ok = true;
		// 	if (node->left != NULL)
		// 	{
		// 		if (node->value <= node->left->value)
		// 		{
		// 			std::cout << "LEFT CHILD LARGER OR EQUAL TO PARENT " << node->value << " " << node->left->value << std::endl;
		// 			return false;
		// 		}
		// 		if (node->color == red && node->left->color == red)
		// 		{
		// 			std::cout << "RED PARENT WITH RED CHILD: " << node->value << " " << node->left->value << std::endl;
		// 			return false;
		// 		}
		// 		ok &= check(node->left,mp);
		// 	}
		// 	if (node->right != NULL)
		// 	{
		// 		if (node->value >= node->right->value)
		// 		{
		// 			std::cout << "RIGHT CHILD SMALLER OR EQUAL TO PARENT " << node->value << " " << node->left->value << std::endl;
		// 			return false;
		// 		}
		// 		if (node->color == red && node->right->color == red)
		// 		{
		// 			std::cout << "RED PARENT WITH RED CHILD: " << node->value << " " << node->right->value << std::endl;
		// 			return false;
		// 		}
		// 		ok &= check(node->right,mp);
		// 	}
		// 	std::vector<int> tmp;
		// 	if (node->left != NULL)
		// 	{
		// 		for (int z : mp[node->left])
		// 			tmp.push_back(z);
		// 	}
		// 	else
		// 		tmp.push_back(0);
		// 	if (node->right != NULL)
		// 	{
		// 		for (int z : mp[node->right])
		// 			tmp.push_back(z);
		// 	}
		// 	else
		// 		tmp.push_back(0);
		// 	std::sort(tmp.begin(), tmp.end());
		// 	for (int &z : tmp)
		// 		z += (node->color == black);
		// 	mp[node] = tmp;
        //     if (tmp[0] != tmp.back())
        //     {
        //         std::cout << "NODE " << node->value << std::endl;
        //         for (int z : tmp)
        //             std::cout << z << " ";
        //         std::cout << std::endl;
        //     }
		// 	return (ok &(tmp[0] == tmp.back()));
		// }
        // end of checker!
        type_name thedeepest(RedBlackTree<type_name> *head)
        {
            if (head->right == NULL)
                return head->value;
            return thedeepest(head->right);
        }
        void remove_helper(RedBlackTree<type_name> **head, type_name element)
        {
            if (*head == NULL)
                return;
            if (cmpr(element, (*head)->value))
                remove_helper(&((*head)->left), element);
            else if (cmpr((*head)->value, element))
                remove_helper(&((*head)->right), element);
            else
            {
                RedBlackTree<type_name> *target = *head;
                if (target->left == NULL && target->right == NULL)
                {
                    bool color = target->color;
                    int position = target->position;
                    RedBlackTree<type_name> *parent = (*head)->parent;
                    ac.destroy(*head);
                    ac.deallocate(*head, 1);
                    *head = NULL;
                    if (color == black && position != rt)
                        fix_double_black(&(parent), position);
                    size--;
                    return;
                }
                if (target->left == NULL)
                {
                    type_name value = target->right->value;
                    (*head)->value = value;
                    remove_helper(&((*head)->right), value);
                    return;
                }
                if (target->right == NULL)
                {
                    type_name value = target->left->value;
                    (*head)->value = value;
                    remove_helper(&((*head)->left), value);
                    return;
                }
                type_name value = thedeepest(target->left);
                (*head)->value = value;
                remove_helper(&((*head)->left), value);
            }
        }
        void    deletion_balancing_recoloring(RedBlackTree<type_name> **head, int position, bool each = true)
        {
            if (each)
            {
                if (position == r)
                {
                    if ((*head)->right->right && (*head)->right->right->color == red)
                    {
                        (*head)->right->color = (*head)->color;
                        (*head)->color = black;
                        (*head)->right->right->color = black;
                        return left_rotation(head, false);
                    }
                    (*head)->right->color = red;
                    (*head)->right->left->color = black;
                    right_rotation(&((*head)->right), false);
                    (*head)->right->color = (*head)->color;
                    (*head)->color = black;
                    (*head)->right->right->color = black;
                    return left_rotation(head, false);
                }
                if ((*head)->left->left && (*head)->left->left->color == red)
                {
                    (*head)->left->color = (*head)->color;
                    (*head)->color = black;
                    (*head)->left->left->color = black;
                    return right_rotation(head, false);
                }
                (*head)->left->color = red;
                (*head)->left->right->color = black;
                left_rotation(&((*head)->left), false);
                (*head)->left->color = (*head)->color;
                (*head)->color = black;
                (*head)->left->left->color = black;
                return right_rotation(head, false);
            }
            if (position == r)
            {
                if ((*head)->right->right)
                    return left_rotation(head, false);
                if ((*head)->right->left)
                    right_rotation(&((*head)->right), false);
                return left_rotation(head, false);
            }
            if ((*head)->left->left)
                return right_rotation(head, false);
            if ((*head)->left->right)
                left_rotation(&((*head)->left), false);
            return right_rotation(head, false);
        }

        RedBlackTree<type_name> *nephew(RedBlackTree<type_name> *node, int position)
        {
            if (position == l)
                return node->right;
            return node->left;
        }
        RedBlackTree<type_name> *niece(RedBlackTree<type_name> *node, int position)
        {
          if (position == l)
              return node->left;
            return node->right;
        }
        void fix_case(RedBlackTree<type_name> **sibling, int position)
        {
            if ((nephew(*sibling, position) && nephew(*sibling, position)->color == red)
                || (niece(*sibling, position) && niece(*sibling, position)->color == red))
                return deletion_balancing_recoloring(&((*sibling)->parent), (*sibling)->position);
            if ((*sibling)->color == black)
            {
                (*sibling)->color = red;
                if ((*sibling)->parent->color != black)
                    (*sibling)->parent->color = black;
                else 
                    fix_double_black(&((*sibling)->parent->parent), (*sibling)->parent->position);
                return ;
            }
            if ((*sibling)->color == red)
            {
                (*sibling)->parent->color = red;
                (*sibling)->color = black;
                deletion_balancing_recoloring(&((*sibling)->parent), (*sibling)->position, false);
                if (position == l)
                    return fix_double_black(&((*sibling)->parent->left), l);
                return fix_double_black(&((*sibling)->parent->right), r);
            }
        }
        void fix_double_black(RedBlackTree<type_name> **leaf_parent, int position)
        {
            if (position == rt)
                return;
            if (position == r)
                return fix_case(&((*leaf_parent)->left), r);
            else
                return fix_case(&((*leaf_parent)->right), l);
        }
        bool find_helper(RedBlackTree<type_name> *head, type_name value)
        {
            if (head == NULL)
                return false;
            if (cmpr(value, head->value))
                return find_helper(head->left, value);
            else if (cmpr(head->value, value))
                return find_helper(head->right, value);
            else
                return true;
        }
        void free_helper(RedBlackTree<type_name> *head)
        {
            if (head == NULL)
                return ;
            free_helper(head->right);
            free_helper(head->left);
            ac.destroy(head);
            ac.deallocate(head, 1);            
        }
        public:
            RBT() : head(NULL), size(0) {}
            ~RBT()
            {
                free_helper(head);
            }
            void insert(type_name value)
            {
                insert(&head, newnode(value), rt);
                // checking time!
                // std::map<RedBlackTree<type_name>* , std::vector<int> > mp;
				// assert(check(head, mp));
                // std::cout << "INSERTED " << value << " SUCCESSFULLY" << std::endl;
            }
            RedBlackTree<type_name> *begin()
            {
                return thedeepest_left(head);
            }
            RedBlackTree<type_name> *_prev(RedBlackTree<type_name> *x)
            {
                if (x == NULL)
                    return prev(x, 10, x);
                return prev(x, x->position, x);
            }
            RedBlackTree<type_name> *_next(RedBlackTree<type_name> *x)
            {
                return next(x, x->position, x);
            }
            void  printing()
            {
                printing(this->head, 0);
            }
            size_amount lengh()
            {
                return size;
            }
            bool find(type_name value)
            {
                return find_helper(head, value);
            }
            void remove(type_name element)
            {
                // std::cout << "the number to delete: " << element << "\n";
                // debug();
                if (!head)
                    return;
                remove_helper(&head, element);
                // if (head == NULL)
                // {
                //     std::cout << element << " SUCCESSFULLY DELETED! " << std::endl;
                //     return;
                // }
                // // debug();
                // std::map<RedBlackTree<type_name>* , std::vector<int> > mp;
				// assert(check(head, mp));
                // std::cout << element << " SUCCESSFULLY DELETED! " << std::endl;
            }
    };
}