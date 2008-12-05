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

static void *__splay(void **tree,
                      void *key,
                      unsigned int m,
                      btree_compare_key_p compare_key_func)
{
  int   diff;
  int   diff2;
  void  *tmp;

  /*
   *
   * Case 1. If the parent of n () is the root, rotate at n - i.e. apply the rotation that makes n the tree's root, and makes its former parent into its child.
   *  The next two cases affect both n and its two immediate ancestors (also ).
   *
   * Case 2. If n and its parent p have the same orientation - i.e. they are both left or both right childrent - first rotate at p and then at n.
   *
   * Case 3. On the other hand, if n and its parent p have different orientations - then rotate twice at n.
   *
   */

  while (*tree != NULL && (diff = compare_key_func(*tree, key)) != BTREE_MATCH)
  {
    if (diff == BTREE_LEFT)
    {
      diff2 = compare_key_func(GET_FIELD(*tree, m, splay_tree_t)->left, key);
      if (diff2 == BTREE_MATCH)
        *tree = avl_single_rotate_with_left(*tree, m);
      if (diff2 == BTREE_LEFT)
      {
        *tree = avl_single_rotate_with_left(*tree, m);
        *tree = avl_single_rotate_with_left(*tree, m);
      }
      if (diff2 == BTREE_RIGHT)
      {
        tmp = GET_FIELD(*tree, m, splay_tree_t)->left;
        tmp = avl_single_rotate_with_right(tmp, m);
        GET_FIELD(*tree, m, splay_tree_t)->left = tmp;
      }
    }
    else
    {
      diff2 = compare_key_func(GET_FIELD(*tree, m, splay_tree_t)->right, key);
      if (diff2 == BTREE_MATCH)
        *tree = avl_single_rotate_with_right(*tree, m);
      if (diff2 == BTREE_RIGHT)
      {
        *tree = avl_single_rotate_with_right(*tree, m);
        *tree = avl_single_rotate_with_right(*tree, m);
      }
      if (diff2 == BTREE_LEFT)
      {
        tmp = GET_FIELD(*tree, m, splay_tree_t)->right;
        tmp = avl_single_rotate_with_left(tmp, m);
        GET_FIELD(*tree, m, splay_tree_t)->right = tmp;
      }
    }
  }
  return (*tree);
}

/* Splay tree functions. */

void *_splay_tree_lookup(void **tree,
                    void *key,
                    unsigned int m,
                    btree_compare_key_p compare_key_func)
{
  void *node;

  node = _btree_lookup(tree, key, m, compare_key_func);
  if (node != NULL)
    node = __splay(tree, key, m, compare_key_func);
  return (node);
}
