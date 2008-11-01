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

#include	<tree.h>

void	_binary_tree_walk_preorder(void **tree,
							unsigned int m,
							btree_walk_p walk_func,
							void *data)
{
	if (tree == NULL
		|| *tree == NULL
		|| walk_func == NULL)
		return;
	walk_func(*tree, data);
	if (GET_FIELD(*tree, m, binary_tree_base_t)->left != NULL)
		_binary_tree_walk_preorder(&GET_FIELD(*tree, m, binary_tree_base_t)->left, m, walk_func, data);
	if (GET_FIELD(*tree, m, btree_t)->_btree_base.right != NULL)
		_binary_tree_walk_preorder(&GET_FIELD(*tree, m, binary_tree_base_t)->right, m, walk_func, data);
}

void	_binary_tree_walk_inorder(void **tree,
							unsigned int m,		
							btree_walk_p walk_func,
							void *data)
{
	if (tree == NULL
		|| *tree == NULL
		|| walk_func == NULL)
		return;
	if (GET_FIELD(*tree, m, binary_tree_base_t)->left != NULL)
		_binary_tree_walk_inorder(&GET_FIELD(*tree, m, binary_tree_base_t)->left, m, walk_func, data);
	walk_func(*tree, data);
	if (GET_FIELD(*tree, m, binary_tree_base_t)->right != NULL)
		_binary_tree_walk_inorder(&GET_FIELD(*tree, m, binary_tree_base_t)->right, m, walk_func, data);
}

void	_binary_tree_walk_postorder(void **tree,
							unsigned int m,		
							btree_walk_p walk_func,
							void *data)
{
	if (tree == NULL
		|| *tree == NULL
		|| walk_func == NULL)
		return;
	if (GET_FIELD(*tree, m, binary_tree_base_t)->left != NULL)
		_binary_tree_walk_postorder(&GET_FIELD(*tree, m, binary_tree_base_t)->left, m, walk_func, data);
	if (GET_FIELD(*tree, m, binary_tree_base_t)->right != NULL)
		_binary_tree_walk_postorder(&GET_FIELD(*tree, m, binary_tree_base_t)->right, m, walk_func, data);
	walk_func(*tree, data);	
}

void *_binary_tree_lookup(void **tree,
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
        it = GET_FIELD(it, m, binary_tree_base_t)->left;
        break;
      case BTREE_RIGHT:
        it = GET_FIELD(it, m, binary_tree_base_t)->right;
        break;
      case BTREE_MATCH:
        return (it);
    }
  }
  return (it);
}
