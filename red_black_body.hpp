/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_body.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 18:06:02 by sakllam           #+#    #+#             */
/*   Updated: 2022/08/27 20:16:36 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
// for ckecker
#include <cstddef>
#include <queue>
#include <vector>
#include <map>
// end
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
        // RedBlackTree<type_name> *ROOT;
        
        
        RedBlackTree<type_name> *newnode(type_name value)
        {
            RedBlackTree<T> *newnode = ac.allocate(1);
            newnode->value = value;
            newnode->color = red;
            newnode->left = NULL;
            newnode->right = NULL;
            newnode->parent = NULL;
            return newnode;
        }
        size_amount max(size_amount a, size_amount b)
        {
            if (a > b)
                return a;
            return b;
        }
        void    left_rotation(RedBlackTree<type_name> **root, bool clr)
        {
            // changing value only so no need to change the parent and color of it | else you may think of "blacking it"
            type_name tmprtval = (*root)->value;
            (*root)->value = (*root)->right->value;
            (*root)->right->value = tmprtval;
            if (clr)
                (*root)->color = black;

            RedBlackTree<type_name> *A = (*root); // the new root
            RedBlackTree<type_name> *B = (*root)->right; // the new left --> must change it's position and parent
            RedBlackTree<type_name> *C = B->right; // the new right --> must change it's position and parent
            RedBlackTree<type_name> *Aleft = A->left; // in case of extra wieghts in left of old root

            A->left = B;
            // start : changing color to red + position to the new one and parent also
            B->position = l;
            B->parent = A;
            if (clr)
                B->color = red;
            // end

            A->right = C;
            // start : changing color to red + position to the new one and parent also
            if (C) // in case of using it just as part of {rotate left + rotate right} 
            {
                C->position = r;
                C->parent = A;
                if (clr)
                    C->color = red;
            }
            // end
            
            B->right = B->left; // returning to the normal order to sqp the problem made while changing values of ex root and new one!
            if (B->right)
            {
                B->right->parent = B;
                B->right->position = r;
            }

            B->left = Aleft;
            // start : keeping lbrahch undercontrole!
            if (Aleft)
                B->left->parent = B;
            //end
        }
        void    right_rotation(RedBlackTree<type_name> **root, bool clr)
        {
            type_name tmprootvalue = (*root)->value;
            (*root)->value = (*root)->left->value;
            (*root)->left->value = tmprootvalue;

            RedBlackTree<type_name> *A = (*root);
            RedBlackTree<type_name> *B = A->left;
            RedBlackTree<type_name> *C = B->left;

            RedBlackTree<type_name> *keepAright = A->right;
            A->right = B;
            if (clr)
                A->color = black;
            
            B->position = r;
            B->parent = A;
            if (clr)
                B->color = red;
            
            A->left = C;
            if (C)
            {
                C->parent = A;
                if (clr)
                    C->color = red;
                C->position = l;
            }
            
            B->left = B->right;
            if (B->left)
                B->left->position = l;
            B->right = keepAright;
            if (keepAright)
                keepAright->parent = B;
            
        }
               void    left_rotationdel(RedBlackTree<type_name> **root, bool clr)
        {
            // changing value only so no need to change the parent and color of it | else you may think of "blacking it"
            type_name tmprtval = (*root)->value;
            (*root)->value = (*root)->right->value;
            (*root)->right->value = tmprtval;
            if (clr)
                (*root)->color = red;

            RedBlackTree<type_name> *A = (*root); // the new root
            RedBlackTree<type_name> *B = (*root)->right; // the new left --> must change it's position and parent
            RedBlackTree<type_name> *C = B->right; // the new right --> must change it's position and parent
            RedBlackTree<type_name> *Aleft = A->left; // in case of extra wieghts in left of old root

            A->left = B;
            // start : changing color to red + position to the new one and parent also
            B->position = l;
            B->parent = A;
            if (clr)
                B->color = black;
            // end

            A->right = C;
            // start : changing color to red + position to the new one and parent also
            if (C) // in case of using it just as part of {rotate left + rotate right} 
            {
                C->position = r;
                C->parent = A;
                if (clr)
                    C->color = black;
            }
            // end
            
            B->right = B->left; // returning to the normal order to sqp the problem made while changing values of ex root and new one!
            if (B->right)
            {
                B->right->parent = B;
                B->right->position = r;
            }

            B->left = Aleft;
            // start : keeping lbrahch undercontrole!
            if (Aleft)
                B->left->parent = B;
            //end
        }
        void    right_rotationdel(RedBlackTree<type_name> **root, bool clr)
        {
            type_name tmprootvalue = (*root)->value;
            (*root)->value = (*root)->left->value;
            (*root)->left->value = tmprootvalue;

            RedBlackTree<type_name> *A = (*root);
            RedBlackTree<type_name> *B = A->left;
            RedBlackTree<type_name> *C = B->left;

            RedBlackTree<type_name> *keepAright = A->right;
            A->right = B;
            if (clr)
                A->color = red;
            
            B->position = r;
            B->parent = A;
            if (clr)
                B->color = black;
            
            A->left = C;
            if (C)
            {
                C->parent = A;
                if (clr)
                    C->color = black;
                C->position = l;
            }
            
            B->left = B->right;
            if (B->left)
                B->left->position = l;
            B->right = keepAright;
            if (keepAright)
                keepAright->parent = B;
            
        }
        void    balancing(RedBlackTree<type_name> **head, int position, RedBlackTree<type_name> *cerr)
        {
            if (position == r)
            {
                if ((*head)->right->right && (cerr->right->color == red || !cerr->left))
                    return left_rotation(head, true);
                right_rotation(&((*head)->right), false);
                left_rotation(head, true);
                return;
            }
            if ((*head)->left->left && (cerr->left->color == red || !cerr->right))
                return right_rotation(head, true);
            left_rotation(&((*head)->left), false);
            right_rotation(head, true);
        }
        int    recentlyadded(RedBlackTree<type_name> *x, type_name value)
        {
            if (x->left && x->left->value == value)
                return (l);
            return r;
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
        //             std::cout << front.first->value << " " << front.first->color << " "<< front.first->position << " " << front.first->parent << std::endl;
        //             if (front.first->left)
        //                 kyou.push(std::make_pair(front.first->left, front.second+1));
        //             if (front.first->right)
        //                 kyou.push(std::make_pair(front.first->right, front.second+1));
        //         }
        //     }
        //     std::cout <<"-------------------------------" << std::endl;
        // }
        void    insert(RedBlackTree<type_name> **head, RedBlackTree<type_name> *nv, int position)
        {
            if (*head == NULL)
            {
                // if (position == rt)
                //     ROOT = nv;
                *head = nv;
                nv->position = position;
                if (position == rt)
                    nv->color = black;
                return;
            }
            if (cmpr(nv->value, (*head)->value))
                insert(&((*head)->left), nv, l);
            else
                insert(&((*head)->right), nv, r);
            if ((*head)->left)
                (*head)->left->parent = *head;
            if ((*head)->right)
                (*head)->right->parent = *head;
            if ((*head)->color == black)
                return;
            if (((*head)->left == NULL || (*head)->left->color == black) && ((*head)->right == NULL || (*head)->right->color == black))
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
                return balancing(&((*head)->parent), (*head)->position, *head);
            }
            if ((*head)->parent->right && (*head)->parent->right->color == red)
            {
                (*head)->parent->right->color = black;
                if ((*head)->parent->position != rt)
                    (*head)->parent->color = red;
                (*head)->color = black;
                return;
            }
            balancing(&((*head)->parent), (*head)->position, *head);
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
        // checker {made by: jalalium}
        bool check(RedBlackTree<type_name>* node, std::map<RedBlackTree<type_name>* , std::vector<int> > &mp)
		{
			bool ok = true;
			if (node->left != NULL)
			{
				if (node->value <= node->left->value)
				{
					std::cout << "LEFT CHILD LARGER OR EQUAL TO PARENT " << node->value << " " << node->left->value << std::endl;
					return false;
				}
				if (node->color == red && node->left->color == red)
				{
					std::cout << "RED PARENT WITH RED CHILD: " << node->value << " " << node->left->value << std::endl;
					return false;
				}
				ok &= check(node->left,mp);
			}
			if (node->right != NULL)
			{
				if (node->value >= node->right->value)
				{
					std::cout << "RIGHT CHILD SMALLER OR EQUAL TO PARENT " << node->value << " " << node->left->value << std::endl;
					return false;
				}
				if (node->color == red && node->right->color == red)
				{
					std::cout << "RED PARENT WITH RED CHILD: " << node->value << " " << node->right->value << std::endl;
					return false;
				}
				ok &= check(node->right,mp);
			}
			std::vector<int> tmp;
			if (node->left != NULL)
			{
				for (int z : mp[node->left])
					tmp.push_back(z);
			}
			else
				tmp.push_back(0);
			if (node->right != NULL)
			{
				for (int z : mp[node->right])
					tmp.push_back(z);
			}
			else
				tmp.push_back(0);
			std::sort(tmp.begin(), tmp.end());
			for (int &z : tmp)
				z += (node->color == black);
			mp[node] = tmp;
			return (ok &(tmp[0] == tmp.back()));
		}
        // end of checker!
        type_name thedeepest(RedBlackTree<type_name> *head)
        {
            if (head->right == NULL)
                return head->value;
            return thedeepest(head->right);
        }
        void remove(RedBlackTree<type_name> **head, type_name element)
        {
            if (*head == NULL)
                return;
            if (cmpr(element, (*head)->value))
                remove(&((*head)->left), element);
            else if (cmpr((*head)->value, element))
                remove(&((*head)->right), element);
            else
            {
                RedBlackTree<type_name> *target = *head;
                if (target->left == NULL && target->right == NULL)
                {
                    bool color = target->color;
                    int position = target->position;
                    RedBlackTree<type_name> **parent = &((*head)->parent);
                    // ac.destroy(*head);
                    // ac.dealocate(*head);
                    *head = NULL;
                    if (position == rt)
                        return;
                    if (color == black)
                        fixblack(parent, position);
                    return;
                }
                if (target->left == NULL)
                {
                    type_name value = target->right->value;
                    // ac.destroy(&(target->value));
                    // ac.dealocate(target);
                    (*head)->value = value;;
                    remove(&((*head)->right), value);
                    return;
                }
                type_name value = thedeepest(target->left);
                (*head)->value = value;
                remove(&((*head)->left), value);
            }
        }
        // void colorsfixing(RedBlackTree<type_name> **head)
        // {
        //     if (*head == NULL)
        //         return;
        //     colorsfixing(&((*head)->left));
        //     colorsfixing(&((*head)->right));
        //     if ((*head)->parent->color == black)
        //         return;
        //     if ((*head)->position == l)
        //     {
        //         if ((*head)->parent->right && (*head)->parent->right->color == red)
        //         {
        //             // recoloring
        //             (*head)->parent->color = black;
        //             return;
        //         }
        //         // balancing shit
        //         // balancing(&((*head)->parent->parent), (*head)->parent->position, (*head)->parent);
        //         return;
        //     }
        //     if ((*head)->parent->left && (*head)->parent->left->color == red)
        //     {
        //         // recoloring
        //         (*head)->parent->color = black;
        //         return;
        //     }
        //     // balancing(&((*head)->parent->parent), (*head)->parent->position, (*head)->parent);
        //     // balancing shit
        //     return;
        // }
        void    balancingdel(RedBlackTree<type_name> **head, int position)
        {
            if (position == r)
            {
                if ((*head)->right->right)
                    return left_rotationdel(head, true);
                right_rotationdel(&((*head)->right), false);
                left_rotationdel(head, true);
                return;
            }
            if ((*head)->left->left)
                return right_rotationdel(head, true);
            left_rotationdel(&((*head)->left), false);
            right_rotationdel(head, true);
        }
        void fixblack(RedBlackTree<type_name> **head, int position)
        {
            if (position == rt)
                return;
            if (position == r)
            {
                if (!((*head)->left) || (*head)->left->color != black)
                    return;
                if ((*head)->left->right == NULL && (*head)->left->left == NULL)
                {
                    // puts("coloring r");
                    (*head)->color = black;
                    (*head)->left->color = red;
                    return;
                }
                    // puts("balancing r");
                balancingdel(head, l);
                // colorsfixing(head);
                // if ((*head)->left || (*head)->right)
                // {
                    // puts("start");
                    // colorsfixing(&((*head)->parent));
                    // puts("end");
                // }
                    // puts("testing the same shit!");
                return;
            }
            if (!((*head)->right) || (*head)->right->color != black)
                return;
            if ((*head)->right->right == NULL && (*head)->right->left == NULL)
            {
            //  puts("coloring l");
                (*head)->color = black;
                (*head)->right->color = red;
                return ;
            }
            //  puts("balancing l");
            // balancing(&((*head)->parent), (), *head);
            balancingdel(head, r);
            // std::cout << "head => " << (*head)->value << std::endl;
            // if ((*head)->left || (*head)->right)
            // {
                // puts("start");
                // colorsfixing(&((*head)->parent));
                // puts("end");
            // }
                // puts("testing s÷ome shit");
                // fixblack(head, (*head)->position);
            // balancing(&(head->parent), position, (*head)->left);
        }
        public:
            RBT() : head(NULL), size(0) {}
            void insert(type_name value)
            {
                insert(&head, newnode(value), rt);
                // checking time!
                std::map<RedBlackTree<type_name>* , std::vector<int> > mp;
				assert(check(head, mp));
                std::cout << "INSERTED " << value << " SUCCESSFULLY" << std::endl;
                // end of check!
                size++;
            }
            void  printing()
            {
                printing(this->head, 0);
            }
            size_amount lengh()
            {
                return size;
            }
            void remove(type_name element)
            {
                std::cout << "the number to delete: " << element << "\n";
                remove(&head, element);
                if (head == NULL)
                {
                    std::cout << element << " SUCCESSFULLY DELETED! " << std::endl;
                    return;
                }
                printing(head, 0);
                std::map<RedBlackTree<type_name>* , std::vector<int> > mp;
				assert(check(head, mp));
                std::cout << element << " SUCCESSFULLY DELETED! " << std::endl;
            }
    };
}