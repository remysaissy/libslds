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

#include	"include/avl_rotation.h"

/* Perform an AVL left rotation. */
void _avl_rotate_left(void **tree,
                      void *node,
                      unsigned int m)
{
  void          *parent;
  void          *grandparent;
    
  if (tree == NULL
      || *tree == NULL
      || node == NULL)
    return;
  parent = GET_FIELD(node, m, avl_compatible_tree_t)->parent;
  grandparent = GET_FIELD(parent, m, avl_compatible_tree_t)->parent;
  GET_FIELD(parent, m, avl_compatible_tree_t)->left = GET_FIELD(node, m, avl_compatible_tree_t)->right;
  if (GET_FIELD(parent, m, avl_compatible_tree_t)->left != NULL)
    GET_FIELD(GET_FIELD(parent, m, avl_compatible_tree_t)->left, m, avl_compatible_tree_t)->parent = parent;
  GET_FIELD(node, m, avl_compatible_tree_t)->right = parent;
  GET_FIELD(parent, m, avl_compatible_tree_t)->parent = node;
  if (grandparent == NULL)
    *tree = node;
    else if (parent == GET_FIELD(grandparent, m, avl_compatible_tree_t)->left)
      GET_FIELD(grandparent, m, avl_compatible_tree_t)->left = node;
    else
      GET_FIELD(grandparent, m, avl_compatible_tree_t)->right = node;    
  GET_FIELD(node, m, avl_compatible_tree_t)->parent = grandparent;
}

/* Perform an AVL right rotation. */
void _avl_rotate_right(void **tree,
                        void *node,
      			unsigned int m)
{
  void          *parent;
  void          *grandparent;
    
  if (tree == NULL
      || *tree == NULL
      || node == NULL)
    return;
  parent = GET_FIELD(node, m, avl_compatible_tree_t)->parent;
  grandparent = GET_FIELD(parent, m, avl_compatible_tree_t)->parent;
  GET_FIELD(parent, m, avl_compatible_tree_t)->right = GET_FIELD(node, m, avl_compatible_tree_t)->left;
  if (GET_FIELD(parent, m, avl_compatible_tree_t)->right != NULL)
    GET_FIELD(GET_FIELD(parent, m, avl_compatible_tree_t)->right, m, avl_compatible_tree_t)->parent = parent;
  GET_FIELD(node, m, avl_compatible_tree_t)->left = parent;
  GET_FIELD(parent, m, avl_compatible_tree_t)->parent = node;
  if (grandparent == NULL)
    *tree = node;
    else if (parent == GET_FIELD(grandparent, m, avl_compatible_tree_t)->left)
      GET_FIELD(grandparent, m, avl_compatible_tree_t)->left = node;
    else
      GET_FIELD(grandparent, m, avl_compatible_tree_t)->right = node;    
  GET_FIELD(node, m, avl_compatible_tree_t)->parent = grandparent;
}
