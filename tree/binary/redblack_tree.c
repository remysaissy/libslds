/*
 * This file is part of libslds

 * Copyright (C) Remy Saissy <remy.saissy@gmail.com>
 * libslds is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * libslds is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include    <tree.h>

#include    "include/avl_rotation.h"

/* Helpers. */

//static void *__grandparent(void *node, unsigned int m)
//{
//    if ((node != NULL) && (GET_FIELD(node, m, redblack_tree_t)->parent != NULL))
//        return (GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->parent);
//    else
//        return (NULL);
//}
//
//static void *__uncle(void *node, unsigned int m)
//{
//    void    *grandpa = __grandparent(node, m);
//
//    if (grandpa == NULL)
//      return (NULL);
//    if (GET_FIELD(node, m, redblack_tree_t)->parent == GET_FIELD(grandpa, m, redblack_tree_t)->left)
//        return GET_FIELD(grandpa, m, redblack_tree_t)->right;
//    else
//        return GET_FIELD(grandpa, m, redblack_tree_t)->left;
//}

//static void *__sibling(void *node, unsigned int m)
//{
//    if (node == GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->left)
//        return (GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->right);
//    else
//      return (GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->left);
//}

//static void __insert_case5(void *node, unsigned int m)
//{
//  void      *grandpa;
//
//  grandpa = __grandparent(node, m);
//  GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->colour = black;
//  GET_FIELD(grandpa, m, redblack_tree_t)->colour = red;
//  if ((node == GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->left)
//      && (GET_FIELD(node, m, redblack_tree_t)->parent == GET_FIELD(grandpa, m, redblack_tree_t)->left))
//  {
//    avl_parent_rotate_with_right(grandpa, m);
//  }
//  else
//  {
//        /*
//         * Here, (n == n->parent->right) && (n->parent == g->right).
//         */
//    avl_parent_rotate_with_left(grandpa, m);
//  }
//}
//
//static void __insert_case4(void *node, unsigned int m)
//{
//  void  *grandpa;
//
//  grandpa = __grandparent(node, m);
//    if ((node == GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->right)
//        && (GET_FIELD(node, m, redblack_tree_t)->parent == GET_FIELD(grandpa, m, redblack_tree_t)->left))
//    {
//        avl_parent_rotate_with_left(GET_FIELD(node, m, redblack_tree_t)->parent, m);
//        node = GET_FIELD(node, m, redblack_tree_t)->left;
//    }
//    else
//      if ((node == GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->left)
//          && (GET_FIELD(node, m, redblack_tree_t)->parent == GET_FIELD(grandpa, m, redblack_tree_t)->right))
//      {
//        avl_parent_rotate_with_right(GET_FIELD(node, m, redblack_tree_t)->parent, m);
//        node = GET_FIELD(node, m, redblack_tree_t)->right;
//      }
//    __insert_case5(node, m);
//}
//
//static void __insert_case1(void *node, unsigned int m);
//
//static void __insert_case3(void *node, unsigned int m)
//{
//    void    *uncle;
//    void    *grandpa;
//
//    uncle = __uncle(node, m);
//    grandpa = NULL;
//    if ((uncle != NULL) && (GET_FIELD(uncle, m, redblack_tree_t)->colour == red))
//    {
//        GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->colour = black;
//        GET_FIELD(uncle, m, redblack_tree_t)->colour = black;
//        grandpa = __grandparent(node, m);
//        GET_FIELD(grandpa, m, redblack_tree_t)->colour = red;
//        __insert_case1(grandpa, m);
//    }
//    else
//    {
//        __insert_case4(node, m);
//    }
//}
//
//static void __insert_case2(void *node, unsigned int m)
//{
//    if (GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->colour == black)
//        return; /* Tree is still valid */
//    else
//        __insert_case3(node, m);
//}
//
//static void __insert_case1(void *node, unsigned int m)
//{
//    if (GET_FIELD(node, m, redblack_tree_t)->parent == NULL)
//      GET_FIELD(node, m, redblack_tree_t)->colour = black;
//    else
//        __insert_case2(node, m);
//}

static void __make_some_painting(void *node, unsigned int m)
{
//  void  *y;
//
////  __insert_case1(node, m);
//  GET_FIELD(node, m, redblack_tree_t)->colour = red;
//    while ((GET_FIELD(node, m, redblack_tree_t)->parent != NULL)
//        && (GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->colour == red))
//    {
//       if (GET_FIELD(node, m, redblack_tree_t)->parent == GET_FIELD(GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->parent, m, redblack_tree_t)->left)
//       {
//         /* If x's parent is a left, y is x's right 'uncle' */
//         y = GET_FIELD(GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->parent, m, redblack_tree_t)->right;
//         if (GET_FIELD(y, m, redblack_tree_t)->colour == red)
//         {
//           /* case 1 - change the colours */
//           GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->colour = black;
//           GET_FIELD(y, m, redblack_tree_t)->colour = black;
//           GET_FIELD(GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->parent, m, redblack_tree_t)->colour = red;
//           /* Move x up the tree */
//           node = GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->parent;
//         }
//         else
//         {
//               /* y is a black node */
//               if (node == GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->right)
//               {
//                   /* and x is to the right */
//                   /* case 2 - move x up and rotate */
//                   node = GET_FIELD(node, m, redblack_tree_t)->parent;
//                   avl_parent_rotate_with_left(node, m);
//               }
//               /* case 3 */
//               GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->colour = black;
//               GET_FIELD(GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->parent, m, redblack_tree_t)->colour = red;
//               avl_parent_rotate_with_right(GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->parent, m);
//         }
//       }
//       else
//       {
//         /* If x's parent is a right, y is x's left 'uncle' */
//         y = GET_FIELD(GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->parent, m, redblack_tree_t)->left;
//         if (GET_FIELD(y, m, redblack_tree_t)->colour == red)
//         {
//           /* case 1 - change the colours */
//           GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->colour = black;
//           GET_FIELD(y, m, redblack_tree_t)->colour = black;
//           GET_FIELD(GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->parent, m, redblack_tree_t)->colour = red;
//           /* Move x up the tree */
//           node = GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->parent;
//         }
//         else
//         {
//               /* y is a black node */
//               if (node == GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->left)
//               {
//                   /* and x is to the left */
//                   /* case 2 - move x up and rotate */
//                   node = GET_FIELD(node, m, redblack_tree_t)->parent;
//                   avl_parent_rotate_with_right(node, m);
//               }
//               /* case 3 */
//               GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->colour = black;
//               GET_FIELD(GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->parent, m, redblack_tree_t)->colour = red;
//               avl_parent_rotate_with_left(GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->parent, m);
//         }
//       }
//    }
}


static void __make_some_repainting(void *node, bool old_was_red, unsigned int m)
{
//  void  *n;
//  void  *s;
//
//  return;
//  if (old_was_red == false)
//    {
//      if (GET_FIELD(node, m, redblack_tree_t)->colour == red)
//        GET_FIELD(node, m, redblack_tree_t)->colour = black;
//      else
//      {
//        /* delete_case1(child): */
//        n = node;
//        /* this loop performs tail recursion on delete_case1(n) */
//        while (1)
//        {
//          /* delete_case1(n): */
//          if (GET_FIELD(n, m, redblack_tree_t)->parent != NULL)
//          {
//            /* delete_case2(n): */
//
//            s = __sibling(n, m);
//            if (GET_FIELD(s, m, redblack_tree_t)->colour == red)
//            {
//              GET_FIELD(GET_FIELD(n, m, redblack_tree_t)->parent, m, redblack_tree_t)->colour = red;
//              GET_FIELD(s, m, redblack_tree_t)->colour = black;
//              if (n == GET_FIELD(GET_FIELD(n, m, redblack_tree_t)->parent, m, redblack_tree_t)->left)
//                avl_parent_rotate_with_left(GET_FIELD(n, m, redblack_tree_t)->parent, m);
//              else
//                avl_parent_rotate_with_right(GET_FIELD(n, m, redblack_tree_t)->parent, m);
//            }
//            /* delete_case3(n): */
//
//            s = __sibling(n, m);
//            if ((GET_FIELD(GET_FIELD(n, m, redblack_tree_t)->parent, m, redblack_tree_t)->colour == black)
//                  && (GET_FIELD(s, m, redblack_tree_t)->colour == black)
//                  && (GET_FIELD(GET_FIELD(s, m, redblack_tree_t)->left, m, redblack_tree_t)->colour == black)
//                  && (GET_FIELD(GET_FIELD(s, m, redblack_tree_t)->right, m, redblack_tree_t)->colour == black))
//            {
//              GET_FIELD(s, m, redblack_tree_t)->colour = red;
//              /* delete_case1(n->parent): */
//              n = GET_FIELD(n, m, redblack_tree_t)->parent;
//              continue; /* tail recursion loop */
//            }
//            else
//            {
//              /* delete_case4(n): */
//
//              //s = sibling(n);//not needed
//              if ((GET_FIELD(GET_FIELD(n, m, redblack_tree_t)->parent, m, redblack_tree_t)->colour == red)
//                  && (GET_FIELD(s, m, redblack_tree_t)->colour == black)
//                  && (GET_FIELD(GET_FIELD(s, m, redblack_tree_t)->left, m, redblack_tree_t)->colour == black)
//                  && (GET_FIELD(GET_FIELD(s, m, redblack_tree_t)->right, m, redblack_tree_t)->colour == black))
//              {
//                GET_FIELD(s, m, redblack_tree_t)->colour = red;
//                GET_FIELD(GET_FIELD(n, m, redblack_tree_t)->parent, m, redblack_tree_t)->colour = black;
//                break;
//              }
//              else
//              {
//                /* delete_case5(n): */
//
//                //s = sibling(n);//not needed
//                if ((n == GET_FIELD(GET_FIELD(n, m, redblack_tree_t)->parent, m, redblack_tree_t)->left)
//                    && (GET_FIELD(s, m, redblack_tree_t)->colour == black)
//                    && (GET_FIELD(GET_FIELD(s, m, redblack_tree_t)->left, m, redblack_tree_t)->colour == red)
//                    && (GET_FIELD(GET_FIELD(s, m, redblack_tree_t)->right, m, redblack_tree_t)->colour = black))
//                {
//                  GET_FIELD(s, m, redblack_tree_t)->colour = red;
//                  GET_FIELD(GET_FIELD(s, m, redblack_tree_t)->left, m, redblack_tree_t)->colour = black;
//                  avl_parent_rotate_with_right(s, m);
//                }
//                else if ((n == GET_FIELD(GET_FIELD(n, m, redblack_tree_t)->parent, m, redblack_tree_t)->right)
//                    && (GET_FIELD(s, m, redblack_tree_t)->colour == black)
//                    && (GET_FIELD(GET_FIELD(s, m, redblack_tree_t)->right, m, redblack_tree_t)->colour == red)
//                    && (GET_FIELD(GET_FIELD(s, m, redblack_tree_t)->left, m, redblack_tree_t)->colour == black))
//                {
//                  GET_FIELD(s, m, redblack_tree_t)->colour = red;
//                  GET_FIELD(GET_FIELD(s, m, redblack_tree_t)->right, m, redblack_tree_t)->colour = black;
//                  avl_parent_rotate_with_left(s, m);
//                }
//                /* delete_case6(n): */
//
//                s = __sibling(n, m);
//                GET_FIELD(s, m, redblack_tree_t)->colour = GET_FIELD(GET_FIELD(n, m, redblack_tree_t)->parent, m, redblack_tree_t)->colour;
//                GET_FIELD(GET_FIELD(n, m, redblack_tree_t)->parent, m, redblack_tree_t)->colour = black;
//                if (n == GET_FIELD(GET_FIELD(n, m, redblack_tree_t)->parent, m, redblack_tree_t)->left)
//                {
//                  /*
//                   * Here, s->right->color == RED.
//                   */
//                  GET_FIELD(GET_FIELD(s, m, redblack_tree_t)->right, m, redblack_tree_t)->colour = black;
//                  avl_parent_rotate_with_left(GET_FIELD(n, m, redblack_tree_t)->parent, m);
//                }
//                else
//                {
//                  /*
//                   * Here, s->left->color == RED.
//                   */
//                  GET_FIELD(GET_FIELD(s, m, redblack_tree_t)->left, m, redblack_tree_t)->colour = black;
//                  avl_parent_rotate_with_right(GET_FIELD(n, m, redblack_tree_t)->parent, m);
//                }
//                break;
//              }
//            }
//          }
//          else
//            break;
//          }
//        }
//    }
}





/* Implementation. */

bool _redblack_tree_init(void *tree,
    unsigned int m)
{
  if (tree)
  {
    GET_FIELD(tree, m, redblack_tree_t)->left = NULL;
    GET_FIELD(tree, m, redblack_tree_t)->right = NULL;
    GET_FIELD(tree, m, redblack_tree_t)->parent = NULL;
    return (true);
  }
  return (false);
}

bool _redblack_tree_insert(void **tree,
                          void *new,
                          unsigned int m,
                          bst_tree_compare_p compare_func)
{
  void *it;
  int ret;

  if (tree == NULL
      || new == NULL
      || compare_func == NULL)
  return (false);
  GET_FIELD(new, m, redblack_tree_t)->left = NULL;
  GET_FIELD(new, m, redblack_tree_t)->right = NULL;
  GET_FIELD(new, m, redblack_tree_t)->parent = NULL;
  if (*tree == NULL)
  {
    *tree = new;
  }
  else
  {
    it = *tree;
    while (1)
    {
      ret = compare_func(it, new);
      switch (ret)
      {
        case BST_TREE_LEFT:
        if (GET_FIELD(it, m, redblack_tree_t)->left == NULL)
        {
          GET_FIELD(it, m, redblack_tree_t)->left = new;
          GET_FIELD(new, m, redblack_tree_t)->parent = it;
          goto redblack_insert_success;
        }
        else
        it = GET_FIELD(it, m, redblack_tree_t)->left;
        break;
        case BST_TREE_RIGHT:
        if (GET_FIELD(it, m, redblack_tree_t)->right == NULL)
        {
          GET_FIELD(it, m, redblack_tree_t)->right = new;
          GET_FIELD(new, m, redblack_tree_t)->parent = it;
          goto redblack_insert_success;
        }
        else
        it = GET_FIELD(it, m, redblack_tree_t)->right;
        break;
        case BST_TREE_MATCH:
        return (false);
      }
    }
  }
redblack_insert_success:
  __make_some_painting(new, m);
  GET_FIELD(*tree, m, redblack_tree_t)->colour = black;
  return (true);
}

/* TODO: to be coded. */
void *_redblack_tree_remove(void **tree,
                    void *key,
                    unsigned int m,
                    bst_tree_compare_p compare_func,
                    bst_tree_compare_key_p compare_key_func)
{
  void *left_prev;
  void *right_prev;
  void *it;
  void *parent;
  void *node;
  int ret;

  if (tree == NULL
          || *tree == NULL
          || compare_func == NULL
          || compare_key_func == NULL)
    return (NULL);
  it = *tree;
  left_prev = NULL;
  right_prev = NULL;
  while (it)
  {
    ret = compare_key_func(it, key);
    switch (ret)
    {
      case BST_TREE_LEFT:
        left_prev = it;
        right_prev = NULL;
        it = GET_FIELD(it, m, redblack_tree_t)->left;
        break;
      case BST_TREE_RIGHT:
        left_prev = NULL;
        right_prev = it;
        it = GET_FIELD(it, m, redblack_tree_t)->right;
        break;
      case BST_TREE_MATCH:
        node = NULL;
        if (GET_FIELD(it, m, redblack_tree_t)->left == NULL
              && GET_FIELD(it, m, redblack_tree_t)->right == NULL
              && GET_FIELD(it, m, redblack_tree_t)->parent == NULL)
            *tree = NULL;
          else
          {
            if (GET_FIELD(it, m, redblack_tree_t)->left != NULL)
            {
              /* Get the node deepest node on the right of the left child. */

              node = GET_FIELD(it, m, redblack_tree_t)->left;
              while (GET_FIELD(node, m, redblack_tree_t)->right != NULL)
                node = GET_FIELD(node, m, redblack_tree_t)->right;
              if (GET_FIELD(node, m, redblack_tree_t)->parent != it)
              {
                parent = GET_FIELD(node, m, redblack_tree_t)->parent;
                GET_FIELD(parent, m, redblack_tree_t)->right = GET_FIELD(node, m, redblack_tree_t)->left;
                if (GET_FIELD(node, m, redblack_tree_t)->left != NULL)
                  GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->left, m, redblack_tree_t)->parent = parent;
                GET_FIELD(node, m, redblack_tree_t)->left = GET_FIELD(it, m, redblack_tree_t)->left;
                GET_FIELD(GET_FIELD(it, m, redblack_tree_t)->left, m, redblack_tree_t)->parent = node;
              }
              GET_FIELD(node, m, redblack_tree_t)->right = GET_FIELD(it, m, redblack_tree_t)->right;
              if (GET_FIELD(it, m, redblack_tree_t)->right != NULL)
                GET_FIELD(GET_FIELD(it, m, redblack_tree_t)->right, m, redblack_tree_t)->parent = node;
            }
            else
            {
              if (GET_FIELD(it, m, redblack_tree_t)->right != NULL)
              {
                /* Get the node deepest node on the left of the right child. */

                node = GET_FIELD(it, m, redblack_tree_t)->right;
                while (GET_FIELD(node, m, redblack_tree_t)->left != NULL)
                  node = GET_FIELD(node, m, redblack_tree_t)->left;
                if (GET_FIELD(node, m, redblack_tree_t)->parent != it)
                {
                  parent = GET_FIELD(node, m, redblack_tree_t)->parent;
                  GET_FIELD(parent, m, redblack_tree_t)->left = GET_FIELD(node, m, redblack_tree_t)->right;
                  if (GET_FIELD(node, m, redblack_tree_t)->right != NULL)
                    GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->right, m, redblack_tree_t)->parent = parent;
                  GET_FIELD(node, m, redblack_tree_t)->right = GET_FIELD(it, m, redblack_tree_t)->right;
                  GET_FIELD(GET_FIELD(it, m, redblack_tree_t)->right, m, redblack_tree_t)->parent = node;
                }
                GET_FIELD(node, m, redblack_tree_t)->left = GET_FIELD(it, m, redblack_tree_t)->left;
                if (GET_FIELD(it, m, redblack_tree_t)->left != NULL)
                  GET_FIELD(GET_FIELD(it, m, redblack_tree_t)->left, m, redblack_tree_t)->parent = node;
              }
            }
            if (left_prev != NULL)
            {
                GET_FIELD(left_prev, m, redblack_tree_t)->left = node;
                if (node != NULL)
                  GET_FIELD(node, m, redblack_tree_t)->parent = left_prev;
            }
            else
            {
              if (right_prev != NULL)
              {
                GET_FIELD(right_prev, m, redblack_tree_t)->right = node;
                if (node != NULL)
                  GET_FIELD(node, m, redblack_tree_t)->parent = right_prev;
              }
              else
                *tree = node;
            }
          }
          __make_some_repainting(node, GET_FIELD(it, m, redblack_tree_t)->colour, m);
          return (it);
    }
  }
  return (NULL);
}

/* TODO: to be coded. */
bool _redblack_tree_graft(void **tree,
    void *subtree,
    unsigned int m,
    bst_tree_compare_p compare_func)
{
  void *it;
  int ret;
  void *left_prev;
  void *right_prev;

  if (tree == NULL
      || *tree == NULL
      || subtree == NULL
      || compare_func == NULL)
  return (false);

  it = *tree;
  left_prev = NULL;
  right_prev = NULL;
  while (it)
  {
    ret = compare_func(it, subtree);
    switch (ret)
    {
      case BST_TREE_LEFT:
      left_prev = it;
      right_prev = NULL;
      it = GET_FIELD(it, m, redblack_tree_t)->left;
      break;
      case BST_TREE_RIGHT:
      left_prev = NULL;
      right_prev = it;
      it = GET_FIELD(it, m, redblack_tree_t)->right;
      break;
      case BST_TREE_MATCH:
      return (false);
    }
  }
  if (left_prev != NULL)
  {
    GET_FIELD(left_prev, m, redblack_tree_t)->left = subtree;
    GET_FIELD(subtree, m, redblack_tree_t)->parent = left_prev;
  }
  else
  {
    if (right_prev != NULL)
    {
      GET_FIELD(right_prev, m, redblack_tree_t)->right = subtree;
      GET_FIELD(subtree, m, redblack_tree_t)->parent = right_prev;
    }
    else
    *tree = subtree;
  }
  return (true);
}

void *_redblack_tree_prune(void **tree,
                   void *key,
                   unsigned int m,
                   bst_tree_compare_key_p compare_key_func)
{
  void *it;
  void *left_prev;
  void *right_prev;
  int ret;

  if (tree == NULL || *tree == NULL || compare_key_func == NULL)
    return (NULL);
  it = *tree;
  left_prev = NULL;
  right_prev = NULL;
  while (it)
  {
    ret = compare_key_func(it, key);
    switch (ret)
    {
      case BST_TREE_LEFT:
        left_prev = it;
        right_prev = NULL;
        it = GET_FIELD(it, m, redblack_tree_t)->left;
        break;
      case BST_TREE_RIGHT:
        left_prev = NULL;
        right_prev = it;
        it = GET_FIELD(it, m, redblack_tree_t)->right;
        break;
      case BST_TREE_MATCH:
        if (left_prev != NULL)
          GET_FIELD(left_prev, m, redblack_tree_t)->left = NULL;
        else
        {
          if (right_prev != NULL)
            GET_FIELD(right_prev, m, redblack_tree_t)->right = NULL;
          else
            *tree = NULL;
        }
        GET_FIELD(it, m, redblack_tree_t)->parent = NULL;
        return (it);
    }
  }
  return (NULL);
}
