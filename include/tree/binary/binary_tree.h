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

#ifndef	__LIBSLDS_BINARY_BTREE_H__
#define	__LIBSLDS_BINARY_BTREE_H__

/**
 * This header implements binary search trees.
 * In order to be flexible, the key lookup line is
 * left to the caller through a macro so it can be
 * set and unset at will.
 */

#include <tree/binary/common.h>

/* Data type. */

/**
 * The datastructure which represents a binary tree.
 */
typedef struct	btree_s
{
	binary_tree_base_t	_btree_base;

}		btree_t;

/* Implementation. */

/**
 * Initialize a binary tree node.
 * @param tree The root of the tree.
 * @param m The name of the binary tree datastructure in tree.
 * @return true on success, false on error.
 */
#define	btree_init(tree, m)						\
	_btree_init((void *)(tree),						\
		   (unsigned int)offsetof(typeof(*(tree)), m))

/**
 * Look for a node in a binary tree.
 * @param tree The root of the tree.
 * @param key Key to the node to look for.
 * @param m The name of the binary tree datastructure in tree.
 * @param compare_key_func callback for comparison.
 * @return The node looked up on success, NULL on error.
 */
#define	btree_lookup(tree, key, m, compare_key_func)			\
	_binary_tree_lookup((void **)&(tree),						\
	    (void *)(key),						\
		     (unsigned int)offsetof(typeof(*(tree)), m),	\
		     compare_key_func)

/**
 * Insert a binary tree node.
 * @param tree The root of the tree.
 * @param new The node to be added.
 * @param m The name of the binary tree datastructure in tree.
 * @param compare_func callback for comparison.
 * @return true on success, false on error.
 */
#define	btree_insert(tree, new, m, compare_func)			\
	_btree_insert((void **)&(tree),						\
              (void *)(new),						\
		     (unsigned int)offsetof(typeof(*(tree)), m),	\
		     compare_func)

/**
 * Remove a binary tree node.
 * @param tree The root of the tree.
 * @param key Key to the node to be removed.
 * @param m The name of the binary tree datastructure in tree.
 * @param compare_func callback for comparison.
 * @param compare_key_func callback for comparison.
 * @return The node removed on success, NULL on error.
 */
#define	btree_remove(tree, key, m, compare_func, compare_key_func)	\
     _btree_remove((void **)&(tree),						\
         (void *)(key),						\
		  (unsigned int)offsetof(typeof(*(tree)), m),		\
		  compare_func,						\
		  compare_key_func)

/**
 * Graft a subtree in a binary tree.
 * @param tree The root of the tree.
 * @param subtree subtree to be graft.
 * @param m The name of the binary tree datastructure in tree.
 * @param compare_func callback for comparison.
 * @return true on success, false on error.
 * @note A subtree that has nodes which are also in tree can be grafted.
 * this preliminary control is left to the caller.
 */
#define	btree_graft(tree, subtree, m, compare_func)			\
	_btree_graft((void **)&(tree),						\
	    (void *)(subtree),						\
		     (unsigned int)offsetof(typeof(*(tree)), m),	\
		     compare_func)

/**
 * Prune a binary tree.
 * @param tree The root of the tree.
 * @param key key of the part of the tree to be pruned.
 * @param m The name of the binary tree datastructure in tree.
 * @param compare_key_func callback for comparison.
 * @return The subtree on success, NULL on error.
 */
#define	btree_prune(tree, key, m, compare_key_func)			\
	_btree_prune((void **)&(tree),						\
	    (void *)(key),						\
		     (unsigned int)offsetof(typeof(*(tree)), m),	\
		     compare_key_func)

/**
 * Step along the tree in a preorder fashion.
 * @param tree The root of the tree.
 * @param m The name of the binary tree datastructure in tree.
 * @param walk_func Callback used like an iterator. Called for every nodes.
 * @param data arbitrary data for callbacks.
 */
#define	btree_walk_preorder(tree, m, walk_func, data)						\
		_binary_tree_walk_preorder((void **)&(tree),								\
							(unsigned int)offsetof(typeof(*(tree)), m),	\
							walk_func,										\
							(void *)(data))

/**
 * Step along the tree in a inorder fashion.
 * @param tree The root of the tree.
 * @param m The name of the binary tree datastructure in tree.
 * @param walk_func Callback used like an iterator. Called for every nodes.
 * @param data arbitrary data for callbacks.
 */
#define	btree_walk_inorder(tree, m, walk_func, data)						\
		_binary_tree_walk_inorder((void **)&(tree),								\
							(unsigned int)offsetof(typeof(*(tree)), m),	\
							walk_func,										\
							(void *)(data))

/**
 * Step along the tree in a postorder fashion.
 * @param tree The root of the tree.
 * @param m The name of the binary tree datastructure in tree.
 * @param walk_func Callback used like an iterator. Called for every nodes.
 * @param data arbitrary data for callbacks.
 */
#define	btree_walk_postorder(tree, m, walk_func, data)						\
		_binary_tree_walk_postorder((void **)&(tree),						\
							(unsigned int)offsetof(typeof(*(tree)), m),	\
							walk_func,										\
							(void *)(data))


/* tree implementation. */

/**
 * Initialize a binary tree node.
 * @param tree The root of the tree.
 * @param m The offset of the binary tree datastructure in tree.
 * @return true on success, false on error.
 */
bool	_btree_init(void *tree,
		    unsigned int m);
/**
 * Insert a binary tree node.
 * @param tree The root of the tree.
 * @param new The node to be added.
 * @param m The offset of the binary tree datastructure in tree.
 * @param compare_func callback for comparison.
 * @return true on success, false on error.
 */
bool	_btree_insert(void **tree,
		      void *new,
		      unsigned int m,
		      btree_compare_p compare_func);

/**
 * Remove a binary tree node.
 * @param tree The root of the tree.
 * @param key Key to the node to be removed.
 * @param m The offset of the binary tree datastructure in tree.
 * @param compare_func callback for comparison.
 * @param compare_key_func callback for comparison.
 * @return The node removed on success, NULL on error.
 */
void	*_btree_remove(void **tree,
		      void *key,
		      unsigned int m,
		      btree_compare_p compare_func,
		      btree_compare_key_p compare_key_func);

/**
 * Graft a subtree in a binary tree.
 * @param tree The root of the tree.
 * @param subtree subtree to be graft.
 * @param m The offset of the binary tree datastructure in tree.
 * @param compare_func callback for comparison.
 * @return true on success, false on error.
 * @note A subtree that has nodes which are also in tree can be grafted.
 * this preliminary control is left to the caller.
 */
bool	_btree_graft(void **tree,
		     void *subtree,
		     unsigned int m,
		     btree_compare_p compare_func);

/**
 * Prune a binary tree.
 * @param tree The root of the tree.
 * @param key key of the part of the tree to be pruned.
 * @param m The offset of the binary tree datastructure in tree.
 * @param compare_key_func callback for comparison.
 * @return The subtree on success, NULL on error.
 */
void	*_btree_prune(void **tree,
		     void *key,
		     unsigned int m,
		     btree_compare_key_p compare_key_func);

#endif /* __LIBSLDS_BINARY_BTREE_H__ */
