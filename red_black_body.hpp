/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_body.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 18:06:02 by sakllam           #+#    #+#             */
/*   Updated: 2022/09/12 19:28:23 by sakllam          ###   ########.fr       */
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
        RedBlackTree<type_name> *ROOT;
        
        

        void swaping(RedBlackTree<type_name> *one, RedBlackTree<type_name> *two)
        {
            type_name   tmp = one->value;
            int         color = one->color;
            one->value = two->value;
            one->color = two->color;
            two->value = tmp;
            two->color = color;
        }
        void    right_rotation(RedBlackTree<type_name> **root, bool coloring = false)
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
        void    left_rotation(RedBlackTree<type_name> **root, bool coloring = false)
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
                if ((*head)->right->right && (*head)->right->right->color == red)//|| !(*head)->right->left))
                    return left_rotation(head, true);
                right_rotation(&((*head)->right), false);
                left_rotation(head, true);
                return;
            }
            if ((*head)->left->left && (*head)->left->left->color == red) //|| !(*head)->left->right))
                return right_rotation(head, true);
            left_rotation(&((*head)->left), false);
            right_rotation(head, true);
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
                if (position == rt)
                     ROOT = nv;
                (*head) = nv;
                nv->position = position;
                if (position == rt)
                    nv->color = black;
                return;
            }
            if (cmpr(nv->value, (*head)->value))
                insert(&((*head)->left), nv, l);
            else if (cmpr((*head)->value, nv->value))
                insert(&((*head)->right), nv, r);
            else
                return;
            if ((*head)->left)
                (*head)->left->parent = *head;
            if ((*head)->right)
                (*head)->right->parent = *head;
            if ((*head)->color == black || (((*head)->left == NULL || (*head)->left->color == black) && ((*head)->right == NULL || (*head)->right->color == black)))
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
            balancing(&((*head)->parent), l);
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
        // this part of code was writen by a student in 1337 and I'm leaving it here cause I appreciate his help!
        void debug()
        {
            if (this->size != 0)
            {
                std::queue<std::pair<RedBlackTree<type_name> *, int> >  kyou;
                kyou.push(std::make_pair(ROOT, 0));
                while(kyou.size())
                {
                    std::pair<RedBlackTree<type_name>*, int>  front = kyou.front();
                    kyou.pop();
                    for (int i = 0; i < front.second; i++)
                        std::cout << "-";
                    std::cout << " ";
                    std::cout << front.first->value << " " << front.first->color << " "<< front.first->position << " " << front.first->parent << " " << front.first << std::endl;
                    if (front.first->left)
                        kyou.push(std::make_pair(front.first->left, front.second+1));
                    if (front.first->right)
                        kyou.push(std::make_pair(front.first->right, front.second+1));
                }
            }
            std::cout <<"-------------------------------" << std::endl;
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
            if (tmp[0] != tmp.back())
            {
                std::cout << "NODE " << node->value << std::endl;
                for (int z : tmp)
                    std::cout << z << " ";
                std::cout << std::endl;
            }
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
                    RedBlackTree<type_name> *parent = (*head)->parent;
                    ac.destroy(*head);
                    ac.deallocate(*head, 1);
                    *head = NULL;
                    if (color == black)
                        correctblackheigt(parent, position);
                    return;
                }
                if (target->left == NULL)
                {
                    type_name value = target->right->value;
                    (*head)->value = value;;
                    remove(&((*head)->right), value);
                    return;
                }
                type_name value = thedeepest(target->left);
                (*head)->value = value;
                remove(&((*head)->left), value);
            }
        }


        void    balanceindeletion(RedBlackTree<type_name> **head, int position)
        {
            if (position == r)
            {
                puts("left rotation");
                if ((*head)->right->right && ((*head)->right->color == red))// || !(*head)->left)) // left oryit3jib
                    return left_rotation(head);
                right_rotation(&((*head)->right));
                left_rotation(head);
                return;
            }
                puts("right rotation");
            if ((*head)->left->left && ((*head)->left->color == red))// || !(*head)->right))
                return right_rotation(head);
                // return balanceindeletion(head, r);
            // puts("sss");
            // if ((*head)->left)
            left_rotation(&((*head)->left));
                // puts("holy fuck l");
            right_rotation(head);
        }

        RedBlackTree<type_name> *nephew(RedBlackTree<type_name> *node, int position) // the child exists far away
        {
            if (position == l)
                return node->right;
            return node->left;
        }
        RedBlackTree<type_name> *niece(RedBlackTree<type_name> *node, int position) // closer child of sibling
        {
          if (position == l)
              return node->left;
            return node->right;
        }
        void correctionhelper(RedBlackTree<type_name> *sibling, int position)
        {
            if (sibling->color == red)
            {
                sibling->parent->color = red;
                sibling->color = black;
                balancing(&(sibling->parent), sibling->position);
            }
            else if (nephew(sibling, position) && nephew(sibling, position)->color == red)
            {
                sibling->color = sibling->parent->color;
                sibling->parent->color = black;
                nephew(sibling, position)->color = black;
                balancing(&(sibling->parent), sibling->position);
                sibling = sibling->parent;
                return;
            }
            else if (niece(sibling, position) && niece(sibling, position)->color == red)
            {
                niece(sibling, position)->color = black;
                sibling->color = red;
                balancing(&sibling, niece(sibling, position)->position);
            }
            else
            {
                sibling->color = red;
                sibling = sibling->parent;
            }
            correctblackheigt(sibling->parent, sibling->position);
        }
        void correctblackheigt(RedBlackTree<type_name> *leaf_parent, int position)
        {
            if (position == r)
                return correctionhelper(leaf_parent->left, r);
            correctionhelper(leaf_parent->right, l);
        }
        public:
            RBT() : head(NULL), size(0) {}
            void insert(type_name value)
            {
                std::cout << head << "\n";
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
                // debug();
                remove(&head, element);
                printing(head, 0);
                // printing(head, 0);
                if (head == NULL)
                {
                    std::cout << element << " SUCCESSFULLY DELETED! " << std::endl;
                    return;
                }
                // debug();
                std::map<RedBlackTree<type_name>* , std::vector<int> > mp;
				assert(check(head, mp));
                std::cout << element << " SUCCESSFULLY DELETED! " << std::endl;
                size--;
            }
    };
}