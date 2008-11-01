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

#ifndef	__LIBSLDS_TREE_H__
#error	"Direct inclusion not allowed. Please include tree.h instead."
#endif

#ifndef	__LIBSLDS_BINARY_TREE_COMMON_H__
#define	__LIBSLDS_BINARY_TREE_COMMON_H__

/*
 * This header provides code common to all binary trees.
 */


/* Data type. */

/**
 * Enumerator of return values of comparison functions.
 * When evaluating a binary tree node, the result can be
 * to go to the left or to the right child. the comparison
 * also match and, in that case, match is returned.
 */
typedef enum	_btree_compare_e
{
	BTREE_LEFT = -1,
	BTREE_MATCH,
	BTREE_RIGHT
	
}				btree_compare_e;

/** 
 * Comparison callback. This callback is used to compare two nodes.
 * @param tree_node The node of the tree. Typically, this node is different from one call to another.
 * @param node The node used for comparison.
 * @return Where the caller must go next: left or right child or match if the comparison matched. 
 */
typedef btree_compare_e (*btree_compare_p)(void *tree_node, void *node);

/** 
 * Comparison callback. This callback is used to compare a node and a key.
 * @param tree_node The node of the tree. Typically, this node is different from one call to another.
 * @param key The key to compare with tree_node.
 * @return Where the caller must go next: left or right child or match if the comparison matched. 
 */
typedef btree_compare_e (*btree_compare_key_p)(void *tree_node, void *key);

/** 
 * Walk along the tree callback. It is used like an iterator.
 * @param node The node of the tree.
 * @param data variable and optional parameter that can be used by the callback content. Typically used to locate the comparison state. 
 */
typedef void            (*btree_walk_p)(void *node, void *data);

/**
 * This data structure must be at least present in every
 * binary trees in order to let them use methods below.
 * 
 * This must be the very first member of any binary tree
 * compatible structure. The structure itself can be
 * anywhere within the structure of a program.
 */
typedef struct	binary_tree_base_s
{
  void		*left;
  void		*right;

}				binary_tree_base_t;

/* Methods */

/**
 * Look for a node in a binary tree.
 * @param tree The root of the tree.
 * @param key Key to the node to look for.
 * @param m The offset of the binary tree datastructure in tree.
 * @param compare_key_func callback for comparison.
 * @return The node looked up on success, NULL on error. 
 */
void	*_binary_tree_lookup(void **tree, 
		       void *key, 
		       unsigned int m, 
		       btree_compare_key_p compare_key_func);

/**
 * Step along the tree in a preorder fashion.
 * @param tree The root of the tree.
 * @param m The offset of the binary tree datastructure in tree.
 * @param walk_func Callback used like an iterator. Called for every nodes.
 * @param data arbitrary data for callbacks.
 */
void	_binary_tree_walk_preorder(void **tree,
							unsigned int m,
							btree_walk_p walk_func,
							void *data);

/**
 * Step along the tree in a inorder fashion.
 * @param tree The root of the tree.
 * @param m The offset of the binary tree datastructure in tree.
 * @param walk_func Callback used like an iterator. Called for every nodes.
 * @param data arbitrary data for callbacks.
 */
void	_binary_tree_walk_inorder(void **tree,
							unsigned int m,		
							btree_walk_p walk_func,
							void *data);

/**
 * Step along the tree in a postorder fashion.
 * @param tree The root of the tree.
 * @param m The offset of the binary tree datastructure in tree.
 * @param walk_func Callback used like an iterator. Called for every nodes.
 * @param data arbitrary data for callbacks.
 */
void	_binary_tree_walk_postorder(void **tree,
							unsigned int m,		
							btree_walk_p walk_func,
							void *data);




#endif /* __LIBSLDS_BINARY_TREE_COMMON_H__ */
