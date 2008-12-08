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


bool _btree_init(void *tree,
    unsigned int m)
{
  if (tree)
  {
    GET_FIELD(tree, m, btree_t)->left = NULL;
    GET_FIELD(tree, m, btree_t)->right = NULL;
    return (true);
  }
  return (false);
}

bool _btree_insert(void **tree,
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
  GET_FIELD(new, m, btree_t)->left = NULL;
  GET_FIELD(new, m, btree_t)->right = NULL;
  if (*tree == NULL)
  *tree = new;
  else
  {
    it = *tree;
    while (1)
    {
      ret = compare_func(it, new);
      switch (ret)
      {
        case BTREE_LEFT:
        if (GET_FIELD(it, m, btree_t)->left == NULL)
        {
          GET_FIELD(it, m, btree_t)->left = new;
          return (true);
        }
        else
        it = GET_FIELD(it, m, btree_t)->left;
        break;
        case BTREE_RIGHT:
        if (GET_FIELD(it, m, btree_t)->right == NULL)
        {
          GET_FIELD(it, m, btree_t)->right = new;
          return (true);
        }
        else
        it = GET_FIELD(it, m, btree_t)->right;
        break;
        case BTREE_MATCH:
        default:
          return (false);
      }
    }
  }
  return (true);
}

void *_btree_remove(void **tree,
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
    ret = compare_key_func(it,
                           key);
    switch (ret)
    {
      case BTREE_LEFT:
        left_prev = it;
        right_prev = NULL;
        it = GET_FIELD(it, m, btree_t)->left;
        break;
      case BTREE_RIGHT:
        left_prev = NULL;
        right_prev = it;
        it = GET_FIELD(it, m, btree_t)->right;
        break;
      case BTREE_MATCH:
          node = NULL;
        if (left_prev == NULL
            && right_prev == NULL
            && GET_FIELD(it, m, btree_t)->left == NULL
            && GET_FIELD(it, m, btree_t)->right == NULL)
          *tree = NULL;
        else
        {
          if (GET_FIELD(it, m, btree_t)->left != NULL)
          {
            /* Get the node depthest node on the right of the left child. */

            parent = it;
            node = GET_FIELD(it, m, btree_t)->left;
            while (GET_FIELD(node, m, btree_t)->right != NULL)
            {
              parent = node;
              node = GET_FIELD(node, m, btree_t)->right;
            }
            if (parent != it)
            {
              GET_FIELD(parent, m, btree_t)->right = GET_FIELD(node, m, btree_t)->left;
              GET_FIELD(node, m, btree_t)->left = GET_FIELD(it, m, btree_t)->left;
            }
            GET_FIELD(node, m, btree_t)->right = GET_FIELD(it, m, btree_t)->right;
          }
          else
          {
            if (GET_FIELD(it, m, btree_t)->right != NULL)
            {
              /* Get the node depthest node on the left of the right child. */

              parent = it;
              node = GET_FIELD(it, m, btree_t)->right;
              while (GET_FIELD(node, m, btree_t)->left != NULL)
              {
                parent = node;
                node = GET_FIELD(node, m, btree_t)->left;
              }
              if (parent != it)
              {
                GET_FIELD(parent, m, btree_t)->left = GET_FIELD(node, m, btree_t)->right;
                GET_FIELD(node, m, btree_t)->right = GET_FIELD(it, m, btree_t)->right;
              }
              GET_FIELD(node, m, btree_t)->left = GET_FIELD(it, m, btree_t)->left;
            }
          }
          if (left_prev != NULL)
          {
              GET_FIELD(left_prev, m, btree_t)->left = node;
          }
          else
          {
            if (right_prev != NULL)
            {
              GET_FIELD(right_prev, m, btree_t)->right = node;
            }
            else
              *tree = node;
          }
        }
        return (it);
    }
  }
  return (NULL);
}

bool _btree_graft(void **tree,
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
      it = GET_FIELD(it, m, btree_t)->left;
      break;
      case BTREE_RIGHT:
      left_prev = NULL;
      right_prev = it;
      it = GET_FIELD(it, m, btree_t)->right;
      break;
      case BTREE_MATCH:
      return (false);
    }
  }
  if (left_prev != NULL)
  GET_FIELD(left_prev, m, btree_t)->left = subtree;
  else
  {
    if (right_prev != NULL)
    GET_FIELD(right_prev, m, btree_t)->right = subtree;
    else
    *tree = subtree;
  }
  return (true);
}

void *_btree_prune(void **tree,
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
        it = GET_FIELD(it, m, btree_t)->left;
        break;
      case BTREE_RIGHT:
        left_prev = NULL;
        right_prev = it;
        it = GET_FIELD(it, m, btree_t)->right;
        break;
      case BTREE_MATCH:
        if (left_prev != NULL)
          GET_FIELD(left_prev, m, btree_t)->left = NULL;
        else
        {
          if (right_prev != NULL)
            GET_FIELD(right_prev, m, btree_t)->right = NULL;
          else
            *tree = NULL;
        }
        return (it);
    }
  }
  return (NULL);
}

void    _btree_walk_preorder(void **tree,
                            unsigned int m,
                            btree_walk_p walk_func,
                            void *data)
{
    if (tree == NULL
        || *tree == NULL
        || walk_func == NULL)
        return;
    walk_func(*tree, data);
    if (GET_FIELD(*tree, m, btree_t)->left != NULL)
        _btree_walk_preorder(&GET_FIELD(*tree, m, btree_t)->left, m, walk_func, data);
    if (GET_FIELD(*tree, m, btree_t)->right != NULL)
        _btree_walk_preorder(&GET_FIELD(*tree, m, btree_t)->right, m, walk_func, data);
}

void    _btree_walk_inorder(void **tree,
                            unsigned int m,
                            btree_walk_p walk_func,
                            void *data)
{
    if (tree == NULL
        || *tree == NULL
        || walk_func == NULL)
        return;
    if (GET_FIELD(*tree, m, btree_t)->left != NULL)
        _btree_walk_inorder(&GET_FIELD(*tree, m, btree_t)->left, m, walk_func, data);
    walk_func(*tree, data);
    if (GET_FIELD(*tree, m, btree_t)->right != NULL)
        _btree_walk_inorder(&GET_FIELD(*tree, m, btree_t)->right, m, walk_func, data);
}

void    _btree_walk_postorder(void **tree,
                            unsigned int m,
                            btree_walk_p walk_func,
                            void *data)
{
    if (tree == NULL
        || *tree == NULL
        || walk_func == NULL)
        return;
    if (GET_FIELD(*tree, m, btree_t)->left != NULL)
        _btree_walk_postorder(&GET_FIELD(*tree, m, btree_t)->left, m, walk_func, data);
    if (GET_FIELD(*tree, m, btree_t)->right != NULL)
        _btree_walk_postorder(&GET_FIELD(*tree, m, btree_t)->right, m, walk_func, data);
    walk_func(*tree, data);
}

void *_btree_lookup(void **tree,
                    void *key,
                    unsigned int m,
                    btree_compare_key_p compare_key_func)
{
  void *it;
  int ret;

  if (tree == NULL || *tree == NULL || compare_key_func == NULL)
    return (NULL);
  it = *tree;
  while (it)
  {
    ret = compare_key_func(it,
                           key);
    switch (ret)
    {
      case BTREE_LEFT:
        it = GET_FIELD(it, m, btree_t)->left;
        break;
      case BTREE_RIGHT:
        it = GET_FIELD(it, m, btree_t)->right;
        break;
      case BTREE_MATCH:
        return (it);
    }
  }
  return (it);
}
