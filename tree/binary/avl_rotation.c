/*
 * avl_rotation.c
 *
 *  Created on: 5 déc. 2008
 *      Author: remy
 */

#include <tree.h>
#include "include/avl_rotation.h"

void    *avl_single_rotate_with_left(void *node,
                                     unsigned int m)
{
  void  *tmp;

  tmp = GET_FIELD(node, m, binary_tree_base_t)->left;
  GET_FIELD(node, m, binary_tree_base_t)->left = GET_FIELD(tmp, m, binary_tree_base_t)->right;
  GET_FIELD(tmp, m, binary_tree_base_t)->right = node;
  return (tmp);
}

void    *avl_single_rotate_with_right(void *node,
                                      unsigned int m)
{
  void  *tmp;

  tmp = GET_FIELD(node, m, binary_tree_base_t)->right;
  GET_FIELD(node, m, binary_tree_base_t)->right = GET_FIELD(tmp, m, binary_tree_base_t)->left;
  GET_FIELD(tmp, m, binary_tree_base_t)->left = node;
  return (tmp);
}
