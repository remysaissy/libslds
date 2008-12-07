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

static void *__grandparent(void *node, unsigned int m)
{
    if ((node != NULL) && (GET_FIELD(node, m, redblack_tree_t)->parent != NULL))
        return (GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->parent);
    else
        return (NULL);
}

static void *__uncle(void *node, unsigned int m)
{
    void    *grandpa = __grandparent(node, m);

    if (grandpa == NULL)
      return (NULL);
    if (GET_FIELD(node, m, redblack_tree_t)->parent == GET_FIELD(grandpa, m, redblack_tree_t)->left)
        return GET_FIELD(grandpa, m, redblack_tree_t)->right;
    else
        return GET_FIELD(grandpa, m, redblack_tree_t)->left;
}

static void *__sibling(void *node, unsigned int m)
{
    if (node == GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->left)
        return (GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->right);
    else
      return (GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->left);
}

static void __insert_case5(void *node, unsigned int m)
{
  void      *grandpa;

  grandpa = __grandparent(node, m);
  GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->is_red = false;
  GET_FIELD(grandpa, m, redblack_tree_t)->is_red = true;
  if ((node == GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->left)
      && (GET_FIELD(node, m, redblack_tree_t)->parent == GET_FIELD(grandpa, m, redblack_tree_t)->left))
  {
    avl_parent_rotate_with_right(grandpa, m);
  }
  else
  {
        /*
         * Here, (n == n->parent->right) && (n->parent == g->right).
         */
    avl_parent_rotate_with_left(grandpa, m);
  }
}

static void __insert_case4(void *node, unsigned int m)
{
  void  *grandpa;

  grandpa = __grandparent(node, m);
    if ((node == GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->right)
        && (GET_FIELD(node, m, redblack_tree_t)->parent == GET_FIELD(grandpa, m, redblack_tree_t)->left))
    {
        avl_parent_rotate_with_left(GET_FIELD(node, m, redblack_tree_t)->parent, m);
        node = GET_FIELD(node, m, redblack_tree_t)->left;
    }
    else
      if ((node == GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->left)
          && (GET_FIELD(node, m, redblack_tree_t)->parent == GET_FIELD(grandpa, m, redblack_tree_t)->right))
      {
        avl_parent_rotate_with_right(GET_FIELD(node, m, redblack_tree_t)->parent, m);
        node = GET_FIELD(node, m, redblack_tree_t)->right;
      }
    __insert_case5(node, m);
}

static void __insert_case1(void *node, unsigned int m);

static void __insert_case3(void *node, unsigned int m)
{
    void    *uncle;
    void    *grandpa;

    uncle = __uncle(node, m);
    grandpa = NULL;
    if ((uncle != NULL) && (GET_FIELD(uncle, m, redblack_tree_t)->is_red == true))
    {
        GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->is_red = false;
        GET_FIELD(uncle, m, redblack_tree_t)->is_red = false;
        grandpa = __grandparent(node, m);
        GET_FIELD(grandpa, m, redblack_tree_t)->is_red = true;
        __insert_case1(grandpa, m);
    }
    else
    {
        __insert_case4(node, m);
    }
}

static void __insert_case2(void *node, unsigned int m)
{
    if (GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->is_red == false)
        return; /* Tree is still valid */
    else
        __insert_case3(node, m);
}

static void __insert_case1(void *node, unsigned int m)
{
    if (GET_FIELD(node, m, redblack_tree_t)->parent == NULL)
      GET_FIELD(node, m, redblack_tree_t)->is_red = false;
    else
        __insert_case2(node, m);
}

static void __make_some_painting(void *node, unsigned int m)
{
  __insert_case1(node, m);
}


static void __make_some_repainting(void *node, bool old_was_red, unsigned int m)
{
  void  *n;
  void  *s;

  return;
  if (old_was_red == false)
    {
      if (GET_FIELD(node, m, redblack_tree_t)->is_red == true)
        GET_FIELD(node, m, redblack_tree_t)->is_red = false;
      else
      {
        /* delete_case1(child): */
        n = node;
        /* this loop performs tail recursion on delete_case1(n) */
        while (1)
        {
          /* delete_case1(n): */
          if (GET_FIELD(n, m, redblack_tree_t)->parent != NULL)
          {
            /* delete_case2(n): */

            s = __sibling(n, m);
            if (GET_FIELD(s, m, redblack_tree_t)->is_red == true)
            {
              GET_FIELD(GET_FIELD(n, m, redblack_tree_t)->parent, m, redblack_tree_t)->is_red = true;
              GET_FIELD(s, m, redblack_tree_t)->is_red = false;
              if (n == GET_FIELD(GET_FIELD(n, m, redblack_tree_t)->parent, m, redblack_tree_t)->left)
                avl_parent_rotate_with_left(GET_FIELD(n, m, redblack_tree_t)->parent, m);
              else
                avl_parent_rotate_with_right(GET_FIELD(n, m, redblack_tree_t)->parent, m);
            }
            /* delete_case3(n): */

            s = __sibling(n, m);
            if ((GET_FIELD(GET_FIELD(n, m, redblack_tree_t)->parent, m, redblack_tree_t)->is_red == false)
                  && (GET_FIELD(s, m, redblack_tree_t)->is_red == false)
                  && (GET_FIELD(GET_FIELD(s, m, redblack_tree_t)->left, m, redblack_tree_t)->is_red == false)
                  && (GET_FIELD(GET_FIELD(s, m, redblack_tree_t)->right, m, redblack_tree_t)->is_red == false))
            {
              GET_FIELD(s, m, redblack_tree_t)->is_red = true;
              /* delete_case1(n->parent): */
              n = GET_FIELD(n, m, redblack_tree_t)->parent;
              continue; /* tail recursion loop */
            }
            else
            {
              /* delete_case4(n): */

              //s = sibling(n);//not needed
              if ((GET_FIELD(GET_FIELD(n, m, redblack_tree_t)->parent, m, redblack_tree_t)->is_red == true)
                  && (GET_FIELD(s, m, redblack_tree_t)->is_red == false)
                  && (GET_FIELD(GET_FIELD(s, m, redblack_tree_t)->left, m, redblack_tree_t)->is_red == false)
                  && (GET_FIELD(GET_FIELD(s, m, redblack_tree_t)->right, m, redblack_tree_t)->is_red == false))
              {
                GET_FIELD(s, m, redblack_tree_t)->is_red = true;
                GET_FIELD(GET_FIELD(n, m, redblack_tree_t)->parent, m, redblack_tree_t)->is_red = false;
                break;
              }
              else
              {
                /* delete_case5(n): */

                //s = sibling(n);//not needed
                if ((n == GET_FIELD(GET_FIELD(n, m, redblack_tree_t)->parent, m, redblack_tree_t)->left)
                    && (GET_FIELD(s, m, redblack_tree_t)->is_red == false)
                    && (GET_FIELD(GET_FIELD(s, m, redblack_tree_t)->left, m, redblack_tree_t)->is_red == true)
                    && (GET_FIELD(GET_FIELD(s, m, redblack_tree_t)->right, m, redblack_tree_t)->is_red = false))
                {
                  GET_FIELD(s, m, redblack_tree_t)->is_red = true;
                  GET_FIELD(GET_FIELD(s, m, redblack_tree_t)->left, m, redblack_tree_t)->is_red = false;
                  avl_parent_rotate_with_right(s, m);
                }
                else if ((n == GET_FIELD(GET_FIELD(n, m, redblack_tree_t)->parent, m, redblack_tree_t)->right)
                    && (GET_FIELD(s, m, redblack_tree_t)->is_red == false)
                    && (GET_FIELD(GET_FIELD(s, m, redblack_tree_t)->right, m, redblack_tree_t)->is_red == true)
                    && (GET_FIELD(GET_FIELD(s, m, redblack_tree_t)->left, m, redblack_tree_t)->is_red == false))
                {
                  GET_FIELD(s, m, redblack_tree_t)->is_red = true;
                  GET_FIELD(GET_FIELD(s, m, redblack_tree_t)->right, m, redblack_tree_t)->is_red = false;
                  avl_parent_rotate_with_left(s, m);
                }
                /* delete_case6(n): */

                s = __sibling(n, m);
                GET_FIELD(s, m, redblack_tree_t)->is_red = GET_FIELD(GET_FIELD(n, m, redblack_tree_t)->parent, m, redblack_tree_t)->is_red;
                GET_FIELD(GET_FIELD(n, m, redblack_tree_t)->parent, m, redblack_tree_t)->is_red = false;
                if (n == GET_FIELD(GET_FIELD(n, m, redblack_tree_t)->parent, m, redblack_tree_t)->left)
                {
                  /*
                   * Here, s->right->color == RED.
                   */
                  GET_FIELD(GET_FIELD(s, m, redblack_tree_t)->right, m, redblack_tree_t)->is_red = false;
                  avl_parent_rotate_with_left(GET_FIELD(n, m, redblack_tree_t)->parent, m);
                }
                else
                {
                  /*
                   * Here, s->left->color == RED.
                   */
                  GET_FIELD(GET_FIELD(s, m, redblack_tree_t)->left, m, redblack_tree_t)->is_red = false;
                  avl_parent_rotate_with_right(GET_FIELD(n, m, redblack_tree_t)->parent, m);
                }
                break;
              }
            }
          }
          else
            break;
          }
        }
    }
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
    btree_compare_p compare_func)
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
    GET_FIELD(new, m, redblack_tree_t)->is_red = false;
  }
  else
  {
    it = *tree;
    while (1)
    {
      ret = compare_func(it, new);
      switch (ret)
      {
        case BTREE_LEFT:
        if (GET_FIELD(it, m, redblack_tree_t)->left == NULL)
        {
          GET_FIELD(it, m, redblack_tree_t)->left = new;
          GET_FIELD(new, m, redblack_tree_t)->parent = it;
          __make_some_painting(new, m);
          return (true);
        }
        else
        it = GET_FIELD(it, m, redblack_tree_t)->left;
        break;
        case BTREE_RIGHT:
        if (GET_FIELD(it, m, redblack_tree_t)->right == NULL)
        {
          GET_FIELD(it, m, redblack_tree_t)->right = new;
          GET_FIELD(new, m, redblack_tree_t)->parent = it;
          __make_some_painting(new, m);
          return (true);
        }
        else
        it = GET_FIELD(it, m, redblack_tree_t)->right;
        break;
        case BTREE_MATCH:
        return (false);
      }
    }
  }
  return (true);
}

/* TODO: to be coded. */
void *_redblack_tree_remove(void **tree,
                    void *key,
                    unsigned int m,
                    btree_compare_p compare_func,
                    btree_compare_key_p compare_key_func)
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
      case BTREE_LEFT:
        left_prev = it;
        right_prev = NULL;
        it = GET_FIELD(it, m, redblack_tree_t)->left;
        break;
      case BTREE_RIGHT:
        left_prev = NULL;
        right_prev = it;
        it = GET_FIELD(it, m, redblack_tree_t)->right;
        break;
      case BTREE_MATCH:
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
          __make_some_repainting(node, GET_FIELD(it, m, redblack_tree_t)->is_red, m);
          return (it);
    }
  }
  return (NULL);
}

/* TODO: to be coded. */
bool _redblack_tree_graft(void **tree,
    void *subtree,
    unsigned int m,
    btree_compare_p compare_func)
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
      case BTREE_LEFT:
      left_prev = it;
      right_prev = NULL;
      it = GET_FIELD(it, m, redblack_tree_t)->left;
      break;
      case BTREE_RIGHT:
      left_prev = NULL;
      right_prev = it;
      it = GET_FIELD(it, m, redblack_tree_t)->right;
      break;
      case BTREE_MATCH:
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
                   btree_compare_key_p compare_key_func)
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
      case BTREE_LEFT:
        left_prev = it;
        right_prev = NULL;
        it = GET_FIELD(it, m, redblack_tree_t)->left;
        break;
      case BTREE_RIGHT:
        left_prev = NULL;
        right_prev = it;
        it = GET_FIELD(it, m, redblack_tree_t)->right;
        break;
      case BTREE_MATCH:
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
