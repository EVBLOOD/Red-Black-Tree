/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_body.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 18:06:02 by sakllam           #+#    #+#             */
/*   Updated: 2022/09/02 20:39:17 by sakllam          ###   ########.fr       */
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
        bool          DB;
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
        RedBlackTree<type_name> *ROOT;
        
        
        RedBlackTree<type_name> *newnode(type_name value)
        {
            RedBlackTree<T> *newnode = ac.allocate(1);
            newnode->value = value;
            newnode->color = red;
            newnode->left = NULL;
            newnode->right = NULL;
            newnode->parent = NULL;
            newnode->DB = false;
            return newnode;
        }
        size_amount max(size_amount a, size_amount b)
        {
            if (a > b)
                return a;
            return b;
        }
        void    left_rotation(RedBlackTree<type_name> **root, bool clr, bool del)
        {
            // changing value only so no need to change the parent and color of it | else you may think of "blacking it"
            type_name tmprtval = (*root)->value;
            (*root)->value = (*root)->right->value;
            (*root)->right->value = tmprtval;
            if (clr)
                (*root)->color = del;

            RedBlackTree<type_name> *A = (*root); // the new root
            RedBlackTree<type_name> *B = (*root)->right; // the new left --> must change it's position and parent
            RedBlackTree<type_name> *C = B->right; // the new right --> must change it's position and parent
            RedBlackTree<type_name> *Aleft = A->left; // in case of extra wieghts in left of old root

            A->left = B;
            // start : changing color to red + position to the new one and parent also
            B->position = l;
            B->parent = A;
            if (clr)
                B->color = !del;
            // end

            A->right = C;
            // start : changing color to red + position to the new one and parent also
            if (C) // in case of using it just as part of {rotate left + rotate right} 
            {
                C->position = r;
                C->parent = A;
                if (clr)
                    C->color = !del;
            }
            // end
            
            B->right = B->left; // returning to the normal order to sqp the problem made while changing values of ex root and new one!
            if (B->right)
            {
                B->right->parent = B;
                B->right->position = r;
            }

            B->left = Aleft;
            // start : keeping childs undercontrole!
            if (Aleft)
                B->left->parent = B;
            //end
        }
        void    right_rotation(RedBlackTree<type_name> **root, bool clr, bool del)
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
                A->color = del;
            
            B->position = r;
            B->parent = A;
            if (clr)
                B->color = !del;
            A->left = C;
            if (C)
            {
                C->parent = A;
                if (clr)
                    C->color = !del;
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
                if ((*head)->right->right && (cerr->right->color == red))// || !cerr->left))
                    return left_rotation(head, true, false);
                right_rotation(&((*head)->right), false, false);
                left_rotation(head, true, false);
                return;
            }
            if ((*head)->left->left && (cerr->left->color == red))// || !cerr->right)) 
                return right_rotation(head, true, false);
            left_rotation(&((*head)->left), false, false);
            right_rotation(head, true, false);
        }
        int    recentlyadded(RedBlackTree<type_name> *x, type_name value)
        {
            if (x->left && x->left->value == value)
                return (l);
            return r;
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
        void    insert(RedBlackTree<type_name> **head, RedBlackTree<type_name> *nv, int position)
        {
            if (*head == NULL)
            {
                if (position == rt)
                     ROOT = nv;
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
        // void    balabla(RedBlackTree<type_name> **head, int position, RedBlackTree<type_name> *cerr)
        // {
        //     if (position == r)
        //     {
        //         if ((*head)->right->right && (cerr->right->color == red || !cerr->left))
        //             return left_rotation(head, true, false);
        //         right_rotation(&((*head)->right), false, false);
        //         left_rotation(head, true, false);
        //         return;
        //     }
        //     if ((*head)->left->left && (cerr->left->color == red || !cerr->right))
        //         return right_rotation(head, true, false);
        //     left_rotation(&((*head)->left), false, false);
        //     right_rotation(head, true, false);
        // }
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
                    ac.destroy(*head);
                    ac.deallocate(*head, 1);
                    *head = NULL;
                    if (color == black)
                        justfixit(parent, position);
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

        void justfixit(RedBlackTree<type_name> **head, int position)
        {
            std::cout << "head => " << (*head)->value << "\n";
            if (position == rt)
                return;
            if (position == r)
                return fixcases(head, (*head)->left, position);
            fixcases(head, (*head)->right, position);
        }

        void    balanceindeletion(RedBlackTree<type_name> **head, int position)
        {
            if (position == r)
            {
                puts("left rotation");
                if ((*head)->right->right)// && ((*head)->right->color == red))// || !(*head)->left)) // left oryit3jib
                    return left_rotation(head, false, false);
                right_rotation(&((*head)->right), false, false);
                left_rotation(head, false, false);
                return;
            }
                puts("right rotation");
            if ((*head)->left->left)// && ((*head)->left->color == red))// || !(*head)->right))
                return right_rotation(head, false, false);
                // return balanceindeletion(head, r);
            // puts("sss");
            // if ((*head)->left)
            left_rotation(&((*head)->left), false, false);
                // puts("holy fuck l");
            right_rotation(head, false, false);
        }

        bool blackchilds(RedBlackTree<type_name> *sibling)
        {
            return ((!sibling->left || sibling->left->color == black)
                && (!sibling->right || sibling->right->color == black));
        }
        
        RedBlackTree<type_name> *far_one(RedBlackTree<type_name> *sibling, int position)
        {
            if (position == r)
                return (sibling->left);
            return (sibling->right);
        }

         RedBlackTree<type_name> *near_one(RedBlackTree<type_name> *sibling, int position)
        {
            if (position == l)
                return (sibling->left);
            return (sibling->right);
        }

        bool faronecoloris(RedBlackTree<type_name> *sibling, int position, bool color)
        {
            if (position == r)
                return (far_one(sibling, position)->color == color);
            return (far_one(sibling, position)->color == color);
        }
        
        bool nearonecoloris(RedBlackTree<type_name> *sibling, int position, bool color)
        {
            if (position == r)
                return (sibling->right->color == color);
            return (sibling->left->color == color);
        }
        
        /*

            // if w->color = RED
            //     w->color ← BLACK //Case 1
            //     x->p->color ← RED //Case 1
            //     left-rotate(t, x->p) //Case 1
            //     w ← x->p->right //Case 1
            
            if w->left->color = BLACK and w->right->color = BLACK
                w->color ← RED //Case 2
                x ← x->p //Case 2
            else if w->right->color = BLACK
                w->left->color ← BLACK                //Case 3
                w->color ← RED          //Case 3
                right-rotate(t, w)        //Case 3
                w ← x->p->right         //Case 3
                w->color ← x->p->color //Case 4
                x->p->color ← BLACK //Case 4
                w->right->color ← BLACK //Case 4
                left-rotate(t, x->p) //Case 4
                x ← t->root Case 4
            else (same as then clause with "right" and "left" exchanged)
                x->color ← BLACK


        
        */
        void fixcases(RedBlackTree<type_name> **head, RedBlackTree<type_name> *sibling, int position) //mirror
        {
            std::cout << "sib : "<<  sibling->value << "\n";
            puts("???");
            // balanceindeletion(RedBlackTree<type_name> **head, int position)
            if (sibling->color == red)
            {
                            // if w->color = RED
            //     w->color ← BLACK //Case 1
            //     x->p->color ← RED //Case 1
            //     left-rotate(t, x->p) //Case 1
            //     w ← x->p->right //Case 1
                puts("case 2");
                puts("----------------------------");
                printing(*head, 0);
                (*head)->color = red;
                sibling->color = black;
                puts("start");
                balanceindeletion(head, sibling->position);
                //////
                if (position == l)
                    sibling = (*head)->left;
                else
                    sibling = (*head)->right;
                ////
                                puts("-----------------------------------------------");
                printing(*head, 0);

                // puts("end");
                // printing(*head, 0);
                // if ((*head)->left)
                    // (*head)->left->color = red;
                // if ((*head)->right)
                    // (*head)->right->color = red;
                    
                // if (position == l)
                //     return justfixit(&((*head)->left), l); // HMMMMMMM
                // return justfixit(&((*head)->right), r);
                // puts("kdhdj");
            }
            
            if (blackchilds(sibling))
            {
                puts("case 1");
                sibling->color = red;
                                puts("-----------------------------------------------");
                printing(*head, 0);

                // if ((*head)->color == black)
                    *head = (*head)->parent;
                    // return justfixit(&((*head)->parent), (*head)->position);
                // (*head)->color = black;
                // return;
            }

            

            
            if (near_one(sibling, position) && nearonecoloris(sibling, position, red))
                // && (!far_one(sibling, position) || faronecoloris(sibling, position, black)))
            {
                puts("case 3");
                near_one(sibling, position)->color = black;
                // sibling->color = red;
                            // puts("hola hola");
                // if (sibling->value > (*head)->value)
                    balanceindeletion(head, sibling->position);
                                    puts("-----------------------------------------------");
                printing(*head, 0);
                // else
                    // balanceindeletion(&((*head)->left), r);
                            // puts("hola hola bey");
                // return;
                // return justfixit(head, position);
            }
            if (far_one(sibling, position) && faronecoloris(sibling, position, red))
            {
                puts("case 4");
                far_one(sibling, position)->color = black;
                balanceindeletion(head, sibling->position);
                puts("-----------------------------------------------");
                printing(*head, 0);
                // justfixit(&((*head)->parent), (*head)->position);
                // puts("end");
            }
        }
        
        //  /*
        //             Case 1: The sibling of x is red.
        //                 we recolor the parent of x and x.sibling then we left rotate around x's parent.
        //         */
        //         if ((*head)->left && (*head)->left->color == red)
        //         {
        //             (*head)->color = red;
        //             (*head)->left->color = black; // double black!
        //             // rotate left the parent {head} left
        //             return;;
        //         }
        //         /*
        //             Case 2: The sibling of x is black and has two black children.
        //                 we recolor x.sibling to red, move x upwards to x.parent and check again for this newX.
        //         */
        //         if (!((*head)->left) || ((*head)->left->color == black && (!(*head)->left->right ||
        //             (*head)->left->right->color == black) && (!(*head)->left->left || (*head)->left->left->color == black)))
        //         {
        //             if ((*head)->left)
        //                 (*head)->left->color = red;
        //             return fixdoubleblack(&((*head)->parent), (*head)->position);
        //         }
        //         /*
        //             Case 3: The sibling of x is black with one black child to the right.
        //                 In this case, we recolor the sibling to red and sibling.leftChild to black,
        //                 then we right rotate around the sibling. After this we have case 4.
        //         */
        //         if ((*head)->left->color == black && (!(*head)->left->right || (*head)->left->right->color == black))
        //         {
        //             (*head)->left->color = red;
        //             if ((*head)->left->left)
        //                 (*head)->left->left = red;
        //             // right rotate sibling
        //         }
        //         /*
        //             Case 4: The sibling of x is black with one red child to the right.
        //                 we recolor the sibling to the color of x.parent and x.parent and sibling.rightChild to black.
        //                 Then we left rotate around x.parent.
        //         */
        //         (*head)->left->color = (*head)->color;
        //         (*head)->color = black;
        //         (*head)->left->right = black;
        //         // left rotate parent (*head);
        // void fixcase(RedBlackTree<type_name> **head, RedBlackTree<type_name> *sibling, int position)
        // {
        //         /*
        //             Case 1: The sibling of x is red.
        //                 we recolor the parent of x and x.sibling then we left rotate around x's parent.
        //         */
        //         if (sibling && sibling->color == black)
        //         {
        //             puts("case 1");
        //             sibling->color = red;
        //             if ((*head)->color == black && (*head)->position != rt)
        //                 return fixdoubleblack(&((*head)->parent), (*head)->position);
        //             (*head)->color = black;
        //             return;
        //         }
        //         if (sibling && sibling->color == red)
        //         {
        //             (*head)->color = red;
        //             sibling->color = black;
        //             balancedel(head, sibling->position);
        //         }
        //         /*
        //             Case 2: The sibling of x is black and has two black children.
        //                 we recolor x.sibling to red, move x upwards to x.parent and check again for this newX.
        //         */
        //         if (!(sibling) || (sibling->color == black && (!sibling->right ||
        //             sibling->right->color == black) && (!sibling->left || sibling->left->color == black)))
        //         {
        //             puts("case 2");
        //             if (sibling)
        //                 sibling->color = red;
        //             return fixdoubleblack(&((*head)->parent), (*head)->position);
        //         }
        //         /*
        //             Case 3: The sibling of x is black with one black child to the right.
        //                 In this case, we recolor the sibling to red and sibling.leftChild to black,
        //                 then we right rotate around the sibling. After this we have case 4.
        //         */
        //         if (sibling->color == black && (!sibling->right || sibling->right->color == black))
        //         {
        //             puts("case 3");
        //             sibling->color = red;
        //             if (sibling->left)
        //                 sibling->left->color = red;
        //             balancedel(&sibling, position);
        //             // right rotate sibling
        //         }
        //             puts("case 4");
        //         /*
        //             Case 4: The sibling of x is black with one red child to the right.
        //                 we recolor the sibling to the color of x.parent and x.parent and sibling.rightChild to black.
        //                 Then we left rotate around x.parent.
        //         */
        //         // if (sibling->color == black && sibling->right->color == red)
        //         sibling->color = (*head)->color;
        //         (*head)->color = black;
        //         if (sibling->right)
        //             sibling->right->color = black;
        //         balancedel(head, sibling->position);
        //         // left rotate parent (head);
        //         // left_rotation(head, true, true);
        // }
        // void    balancedel(RedBlackTree<type_name> **head, int position)
        // {
        //     if (position == r)
        //     {
        //         if ((*head)->right->right  && ((*head)->right->color == red || !(*head)->left))
        //             return left_rotation(head, true, false);
        //         right_rotation(&((*head)->right), false, false);
        //         left_rotation(head, true, false);
        //         return;
        //     }
        //     if ((*head)->left->left && ((*head)->left->color == red || !(*head)->right))
        //         return right_rotation(head, true, false);
        //     left_rotation(&((*head)->left), false, false);
        //     right_rotation(head, true, false);
        // }
        // void fixdoubleblack(RedBlackTree<type_name> **head, int position)
        // {
        //     puts("fixdoubleblack called");
        //     if ((*head)->position == rt)
        //         return;
        //     if (position == r) // checking the left subl
        //         return puts("right"), fixcases(head, (*head)->left, position);
        //     puts("left"); fixcases(head, (*head)->right, position);
        // }
        // void    balancingdel(RedBlackTree<type_name> **head, int position, bool test)
        // {
        //     if (position == r)
        //     {
        //         if ((*head)->right->right)
        //         {
                    
        //         puts ("right right");
        //             return left_rotation(head, test, test);
        //         }
        //         right_rotation(&((*head)->right), !test, test);
        //         left_rotation(head, test, test);
        //         return;
        //     }
        //     if ((*head)->left->left)
        //     {
        //         puts ("left left");
        //         return right_rotation(head, test, test);
        //     }
        //     left_rotation(&((*head)->left), !test, test);
        //     right_rotation(head, test, test);
        // }
        // void fixblack(RedBlackTree<type_name> **head, int position)
        // {
        //     if (position == r)
        //     {
        //         if (!((*head)->left))
        //             return;
        //         if ((*head)->left->right == NULL && (*head)->left->left == NULL)
        //         {
        //             puts("coloring");
        //             (*head)->color = black;
        //             (*head)->left->color = red;
        //             return;
        //         }
        //         puts("bal");
        //         // if ((*head)->left->color != black)
                    
        //         balancingdel(head, (*head)->position, true);
        //         return;
        //     }
        //     if (!((*head)->right))
        //         return;
        //     if ((*head)->right->right == NULL && (*head)->right->left == NULL)
        //     {
        //          puts("coloring");
        //         (*head)->color = black;
        //         (*head)->right->color = red;
        //         return ;
        //     }
        //         puts("bal");
        //     balancingdel(head, (*head)->position, true);
        //     if ((*head)->left->left)
        //         fixblack(&((*head)->left->left), (*head)->left->left->position);
        //     if ((*head)->left->right)
        //         fixblack(&((*head)->left->right), (*head)->left->right->position);
        //     std::cout << "ckeck: " << (*head)->value << "\n";
        // }
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